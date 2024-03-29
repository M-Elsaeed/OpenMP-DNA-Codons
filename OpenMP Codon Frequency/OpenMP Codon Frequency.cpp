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
unordered_map<string, int> countMapParallel({{"ILE", 0},
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
unordered_map<string, int> countMapSequential({{"ILE", 0},
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
	for (int i = 0; i < inStr.size(); i += 3)
	{
		string temp{inStr[i], inStr[i + 1], inStr[i + 2]};
		countMapSequential[codonMap[temp]] += 1;
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
#pragma omp parallel for
	for (int i = 0; i < inStr.size(); i += 3)
	{
		string temp{inStr[i], inStr[i + 1], inStr[i + 2]};
#pragma omp atomic
		countMapParallel[codonMap[temp]] += 1;
	}
	auto end = chrono::steady_clock::now();
	cout << "Parallel time in milliseconds : "
		 << chrono::duration_cast<chrono::milliseconds>(end - start).count()
		 << " ms" << endl;
}

void parallelSections(string inStr)
{

	const int seqSize[] = {
		inStr.size() / 2,
		inStr.size()};

	vector<vector<string>> codonsArr(2, vector<string>(seqSize[1] / 3));
	int countedCodons[2] = {0, 0};
	int formedCodons[2] = {0, 0};
	int done[2] = {0, 0};

	omp_set_nested(1);
	omp_set_num_threads(threads);

	auto start = chrono::steady_clock::now();
#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < seqSize[0]; i += 3)
			{
				string temp = {inStr[i], inStr[i + 1], inStr[i + 2]};
				codonsArr[0][formedCodons[0]++] = temp;
			}
			done[0] = 1;
		}
#pragma omp section
		{
			while ((!done[0]) || (countedCodons[0] < formedCodons[0]))
			{
				while (countedCodons[0] < formedCodons[0])
				{
#pragma omp atomic
					countMapSections[codonMap[codonsArr[0][countedCodons[0]]]] += 1;
					countedCodons[0]++;
				}
			}
		}

#pragma omp section
		{
			for (int i = seqSize[0]; i < seqSize[1]; i += 3)
			{
				string temp = {inStr[i], inStr[i + 1], inStr[i + 2]};
				codonsArr[1][formedCodons[1]++] = temp;
			}
			done[1] = 1;
		}
#pragma omp section
		{
			while ((!done[1]) || (countedCodons[1] < formedCodons[1]))
			{
				while (countedCodons[1] < formedCodons[1])
				{
#pragma omp atomic
					countMapSections[codonMap[codonsArr[1][countedCodons[1]]]] += 1;
					countedCodons[1]++;
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
		parallelSections(inStr);
		parallel(inStr);

		string errs = "No Errors";
		for (auto i = countMapSequential.begin(); i != countMapSequential.end(); i++)
		{
			cout << i->first << "      " << i->second << ", " << countMapSections[i->first] << ", " << countMapParallel[i->first] << " , Percentage: " << (float)(i->second * 100) / (float)(inStr.length() / 3) << "\%" << endl;
			if (!(i->second == countMapParallel[i->first] && countMapParallel[i->first] == countMapSections[i->first]))
			{
				cout << "Error Here" << endl;
				errs = "Errors";
			}
			i->second = 0;
			countMapParallel[i->first] = 0;
			countMapSections[i->first] = 0;
		}
		cout << errs << endl;
		threads *= 2;
	}
	cin >> inStr;
	return 0;
}