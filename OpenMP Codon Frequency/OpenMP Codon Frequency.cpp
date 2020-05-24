#include "omp.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

int threads = 2;

unordered_map<string, string> codonMap({{"ATA", "ILE"},
										{"ATC", "ILE"},
										{"ATT", "ILE"},
										{"ATG", "MET"},
										{"ACA", "THR"},
										{"ACC", "THR"},
										{"ACG", "THR"},
										{"ACT", "THR"},
										{"AAC", "ASN"},
										{"AAT", "ASN"},
										{"AAA", "LYS"},
										{"AAG", "LYS"},
										{"AGC", "SER"},
										{"AGT", "SER"},
										{"AGA", "ARG"},
										{"AGG", "ARG"},
										{"CTA", "LEU"},
										{"CTC", "LEU"},
										{"CTG", "LEU"},
										{"CTT", "LEU"},
										{"CCA", "PRO"},
										{"CCC", "PRO"},
										{"CCG", "PRO"},
										{"CCT", "PRO"},
										{"CAC", "HIS"},
										{"CAT", "HIS"},
										{"CAA", "GIN"},
										{"CAG", "GIN"},
										{"CGA", "ARG"},
										{"CGC", "ARG"},
										{"CGG", "ARG"},
										{"CGT", "ARG"},
										{"GTA", "VAL"},
										{"GTC", "VAL"},
										{"GTG", "VAL"},
										{"GTT", "VAL"},
										{"GCA", "ALA"},
										{"GCC", "ALA"},
										{"GCG", "ALA"},
										{"GCT", "ALA"},
										{"GAC", "ASP"},
										{"GAT", "ASP"},
										{"GAA", "GLU"},
										{"GAG", "GLU"},
										{"GGA", "GLY"},
										{"GGC", "GLY"},
										{"GGG", "GLY"},
										{"GGT", "GLY"},
										{"TCA", "SER"},
										{"TCC", "SER"},
										{"TCG", "SER"},
										{"TCT", "SER"},
										{"TTC", "PHE"},
										{"TTT", "PHE"},
										{"TTA", "LEU"},
										{"TTG", "LEU"},
										{"TAC", "TYR"},
										{"TAT", "TYR"},
										{"TAA", "STP"},
										{"TAG", "STP"},
										{"TGC", "CYS"},
										{"TGT", "CYS"},
										{"TGA", "STP"},
										{"TGG", "TRP"}});
unordered_map<string, int> countMap({{"ILE", 0},
									 {"MET", 0},
									 {"THR", 0},
									 {"ASN", 0},
									 {"LYS", 0},
									 {"ARG", 0},
									 {"LEU", 0},
									 {"PRO", 0},
									 {"HIS", 0},
									 {"GIN", 0},
									 {"VAL", 0},
									 {"ALA", 0},
									 {"ASP", 0},
									 {"GLU", 0},
									 {"GLY", 0},
									 {"SER", 0},
									 {"PHE", 0},
									 {"LEU", 0},
									 {"TYR", 0},
									 {"STP", 0},
									 {"CYS", 0},
									 {"TRP", 0}});
unordered_map<string, int> countMapSections({{"ILE", 0},
											 {"MET", 0},
											 {"THR", 0},
											 {"ASN", 0},
											 {"LYS", 0},
											 {"ARG", 0},
											 {"LEU", 0},
											 {"PRO", 0},
											 {"HIS", 0},
											 {"GIN", 0},
											 {"VAL", 0},
											 {"ALA", 0},
											 {"ASP", 0},
											 {"GLU", 0},
											 {"GLY", 0},
											 {"SER", 0},
											 {"PHE", 0},
											 {"LEU", 0},
											 {"TYR", 0},
											 {"STP", 0},
											 {"CYS", 0},
											 {"TRP", 0}});
unordered_map<string, int> countMapSeq({{"ILE", 0},
										{"MET", 0},
										{"THR", 0},
										{"ASN", 0},
										{"LYS", 0},
										{"ARG", 0},
										{"LEU", 0},
										{"PRO", 0},
										{"HIS", 0},
										{"GIN", 0},
										{"VAL", 0},
										{"ALA", 0},
										{"ASP", 0},
										{"GLU", 0},
										{"GLY", 0},
										{"SER", 0},
										{"PHE", 0},
										{"LEU", 0},
										{"TYR", 0},
										{"STP", 0},
										{"CYS", 0},
										{"TRP", 0}});

void sequential(string inStr)
{
	string temp = "";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < inStr.size() - 3; i += 3)
	{
		string temp{inStr[i], inStr[i + 1], inStr[i + 2]};
		countMapSeq[codonMap[temp]] += 1;
	}
	auto end = chrono::steady_clock::now();
	cout << "Sequential time in milliseconds : "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}

void parallel(string inStr)
{
	string temp = "";
	omp_set_num_threads(threads);
	auto start = chrono::steady_clock::now();
#pragma omp parallel for private(temp)
	for (int i = 0; i < inStr.size() - 3; i += 3)
	{
		string temp{inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
		countMap[codonMap[temp]] += 1;
	}
	auto end = chrono::steady_clock::now();
	cout << "Parallel time in milliseconds : "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}

void parallelSections(string inStr)
{

	const int seqSize1 = inStr.size() - (inStr.size() / 2) - 3;
	int countedCodons1 = 0, formedCodons1 = 0;

	const int seqSize2 = inStr.size() - 3;
	int countedCodons2 = 0, formedCodons2 = 0;

	cout << "seq1 " << seqSize1 << " seq2 " << seqSize2 << endl;

	vector<string> codonsArr1(seqSize2 / 3);
	vector<string> codonsArr2(seqSize2 / 3);

	omp_set_nested(5);
	omp_set_num_threads(threads);

	int done1 = 0;
	int done2 = 0;

	auto start = chrono::steady_clock::now();
#pragma omp parallel sections
	{
#pragma omp section
		{
#pragma omp parallel for schedule(static)
			for (int i1 = 0; i1 < seqSize1; i1 += 3)
			{
				string temp1 = {inStr[i1], inStr[i1 + 1], inStr[i1 + 2]};
#pragma omp critical
				codonsArr1[formedCodons1++] = temp1;

				if (i1 == seqSize1 - 3)
				{
					done1 = 1;
				}
			}
		}
#pragma omp section
		{
			while ((!done1) || (countedCodons1 < formedCodons1))
			{
				while (countedCodons1 < formedCodons1)
				{
#pragma omp atomic
					countMapSections[codonMap[codonsArr1[countedCodons1]]] += 1;
					countedCodons1++;
				}
			}
		}
#pragma omp section
		{
#pragma omp parallel for schedule(static)
			for (int i2 = seqSize1; i2 < seqSize2; i2 += 3)
			{
				string temp2 = {inStr[i2], inStr[i2 + 1], inStr[i2 + 2]};
#pragma omp critical
				codonsArr2[formedCodons2++] = temp2;

				if (i2 == seqSize2 - 3)
				{
					done2 = 1;
				}
			}
		}
#pragma omp section
		{
			while ((!done2) || (countedCodons2 < formedCodons2))
			{
				while (countedCodons2 < formedCodons2)
				{
#pragma omp atomic
					countMapSections[codonMap[codonsArr2[countedCodons2]]] += 1;
					countedCodons2++;
				}
			}
		}
	}
	auto end = chrono::steady_clock::now();
	cout << "Sections time in milliseconds : "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}

string readFile()
{
	string inStr = "";
	string temp;
	ifstream inFile;
	inFile.open("D:\\learning\\distributed\\OpenMP Codon Frequency\\InputSeq.dat.txt");
	if (!inFile)
	{
		cerr << "Unable to open file datafile.txt";
		exit(1);
	}
	while (inFile >> temp)
	{
		inStr.append(temp);
	}
	inStr.erase(remove_if(inStr.begin(), inStr.end(), [](char c) { return !isalpha(c); }), inStr.end());
	transform(inStr.begin(), inStr.end(), inStr.begin(), ::toupper);
	inFile.close();
	return inStr;
}

int main()
{
	string inStr = readFile();
	while (threads < 32)
	{
		cout << "# of threads " << threads << endl;

		sequential(inStr);
		parallel(inStr);
		parallelSections(inStr);

		string errs = "No Errors";
		for (auto i = countMap.begin(); i != countMap.end(); i++)
		{
			cout << i->first << "      " << i->second << ", " << countMapSeq[i->first] << ", " << countMapSections[i->first] << endl;
			if (!(i->second == countMapSeq[i->first] && countMapSeq[i->first] == countMapSections[i->first]))
			{
				cout << "Error Here" << endl;
				errs = "Errors";
			}
			i->second = 0;
			countMapSeq[i->first] = 0;
			countMapSections[i->first] = 0;
		}
		cout << errs << endl;
		threads *= 2;
	}
	cin >> inStr;
	return 0;
}