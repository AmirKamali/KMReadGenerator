#include <iostream>
using namespace std;

long* GetReferenceBoundry(string chr,string FAddress);
void PrintChromosome(string chr, long Boundry[], string FAddress);
void GenerateRandomReads(string chr,int ReadsNumber,int ReadLength,string FAddress,bool Overlap);
