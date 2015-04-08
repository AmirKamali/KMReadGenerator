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
const int PAIRED_READ_SPACE=50;//50 bp + 1 \n
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
int CalculatePatternLength(string* Patterns,int PatternNumber)
{
	int PatternLength=0;
	for (int i = 0; i < PatternNumber; i++) {
		string str= Patterns[i];
		if (str[0]!='l'&&str[0]!='r'&&str[0]!='c')
		{
			str=str.substr(1,str.length()-1);
			PatternLength += stoi(str);
		}
	}
	return PatternLength;
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
				outputFile << "\t" << pos -1 << endl << flush;
				if (line.at(0) == '>')
				{
					outputFile << line << "\t" << pos;
					InChromosom=true;
				}
				else
				{
					InChromosom = false;
				}
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
	cout <<"oooooooooooFinding Chromosom boundry for "<<chr<<endl;

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
	if (chr_l.compare(chr)!=0)
	{
		cout <<"Chromosome not found"<<endl;
		return 0;
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
	cout << "Generating chromosome:"<<chr<<" in range:" << StartIndex << "-" << EndIndex
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
	cout << "Generating chromosome"<<Chr<< " in range:" << StartIndex << "-" << EndIndex
			<< endl;
	StartIndex += Chr.length() + 2;
	EndIndex += Chr.length() + 2;
	cout<<"CHR FADDRESS:"<<FAddr<<endl;
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
string GenerateQualityForRead(string Read,string Quality)
{

	if (Quality.length()==0)
	{
		Quality="~";
	}
	if (Quality.length()==Read.length())
	{
		return Quality;
	}
	else
	{
		string QualityStr="";
		for (int i=0;i<Read.length();i++)
		{
			QualityStr+=Quality[0];
		}
		return QualityStr;
	}

}
string ReverseComplement(string Read)
{
	string output="";
	for (int i=Read.length()-1;i>=0;i--)
	{
		if (Read[i]=='a')
			output+="t";
		else if (Read[i]=='A')
			output+="T";
		else if (Read[i]=='t')
			output+="a";
		else if (Read[i]=='T')
			output+="A";
		else if (Read[i]=='c')
			output+="g";
		else if (Read[i]=='C')
			output+="G";
		else if (Read[i]=='g')
			output+="c";
		else if (Read[i]=='G')
			output+="C";
		else
			output+=Read[i];
	}
	return output;
}
void GenerateOverlappedReads_ConstantSize(string prefix,string chr, int TotalReads,
		int Length,string ReadQuality, long startindex, long endindex, long CenterIndex
		, int VariantPercentage, string* OverLapAndSpaceRegion,
		int RegionNumber, string FAddress, string output,string outputformat, bool isDebug) {

//cout <<" CHROMOSOM:"<<chr<<endl;
	int overlapsize = CalculatePatternLength(OverLapAndSpaceRegion,RegionNumber);
	string output_paired=output;

	//OverlappingRegion : b=blank s=substution i=insertion d=deletion

	//cout << "Generating Region is :" << startindex << "-" << endindex
	//	<< "center is:" << CenterIndex << "OVERLAP SIZE:"<<overlapsize<< endl;
	string ReadRegion="";
	if (outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
	{
		ReadRegion= ReadPosition(chr, startindex, endindex+PAIRED_READ_SPACE+Length, FAddress);
		for (int i=output.length()-1;i>=0;i--)
		{
			if (output[i]=='.')
			{
				output=output.insert(i,"_1");
				output_paired=output_paired.insert(i,"_2");
				cout <<"OOOO!!!! Replaced"<<endl;
				break;
			}
		}
	}
	else
	{
		//cout <<"READING chromosome:"<<chr<<endl;
		ReadRegion= ReadPosition(chr, startindex, endindex, FAddress);
	}

	ReadRegion = RemoveCharFromString('\n', ReadRegion);
	cout<<"READ REGION:"<<ReadRegion<<endl;
	cout <<"OUTPUT1:"<<output<<" PAIR NAME:"<<output_paired<<endl;

	string ReadRegion_Mu = "";

	int NumberOfMutatedReads = 0;
	if ( OverLapAndSpaceRegion) {
		cout <<"generating Overlapped"<<endl;
		NumberOfMutatedReads = (TotalReads * VariantPercentage) / 100;
		ReadRegion_Mu = RemoveCharFromString('\n', ReadRegion);
		int CC = 0;

		int RegionIterator = 0;
		string CurrentRegionValue = OverLapAndSpaceRegion[0];//s25
		VariantType CurrentVariation=GetVariantType(CurrentRegionValue[0]);//s
		CurrentRegionValue=CurrentRegionValue.substr(1,CurrentRegionValue.length()-1);//25
		int CurrentRegionIndex = 0;
		cout <<"LEngth:"<<Length<<" Over lap size:"<<overlapsize<<endl;

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

					//Add to paired end
					if (outputformat.compare("pair-mu")==0)
					{
						char c = FindVariant(ReadRegion_Mu[i+PAIRED_READ_SPACE+Length]);
						ReadRegion_Mu[i+PAIRED_READ_SPACE+Length] = c;
					}
					////
				} else if (CurrentVariation == VariantTypeInsertion) {
					char var_c = FindVariant(ReadRegion_Mu[i]);
					string var_str = "";
					var_str.insert(0, 1, var_c);
					//cout<<"Variant: Insert "<<var_str<<endl;
					ReadRegion_Mu.insert(i, var_str);
					//Add to paired end
					if (outputformat.compare("pair-mu")==0)
					{
						var_c = FindVariant(ReadRegion_Mu[i+PAIRED_READ_SPACE+Length]);
						string var_str = "";
						var_str.insert(0, 1, var_c);
						ReadRegion_Mu.insert(i+PAIRED_READ_SPACE+Length, var_str);
					}
					////
				} else if (CurrentVariation == VariantTypeDeletation) {
					//cout <<"Deletion selected"<<endl;
					ReadRegion_Mu.erase(i);
					if (outputformat.compare("pair-mu")==0)
					{
						ReadRegion_Mu.erase(i+PAIRED_READ_SPACE+Length);
					}
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
	cout<<"Outputformat :"<<outputformat<<endl;
	if (outputformat.compare("fasta")==0)
	{
		for (int i = 0; i < TotalReads; i++) {

			read_end += Length;
			outputFile << ">" << prefix<< Iteration++ << "." << startindex+chr.length()+ read_start << "."
					<<startindex+chr.length()+ read_end << endl;
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
	}
	else if (outputformat.compare("fastq")==0)
	{
		cout<<"is fastq with quality" <<ReadQuality<< endl;
		for (int i = 0; i < TotalReads; i++) {

			read_end += Length;
			outputFile << "@" <<prefix << Iteration++ << "." << startindex+chr.length()+read_start << "."
					<< startindex+chr.length()+read_end << endl;
			string ReadData = "";
			if (NumberOfMutatedReads-- > 0) {
				//cout<<"Applying mutation"<<endl;
				ReadData = ReadRegion_Mu.substr(read_start, Length);
			} else {
				ReadData = ReadRegion.substr(read_start, Length);

			}

			cout << "Generating Read..." << ReadData << endl;

			outputFile << ReadData << endl;
			outputFile << "+" << endl;
			string Quality=GenerateQualityForRead(ReadData,ReadQuality);
			outputFile << Quality << endl;
			read_start += Steps;
		}
	}
	else if (outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
	{
		cout <<"--------IS PAAAAAIR"<<endl;
		ofstream outputFile2(output_paired);

		cout<<"is fastq with quality" <<ReadQuality<< endl;
		for (int i = 0; i < TotalReads; i++) {
			read_end += Length;

			outputFile << "@" << prefix<< Iteration << "." << read_start+startindex+chr.length() << "."
					<< startindex+chr.length()+read_end <<"_1"<< endl;

			outputFile2 << "@" << prefix<< Iteration++ << "." << read_start+startindex+chr.length() << "."
					<< startindex+chr.length()+read_end <<"_2" <<endl;


			string ReadData = "";
			string ReadData_paired = "";
			if (NumberOfMutatedReads-- > 0) {
				//cout<<"Applying mutation"<<endl;
				ReadData = ReadRegion_Mu.substr(read_start, Length);
				ReadData_paired=ReadRegion_Mu.substr(read_start+Length+PAIRED_READ_SPACE, Length);
				//cout<<"ORG Start :"<<read_start<<"END:"<<read_start+Length<<endl;
				//cout<<"MUT Start :"<<read_start+Length+PAIRED_READ_SPACE<<"END:"<<read_start+Length+PAIRED_READ_SPACE+Length<<endl;
			} else {
				ReadData = ReadRegion.substr(read_start, Length);
				ReadData_paired=ReadRegion.substr(read_start+Length+PAIRED_READ_SPACE, Length);
			}

			cout << "Generating Read..." << ReadData << endl;

			outputFile << ReadData << endl;

			//outputFile2<<ReadData_paired<<endl;
			ReadData_paired=ReverseComplement(ReadData_paired);
			outputFile2<<ReadData_paired<<endl;

			outputFile << "+" << endl;
			outputFile2 << "+" << endl;

			string Quality=GenerateQualityForRead(ReadData,ReadQuality);
			outputFile << Quality << endl;
			outputFile2 << Quality << endl;
			read_start += Steps;
		}
		outputFile2.close();
	}

	outputFile.close();


}
long lastrandom=0;
string* GenerateNonOverLappingRandomSingleRead(string* Patterns,int RegionNumber,string chr,long PosStart,long PosEnd,int Length,string outputformat,string FAddress)
{
	///Select Read
	string ReadRegion="";
	while (true) {
		long CenterIndex=0;
		while(true)
		{
		long newrandom = LongRandom(PosStart + Length / 2,
				PosEnd - Length / 2);
			if (newrandom!=lastrandom)
			{
				lastrandom=newrandom;
				CenterIndex=newrandom;
				break;
			}
		}

		int PotentialStartPos = CenterIndex - Length / 2;
		int extraspace=0;
		if (outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
			extraspace=PAIRED_READ_SPACE+Length;
		ReadRegion = ReadPosition(chr, PotentialStartPos,
				PotentialStartPos + Length+extraspace+Length*6 /50, FAddress);
		ReadRegion=RemoveCharFromString('\n', ReadRegion);
		ReadRegion=ReadRegion.substr(0,Length+extraspace);
		if (ReadRegion[0] == 'N'
				|| ReadRegion[ReadRegion.length() - 1] == 'N') {
			cout << "Un acceptable region :" << ReadRegion << " PosStart:"
					<< PotentialStartPos << endl;
		} else {
			cout << "region found :" << ReadRegion << endl;
			break;
		}
	}

	//Apply Mutation

	ReadRegion=RemoveCharFromString('\n', ReadRegion);
	string ReadRegion_Mu = RemoveCharFromString('\n', ReadRegion);
	int CC = 0;
	int FirstPatternIndex=0;
	int RegionIterator = 0;
	string CurrentRegionValue = Patterns[0];
	int ApplyMutationDirection=0;  ///0 =Left to right, 1=Right to left , 2=Center
	int StartIndex=0,EndIndex=Length;

	if (CurrentRegionValue[0]=='l' )
	{
		ApplyMutationDirection=0;
		FirstPatternIndex=1;
		CurrentRegionValue=Patterns[FirstPatternIndex];
		StartIndex=0;
		EndIndex=Length;
	}
	else if (CurrentRegionValue[0]=='r' )
	{
		ApplyMutationDirection=1;
		FirstPatternIndex=1;
		CurrentRegionValue=Patterns[FirstPatternIndex];
	}
	else if (CurrentRegionValue[0]=='c' )
	{
		ApplyMutationDirection=2;
		CurrentRegionValue=Patterns[FirstPatternIndex];

	}

	///////Calculate Pattern Length
	int PatternLength=CalculatePatternLength(Patterns,RegionNumber);
	if (ApplyMutationDirection==1 )//Right to left
	{
		StartIndex=Length-PatternLength;
	}
	else if (ApplyMutationDirection==2 )//Center
	{
		StartIndex=Length/2-PatternLength/2-1;
	}
	else
	{
		StartIndex=0;
	}

	EndIndex=StartIndex+Length;
	if (EndIndex>StartIndex+PatternLength)
		EndIndex=StartIndex+PatternLength;

	cout <<"Pattern Length:"<<PatternLength<<" With Direction:"<<ApplyMutationDirection<<endl;
	cout <<"Start Index:"<<StartIndex<<" end index:"<<EndIndex<<"Length:"<<Length<<endl;

	VariantType CurrentVariation=GetVariantType(CurrentRegionValue[0]);
	CurrentRegionValue=CurrentRegionValue.substr(1,CurrentRegionValue.length()-1);
	int CurrentRegionIndex = 0;

	for (int i = StartIndex; i < EndIndex; i++) {
		cout <<"i="<<i<<"CC" <<CC<<endl;
		if (CurrentRegionIndex >=stoi( CurrentRegionValue)) {
			RegionIterator++;
			CurrentRegionIndex = 0;
			CurrentRegionValue = Patterns[RegionIterator];
			CurrentVariation=GetVariantType(CurrentRegionValue[0]);
			CurrentRegionValue=CurrentRegionValue.substr(1,CurrentRegionValue.length()-1);
		}
		if (CC++ >= PatternLength)
			break;
		cout <<"PASS CC"<<CC<<endl;
		if (CurrentVariation!=VariantTypeNone) {

			//cout<<"EXEC: ITER:"<<RegionIterator<< "Index:"<< CurrentRegionIndex<<"Value:"<<CurrentRegionValue <<endl;
			if (CurrentVariation == VariantTypeSubstitution) {
				char c = FindVariant(ReadRegion_Mu[i]);
				//cout <<"Variant: Substitution at"<<Length-1<< " Original:"<<ReadRegion_Mu[Length-1]<<" New value:" <<c<<endl;
				ReadRegion_Mu[i] = c;

				//Add to paired end
				if (outputformat.compare("pair-mu")==0)
				{
					char c = FindVariant(ReadRegion_Mu[i+PAIRED_READ_SPACE+Length]);
					ReadRegion_Mu[i+PAIRED_READ_SPACE+Length] = c;
				}
				////
			} else if (CurrentVariation == VariantTypeInsertion) {
				char var_c = FindVariant(ReadRegion_Mu[i]);
				string var_str = "";
				var_str.insert(0, 1, var_c);
				//cout<<"Variant: Insert "<<var_str<<endl;
				ReadRegion_Mu.insert(i, var_str);
				//Add to paired end
				if (outputformat.compare("pair-mu")==0)
				{
					var_c = FindVariant(ReadRegion_Mu[i+PAIRED_READ_SPACE+Length]);
					string var_str = "";
					var_str.insert(0, 1, var_c);
					ReadRegion_Mu.insert(i+PAIRED_READ_SPACE+Length, var_str);
				}
				////
			} else if (CurrentVariation == VariantTypeDeletation) {
				//cout <<"Deletion selected"<<endl;
				ReadRegion_Mu.erase(i);
				if (outputformat.compare("pair-mu")==0)
				{
					ReadRegion_Mu.erase(i+PAIRED_READ_SPACE+Length);
				}
			}
		}
		CurrentRegionIndex++;
		//cout <<"With mutations:"<<NumberOfMutatedReads<<endl;
	}
	cout<<"Original:"<<ReadRegion<<endl;
	cout<<"Mutation:"<<ReadRegion_Mu<<endl;

	string Read=ReadRegion_Mu.substr(0,Length);
	string Read_Pair="";
	if (outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
	{
		Read_Pair=ReadRegion_Mu.substr(ReadRegion_Mu.length()- Length,Length);
	}
	string Pair_Rc=ReverseComplement(Read_Pair);;
	cout <<"READ:"<<Read<<endl;
	cout <<"PAIR:"<<Read_Pair<<" Revers:"<<Pair_Rc <<endl;
	Read_Pair=Pair_Rc;
	string* Res=new string[2];
	Res[0]=Read;
	Res[1]=Read_Pair;



	////////
	return Res;

}
void GenerateNonOverlappingRandomReads(string* Patterns,int RegionNumber,string chr,long PosStart,long PosEnd, int TotalReads,
		int Length,string ReadQuality,int VariantPercentage, string FAddress,
		string output,string outputformat, bool isDebug)
{

	int NumberOfVariations= (TotalReads*VariantPercentage)/100;
	if (TotalReads%VariantPercentage!=0)//rounding up
		NumberOfVariations++;



	string output_paired=output;

		//OverlappingRegion : b=blank s=substution i=insertion d=deletion

		//cout << "Generating Region is :" << startindex << "-" << endindex
		//	<< "center is:" << CenterIndex << "OVERLAP SIZE:"<<overlapsize<< endl;
		string ReadRegion="";
		if (outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
		{
			for (int i=output.length()-1;i>=0;i--)
			{
				if (output[i]=='.')
				{
					output=output.insert(i,"_1");
					output_paired=output_paired.insert(i,"_2");
					break;
				}
			}
		}

		ofstream outputFile(output);
		ofstream outputFile_paired(output_paired);

	for (int i=0;i<=TotalReads;i++)
	{
		string *res=GenerateNonOverLappingRandomSingleRead( Patterns, RegionNumber, chr, PosStart, PosEnd, Length, outputformat, FAddress);
		if (NumberOfVariations-->0)
			res=GenerateNonOverLappingRandomSingleRead( Patterns, RegionNumber, chr, PosStart, PosEnd, Length, outputformat, FAddress);
		else
			res=GenerateNonOverLappingRandomSingleRead( Patterns, 0, chr, PosStart, PosEnd, Length, outputformat, FAddress);

		outputFile<<"READ "<<i<<endl;
		outputFile<<res[0]<<endl;
		if(outputformat.compare("pair")==0 || outputformat.compare("pair-mu")==0)
		{
			outputFile_paired<<"READ "<<i<<endl;
			outputFile_paired<<res[1]<<endl;
		}
	}
	outputFile.flush();
	outputFile_paired.flush();
	outputFile.close();
	outputFile_paired.close();
	cout<<"File generated successfully."<<endl;


}
//Read Length = 0 means Random length
void GenerateReads(string prefix,string chr, int ReadsNumber, int ReadLength,string ReadQuality,
		int VariantPercentage, string FAddress,
		bool Overlap, string* OverLapAndSpaceRegion, int RegionNumber,
		string output,string outputformat, bool IsDebugMode) {


	//int overlappinglen = CalculatePatternLength(OverLapAndSpaceRegion,RegionNumber);



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

	if (Overlap)
	{
		cout<<"Generating Random WITH overlapping Reads..."<<endl;
		if (ReadLength == 0)	//Not same size reads
		{
			//GenerateOverlappedReads_RandomSize(ReadsNumber,CenterIndex,chr,FAddress);
		}
		else	//Reads with same size
		{
			long CenterIndex = 0;
			while (true) {
				CenterIndex = LongRandom(Pos_start + ReadLength / 2,
						Pos_end - ReadLength / 2);
				cout << endl << endl << "Randomm Center Number:" << CenterIndex	<< endl;

				int PotentialStartPos = CenterIndex - ReadLength / 2;
				int extraspace=0;
				if (outputformat.compare("pair")==0)
					extraspace=PAIRED_READ_SPACE+ReadLength;
				string ReadRegion = ReadPosition(chr, PotentialStartPos,
						PotentialStartPos + ReadLength+extraspace, FAddress);
				ReadRegion=RemoveCharFromString('\n', ReadRegion);

				if (ReadRegion[0] == 'N'|| ReadRegion[ReadRegion.length() - 1] == 'N') {
					cout << "Un acceptable region :" << ReadRegion << " PosStart:"
							<< PotentialStartPos << endl;
				}
				else {
					cout << "region found :" << ReadRegion << endl;
					break;
				}
			}
			GenerateOverlappedReads_ConstantSize(prefix,chr, ReadsNumber, ReadLength,ReadQuality,
					CenterIndex - ReadLength, CenterIndex + ReadLength + 2,
					CenterIndex, VariantPercentage, OverLapAndSpaceRegion,
					RegionNumber, FAddress, output,outputformat, IsDebugMode);
		}
	}
	else
	{
		cout<<"Generating Random non overlapping Reads..."<< endl;
		GenerateNonOverlappingRandomReads(OverLapAndSpaceRegion,RegionNumber,chr, Pos_start,Pos_end,  ReadsNumber,
				ReadLength,ReadQuality,VariantPercentage,  FAddress,
				output, outputformat,  IsDebugMode);

	}

}

//

