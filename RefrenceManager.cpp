#include <iostream>
#include <fstream>
#include <string>
#include <libgen.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#import "RefrenceManager.h"
#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"
using namespace std;
#if !defined(ARRAY_SIZE)
#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))
#endif

string GetFileDirectory(string FAddress) {
	return FAddress.substr(0, FAddress.find_last_of("\\/")) + "/";
}
string GetFileName(string filepath) {
	char *ff = const_cast<char*>(filepath.c_str());
	string filename = basename(ff);
	return filename;
}
inline bool FileExist(const std::string& name) {
	ifstream file(name);
	if (!file) // If the file was not found, then file is 0, i.e. !file=1 or true.
		return false;    // The file was not found.
	else
		// If the file was found, then file is non-0.
		return true;     // The file was found.
}
bool GenerateRefrenceIndex(string FAddress) {
	string IndexFileAddress = FAddress + ".kmdx";
	if (!FileExist(FAddress)) {
		cout << "Reference file not found" << endl;
		return false;
	}
	if (FileExist(IndexFileAddress)) {
		cout << "index file found" << endl;
		return true;
	}

	cout << "XGenerating index file for :" << FAddress << endl;
	//Read file
	ifstream file(FAddress);
	string line;

	//Output index
	ofstream outputFile(FAddress + ".kmdx");
	bool InChromosom = false;
	long CC = 0;
	while (file >> line) {

		//cout<<endl<<"SALAAAAAM."<<flush;
		//break;
		if (line.at(0) == '>') {
			cout << "Generating index for " << line << endl << flush;
			long pos = ((long) file.tellg() - (long) line.length());
			if (!InChromosom) {
				outputFile << line << "\t" << pos;
				InChromosom = true;
			} else {
				outputFile << "\t" << pos - 1 << endl << flush;
				;
				InChromosom = false;
			}
		}

		CC += line.length() + 1;
	}
	if (InChromosom) {
		outputFile << "\t" << CC - 1 << flush;
		;
	}
	cout << "CONTENT:" << line;
	file.close();
	outputFile.close();
	return true;
}
long* GetReferenceBoundry(string chr, string FAddress) {
	chr = ">" + chr;
	bool RefrenceOK = GenerateRefrenceIndex(FAddress);
	if (!RefrenceOK) {
		long default_arr[2] = { 0, 0 };
		return default_arr;
	}
	string IndexFileAddress = FAddress + ".kmdx";
	ifstream file(IndexFileAddress);
	string chr_l;
	long pos_start = 0;
	long pos_end = 0;

	while (file >> chr_l >> pos_start >> pos_end) {
		if (chr_l.compare(chr) == 0) {
			break;
		}
	}
	file.close();
	long Res[2];
	Res[0] = pos_start;
	Res[1] = pos_end;
	if (pos_end == 0) {
		cout << "Chromosome not found or index file is not complete." << endl;
	} else {
		cout << "Chr boundry" << pos_start << "-" << pos_end << endl;
	}
	return Res;
}
void PrintChromosome(string chr, long Boundry[], string FAddress) {
	long StartIndex = Boundry[0];
	long EndIndex = Boundry[1];
	ifstream file(FAddress);
	file.seekg(StartIndex, file.beg);
	string content;
	string ChrAddr = GetFileDirectory(FAddress) + chr + "."
			+ GetFileName(FAddress) + ".fa";
	ofstream outputFile(ChrAddr);
	cout << "Generating chromosome in range:" << StartIndex << "-" << EndIndex
			<< endl;
	//outputFile<<"<chr21";
	while (file >> content && file.tellg() <= EndIndex) {
		//cout<<"1";
		outputFile << content << endl;
	}
	outputFile << content << endl;
	file.close();
	outputFile.close();
}
unsigned long LongRandom(long low, long high) {


	 typedef boost::uniform_real<> NumberDistribution;
	  typedef boost::mt19937 RandomNumberGenerator;
	  typedef boost::variate_generator<RandomNumberGenerator&,
	                                   NumberDistribution> Generator;
	  NumberDistribution distribution(low, high);
	    RandomNumberGenerator generator;
	    Generator numberGenerator(generator, distribution);
	    generator.seed(std::time(0)); // seed with the current time

	    long val= numberGenerator() ;
	    return val;
	////2///////////
//    typedef boost::mt19937 RNGType;
//
//    RNGType rng( time(0)*time(0)%50 *time(0) );
//     boost::uniform_int<> one_to_six( low, high );
//     boost::variate_generator< RNGType, boost::uniform_int<> >
//                   dice(rng, one_to_six);
//
//         int n  = dice();
//     return n;

	////////1///////////
//	long Diff = high - low;
//	srand(time(0));
//
//	long RNDDDD = rand();
//
//	cout<<"GENERATINH RANDOM:"<<RNDDDD<<endl;
//	long RandNum = low + (long) (RNDDDD % Diff);
//	return RandNum;
}

string RemoveCharFromString(char c, string str) {
	//cout <<endl<<"Data:"<<str.length()<<str<<endl;
	str.erase(std::remove(str.begin(), str.end(), c), str.end());
	return str;
}
string RemoveCharFromCharArray(char c, char arr[]) {

	char Res[strlen(arr)];
	int Xindex = 0;
	for (int i = 0; arr[i] != '\0'; i++) {

		if (arr[i] != c) {
			Res[Xindex++] = arr[i];
		}
	}
	Res[Xindex] = '\0';
	Res[Xindex + 1] = '\n';
	cout << "After remove:" << Res << endl;
	return Res;
}
string ReadPosition(string Chr, int StartIndex, int EndIndex, string FAddr) {
	cout << "Generating chromosome in range:" << StartIndex << "-" << EndIndex
			<< endl;
	StartIndex += Chr.length() + 2;
	EndIndex += Chr.length() + 2;

	ifstream file(FAddr);
	file.seekg(StartIndex, file.beg);
	file.clear();
	string content;
	string Res = "";
	char * buffer = new char[EndIndex - StartIndex];
	for (int i = 0; i < EndIndex - StartIndex + 1; i++) {
		buffer[i] = '\0';
	}
	file.read(buffer, EndIndex - StartIndex);

	return buffer;
}

std::string ReplaceString(std::string subject, const std::string& search,
		const std::string& replace) {
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return subject;
}
void GenerateOverlappedReads_RandomSize(int TotalReads, long CenterIndex,
		string chr, string FAddress) {

}
int CountWhiteSpace(string str) {
	int sum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\n')
			sum++;
	}
	return sum;
}
char FindVariant(char c) {
	//return 'X';
	if (c == 'A' || c == 'a')
		return 'C';
	else if (c == 'T' || c == 't')
		return 'A';
	else if (c == 'C' || c == 'c')
		return 'G';
	else if (c == 'G' || c == 'g')
		return 'T';
	return c;
}
VariantType GetVariantType(char c)
{
	if (c=='s')
	{
		return VariantTypeSubstitution;
	}
	else if (c=='d')
		{
			return VariantTypeDeletation;
		}
	else if (c=='i')
		{
			return VariantTypeInsertion;
		}
	else
		return VariantTypeNone;
}
void GenerateOverlappedReads_ConstantSize(string chr, int TotalReads,
		int Length, long startindex, long endindex, long CenterIndex
		, int VariantPercentage, string* OverLapAndSpaceRegion,
		int RegionNumber, string FAddress, string output, bool isDebug) {
	int overlapsize = 0;
	//OverlappingRegion : b=blank s=substution i=insertion d=deletion
	for (int i = 0; i < RegionNumber; i++) {
		string str= OverLapAndSpaceRegion[i];

				str=str.substr(1,str.length()-1);
				//cout<<"CCCCLEN"<<str<<endl;;
				overlapsize += stoi(str);

	}

	//cout << "Generating Region is :" << startindex << "-" << endindex
		//	<< "center is:" << CenterIndex << "OVERLAP SIZE:"<<overlapsize<< endl;
	string ReadRegion = ReadPosition(chr, startindex, endindex, FAddress);

	ReadRegion = RemoveCharFromString('\n', ReadRegion);
	cout<<"READ REGION:"<<ReadRegion<<endl;

	string ReadRegion_Mu = "";

	int NumberOfMutatedReads = 0;
	if ( OverLapAndSpaceRegion) {

		NumberOfMutatedReads = (TotalReads * VariantPercentage) / 100;
		ReadRegion_Mu = RemoveCharFromString('\n', ReadRegion);
		int CC = 0;

		int RegionIterator = 0;
		string CurrentRegionValue = OverLapAndSpaceRegion[0];
		VariantType CurrentVariation=GetVariantType(CurrentRegionValue[0]);
		CurrentRegionValue=CurrentRegionValue.substr(1,CurrentRegionValue.length()-1);
		int CurrentRegionIndex = 0;

		for (int i = Length - overlapsize; i < Length; i++) {
			if (CurrentRegionIndex >=stoi( CurrentRegionValue)) {
				RegionIterator++;
				CurrentRegionIndex = 0;
				CurrentRegionValue = OverLapAndSpaceRegion[RegionIterator];
				CurrentVariation=GetVariantType(CurrentRegionValue[0]);
				CurrentRegionValue=CurrentRegionValue.substr(1,CurrentRegionValue.length()-1);
			}
			if (CC++ >= overlapsize)
				break;

			if (CurrentVariation!=VariantTypeNone) {

				//cout<<"EXEC: ITER:"<<RegionIterator<< "Index:"<< CurrentRegionIndex<<"Value:"<<CurrentRegionValue <<endl;
				if (CurrentVariation == VariantTypeSubstitution) {

					char c = FindVariant(ReadRegion_Mu[i]);
					//cout <<"Variant: Substitution at"<<Length-1<< " Original:"<<ReadRegion_Mu[Length-1]<<" New value:" <<c<<endl;
					ReadRegion_Mu[i] = c;
				} else if (CurrentVariation == VariantTypeInsertion) {
					char var_c = FindVariant(ReadRegion_Mu[i]);
					string var_str = "";
					var_str.insert(0, 1, var_c);
					//cout<<"Variant: Insert "<<var_str<<endl;
					ReadRegion_Mu.insert(i, var_str);
				} else if (CurrentVariation == VariantTypeDeletation) {
					//cout <<"Deletion selected"<<endl;
					ReadRegion_Mu.erase(i);
				}
			}
			CurrentRegionIndex++;
			//cout <<"With mutations:"<<NumberOfMutatedReads<<endl;
		}
	}
	else
		cout << "Variation: None" << endl;
cout<<"MUTATION REGION:"<<ReadRegion_Mu<<endl;
	int FramesNumber = Length - overlapsize;
	cout << "Frame number:" << FramesNumber << " Total Reads:" << TotalReads
			<< endl;
	if (TotalReads > FramesNumber + 1) {
		cout << "Reference is too short for the number of reads" << endl;
		return;
	}
	cout << "Frame numbers:" << FramesNumber << endl;

	ofstream outputFile(output);
	if (isDebug) {
		outputFile << ReadRegion << endl;
		outputFile << ReadRegion_Mu << endl << endl;
	}
	int Steps = FramesNumber / TotalReads;
	if (Steps == 0)
		Steps++;
	int Iteration = 1;
	int read_start = 0;
	int read_end = 0;
	cout << "Steps::" << Steps << endl;
	for (int i = 0; i < TotalReads; i++) {

		read_end += Length;
		outputFile << ">" << "Read" << Iteration++ << "." << read_start << "."
				<< read_end << endl;
		string ReadData = "";
		if (NumberOfMutatedReads-- > 0) {
			//cout<<"Applying mutation"<<endl;
			ReadData = ReadRegion_Mu.substr(read_start, Length);
		} else {
			ReadData = ReadRegion.substr(read_start, Length);

		}

		cout << "Generating Read..." << ReadData << endl;

		outputFile << ReadData << endl;
		read_start += Steps;
	}

	outputFile.close();

}

//Read Length = 0 means Random length
void GenerateReads(string chr, int ReadsNumber, int ReadLength,
		 int VariantPercentage, string FAddress,
		bool Overlap, string* OverLapAndSpaceRegion, int RegionNumber,
		string output, bool IsDebugMode) {
	///REMOVE INDEX FILE FOR TEST
	//string IndexAddress=FAddress+".kmdx";
	//if( remove( IndexAddress.c_str() ) != 0 )
	//    perror( "Error deleting file" );
	// else
	//    puts( "File successfully deleted" );
	///
	//cout<<endl<<"CCCCLENxxxxxxxxkjhkewldjlkejflkewfj"<<endl;;

	int overlappinglen = 0;
	//OverlappingRegion : 2,3,5,7,4=2bp+ 3space+5bp+7sp+4bp
	for (int i = 0; i < RegionNumber; i++) {
		//cout<<"OK:"<<OverLapAndSpaceRegion[i]<<endl;
		string str= OverLapAndSpaceRegion[i];

		str=str.substr(1,str.length()-1);
		//cout<<"CCCCLEN"<<str<<endl;;
		overlappinglen += stoi(str);
	}

	cout << "Overlapping region:" << overlappinglen;
	const int ReadLength_MaxRandom = 220;
	long* Boundries = GetReferenceBoundry(chr, FAddress);
	long Pos_start = Boundries[0];
	long Pos_end = Boundries[1];

	if (Pos_end == 0)
		return;
	//Check Space for Randoms
	if (ReadLength == 0 && Pos_end - Pos_start < ReadLength * 2) {
		cout
				<< "Not enough space for generating random reads. For random reads minimum length of the reference should be 2*Read maximum length"
				<< endl;
		return;
	}
	if (Pos_end - Pos_start < 2 * ReadLength + 1) {
		cout
				<< "Not enough space for generating reads. For generating random reads "
				<< endl;
		return;
	}

	int MaxReadLength = ReadLength;
	if (MaxReadLength == 0)
		MaxReadLength = ReadLength_MaxRandom;

	if (ReadLength == 0)	//Not same size reads
			{
		//GenerateOverlappedReads_RandomSize(ReadsNumber,CenterIndex,chr,FAddress);
	} else	//Reads with same size
	{
		long CenterIndex = 0;
		while (true) {
			CenterIndex = LongRandom(Pos_start + ReadLength / 2,
					Pos_end - ReadLength / 2);
			cout << endl << endl << "Randomm Center Number:" << CenterIndex	<< endl;

			int PotentialStartPos = CenterIndex - ReadLength / 2;
			string ReadRegion = ReadPosition(chr, PotentialStartPos,
					PotentialStartPos + ReadLength, FAddress);
			if (ReadRegion[0] == 'N'
					|| ReadRegion[ReadRegion.length() - 1] == 'N') {
				cout << "Un acceptable region :" << ReadRegion << " PosStart:"
						<< PotentialStartPos << endl;
			} else {
				cout << "region found :" << ReadRegion << endl;
				break;
			}
		}

		GenerateOverlappedReads_ConstantSize(chr, ReadsNumber, ReadLength,
				CenterIndex - ReadLength, CenterIndex + ReadLength + 2,
				CenterIndex, VariantPercentage, OverLapAndSpaceRegion,
				RegionNumber, FAddress, output, IsDebugMode);
	}

}

//

