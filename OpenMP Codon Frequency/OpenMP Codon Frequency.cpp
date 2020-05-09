#include "omp.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <chrono>
//#include <unistd.h>
using namespace std;

#define Threads 4

unordered_map<string, string> codonMap({
	{ "ATA", "ILE" },
	{ "ATC", "ILE" },
	{ "ATT", "ILE" },
	{ "ATG", "MET" },
	{ "ACA", "THR" },
	{ "ACC", "THR" },
	{ "ACG", "THR" },
	{ "ACT", "THR" },
	{ "AAC", "ASN" },
	{ "AAT", "ASN" },
	{ "AAA", "LYS" },
	{ "AAG", "LYS" },
	{ "AGC", "SER" },
	{ "AGT", "SER" },
	{ "AGA", "ARG" },
	{ "AGG", "ARG" },
	{ "CTA", "LEU" },
	{ "CTC", "LEU" },
	{ "CTG", "LEU" },
	{ "CTT", "LEU" },
	{ "CCA", "PRO" },
	{ "CCC", "PRO" },
	{ "CCG", "PRO" },
	{ "CCT", "PRO" },
	{ "CAC", "HIS" },
	{ "CAT", "HIS" },
	{ "CAA", "GIN" },
	{ "CAG", "GIN" },
	{ "CGA", "ARG" },
	{ "CGC", "ARG" },
	{ "CGG", "ARG" },
	{ "CGT", "ARG" },
	{ "GTA", "VAL" },
	{ "GTC", "VAL" },
	{ "GTG", "VAL" },
	{ "GTT", "VAL" },
	{ "GCA", "ALA" },
	{ "GCC", "ALA" },
	{ "GCG", "ALA" },
	{ "GCT", "ALA" },
	{ "GAC", "ASP" },
	{ "GAT", "ASP" },
	{ "GAA", "GLU" },
	{ "GAG", "GLU" },
	{ "GGA", "GLY" },
	{ "GGC", "GLY" },
	{ "GGG", "GLY" },
	{ "GGT", "GLY" },
	{ "TCA", "SER" },
	{ "TCC", "SER" },
	{ "TCG", "SER" },
	{ "TCT", "SER" },
	{ "TTC", "PHE" },
	{ "TTT", "PHE" },
	{ "TTA", "LEU" },
	{ "TTG", "LEU" },
	{ "TAC", "TYR" },
	{ "TAT", "TYR" },
	{ "TAA", "STP" },
	{ "TAG", "STP" },
	{ "TGC", "CYS" },
	{ "TGT", "CYS" },
	{ "TGA", "STP" },
	{ "TGG", "TRP" },
	});

unordered_map<string, int> countMap({ { "ILE", 0 },{ "MET", 0 },{ "THR", 0 },{ "ASN", 0 },{ "LYS", 0 },{ "ARG", 0 },{ "LEU", 0 },{ "PRO", 0 },{ "HIS", 0 },{ "GIN", 0 },{ "VAL", 0 },{ "ALA", 0 },{ "ASP", 0 },{ "GLU", 0 },{ "GLY", 0 },{ "SER", 0 },{ "PHE", 0 },{ "LEU", 0 },{ "TYR", 0 },{ "STP", 0 },{ "CYS", 0 },{ "TRP", 0 } });
unordered_map<string, int> countMapSections({ { "ILE", 0 },{ "MET", 0 },{ "THR", 0 },{ "ASN", 0 },{ "LYS", 0 },{ "ARG", 0 },{ "LEU", 0 },{ "PRO", 0 },{ "HIS", 0 },{ "GIN", 0 },{ "VAL", 0 },{ "ALA", 0 },{ "ASP", 0 },{ "GLU", 0 },{ "GLY", 0 },{ "SER", 0 },{ "PHE", 0 },{ "LEU", 0 },{ "TYR", 0 },{ "STP", 0 },{ "CYS", 0 },{ "TRP", 0 } });

unordered_map<string, int> countMapSeq({ { "ILE", 0 },{ "MET", 0 },{ "THR", 0 },{ "ASN", 0 },{ "LYS", 0 },{ "ARG", 0 },{ "LEU", 0 },{ "PRO", 0 },{ "HIS", 0 },{ "GIN", 0 },{ "VAL", 0 },{ "ALA", 0 },{ "ASP", 0 },{ "GLU", 0 },{ "GLY", 0 },{ "SER", 0 },{ "PHE", 0 },{ "LEU", 0 },{ "TYR", 0 },{ "STP", 0 },{ "CYS", 0 },{ "TRP", 0 } });



void sequential(string inStr) {
	string temp = "";
	auto start = chrono::steady_clock::now();
	for (int i = 0; i < inStr.size() - 3; i += 3)
	{
		temp = "";
		temp.push_back(inStr[i]);
		temp.push_back(inStr[i + 1]);
		temp.push_back(inStr[i + 2]);
		countMapSeq[codonMap[temp]] += 1;
	}
	auto end = chrono::steady_clock::now();
	cout << "Sequential time in microseconds : "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " ms" << endl;
}

void parallel(string inStr) {
	string temp = "";
	omp_set_num_threads(Threads);
	auto start = chrono::steady_clock::now();
#pragma omp parallel for private(temp)
	for (int i = 0; i < inStr.size() - 3; i += 3)
	{
		temp = "";
		temp.push_back(inStr[i]);
		temp.push_back(inStr[i + 1]);
		temp.push_back(inStr[i + 2]);
		countMap[codonMap[temp]] += 1;
	}
	auto end = chrono::steady_clock::now();
	cout << "Parallel time in microseconds : "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " ms" << endl;
}



void parallelSections(string inStr) {
	string temp = "";
	omp_set_num_threads(Threads);
	auto start = chrono::steady_clock::now();
	auto end = chrono::steady_clock::now();
	cout << "Sections time in microseconds : "
		<< chrono::duration_cast<chrono::microseconds>(end - start).count()
		<< " ms" << endl;
}

int main()
{

	string inStr = "";
	cin >> inStr;
	//inStr.append(inStr);
	//inStr.append(inStr);
	//inStr.append(inStr);
	transform(inStr.begin(), inStr.end(), inStr.begin(), ::toupper);
	cout << inStr << endl;
	
	sequential(inStr);
	parallel(inStr);
	//parallelSections(inStr);

	for (auto i = countMap.begin(); i != countMap.end(); i++)
		cout << i->first << "      " << i->second << ", " << countMapSeq[i->first] << endl;

	cin >> inStr;
	return 0;
}