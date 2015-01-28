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
void GenerateReads(string chr, int ReadsNumber, int ReadLength,string ReadQuality,
		 int VariantPercentage, string FAddress,
		bool Overlap, string* OverLapAndSpaceRegion, int RegionNumber,
		string output,string outputformat, bool IsDebugMode);
