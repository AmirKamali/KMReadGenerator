#include <iostream>
using namespace std;

long* GetReferenceBoundry(string chr,string FAddress);
void PrintChromosome(string chr, long Boundry[], string FAddress);
void GenerateReads(string chr,int ReadsNumber,int ReadLength,bool HasVariant,int VariantPercentage,string FAddress,bool Overlap);
