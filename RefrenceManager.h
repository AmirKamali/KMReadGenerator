#include <iostream>
using namespace std;
enum VariantType
{
	VariantTypeNone,
	VariantTypeInsertion,
	VariantTypeDeletation,
	VariantTypeSubstitution
};
long* GetReferenceBoundry(string chr,string FAddress);
void PrintChromosome(string chr, long Boundry[], string FAddress);
void GenerateReads(string chr,int ReadsNumber,int ReadLength, VariantType variantT,int VariantPercentage,string FAddress,bool Overlap,int overlappinglen,string output,bool IsDebugMode);
