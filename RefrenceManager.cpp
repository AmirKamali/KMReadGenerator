
#include <iostream>
#include <fstream>
#include <string>
#include <libgen.h>
#include <string.h>
#include <sstream>
#import "RefrenceManager.h"
using namespace std;
string GetFileDirectory(string FAddress)
{
	return FAddress.substr(0, FAddress.find_last_of("\\/"))+"/";
}
string GetFileName(string filepath)
{
	char *ff = const_cast<char*>(filepath.c_str());
	string filename = basename(ff);
	return filename;
}
inline bool FileExist(const std::string& name)
{
    ifstream file(name);
    if(!file)            // If the file was not found, then file is 0, i.e. !file=1 or true.
        return false;    // The file was not found.
    else                 // If the file was found, then file is non-0.
        return true;     // The file was found.
}
bool GenerateRefrenceIndex(string FAddress)
{
	string IndexFileAddress=FAddress+".kmdx";
	if (!FileExist(FAddress))
	{
		cout <<"Reference file not found"<<endl;
		return false;
	}
	if (FileExist(IndexFileAddress))
	{
		cout <<"index file found"<<endl;
		return true;
	}

	cout<<"Generating index file for :"<<FAddress<< endl;
	//Read file
	ifstream file(FAddress);
	string content;

	//Output index
	ofstream outputFile(FAddress+".kmdx");
bool InChromosom=false;
	while(file >> content)
	{

		//cout<<endl<<"SALAAAAAM."<<flush;
		//break;
		if (content.at(0)=='>')
		{
			cout << "Generating index for "<<content <<endl<<flush;
			long pos=((long)file.tellg()-(long)content.length());
			if (!InChromosom)
			{
				outputFile<< content <<"\t"<< pos ;
				InChromosom=true;
			}
			else
			{
				outputFile<<"\t"<< pos-1 <<endl<<flush;;
				InChromosom=false;
			}
		}
	}
	if (InChromosom)
	{

		//file.seekg (0, ios::end);
		long length = file.tellg();
		cout<<"Lengthhhh :"<<length<<endl;
		outputFile<<"\t"<<length<<flush;;
	}
	cout<<"CONTENT:"<<content;
	file.close();
	outputFile.close();
	return true;
}
long* GetReferenceBoundry(string chr,string FAddress)
{
	chr=">"+chr;
	bool RefrenceOK=GenerateRefrenceIndex(FAddress);
	if (!RefrenceOK)
	{
		long default_arr [2] = { 0,0};
		return default_arr;
	}
	string IndexFileAddress=FAddress+".kmdx";
	ifstream file(IndexFileAddress);
	string chr_l;
	long pos_start=0;
	long pos_end=0;
	while(file >> chr_l>>pos_start>>pos_end)
	{
		if (chr_l.compare(chr)==0)
		{
			break;
		}
	}
	file.close();
	long Res[2];
	Res[0]=pos_start;
	Res[1]=pos_end;
	if (pos_end==0)
	{
		cout <<"Chromosome not found or index file is not complete."<<endl;
	}
	else
	{
		cout <<"Chr boundry"<<pos_start<<"-"<<pos_end<<endl;
	}
	return Res;
}
void PrintChromosome(string chr, long Boundry[], string FAddress)
{
	long StartIndex=Boundry[0];
	long EndIndex=Boundry[1];
	ifstream file(FAddress);
	file.seekg(StartIndex,file.beg);
	string content;
	string ChrAddr=GetFileDirectory(FAddress)+chr+"."+ GetFileName(FAddress)+".fa";
	ofstream outputFile(ChrAddr);
	cout<<"Generating chromosome in range:"<<StartIndex<<"-"<<EndIndex<<endl;
	//outputFile<<"<chr21";
	while (file>>content && file.tellg()<=EndIndex)
	{
		//cout<<"1";
		outputFile<<content<<endl;
	}
	outputFile<<content<<endl;
	file.close();
	outputFile.close();
}
unsigned long LongRandom ()
{

	unsigned char MyBytes[4];
	unsigned long MyNumber = 0;
	unsigned char * ptr = (unsigned char *) &MyNumber;

	MyBytes[0] = rand() % 256; //0-255
	MyBytes[1] = rand() % 256; //256 - 65535
	MyBytes[2] = rand() % 256; //65535 -
	MyBytes[3] = rand() % 256; //16777216

	memcpy (ptr+0, &MyBytes[0], 1);
	memcpy (ptr+1, &MyBytes[1], 1);
	memcpy (ptr+2, &MyBytes[2], 1);
	memcpy (ptr+3, &MyBytes[3], 1);

	return(MyNumber);
}
string RemoveCharFromString(char c,string str)
{
	//cout <<endl<<"Data:"<<str.length()<<str<<endl;
	str.erase(std::remove(str.begin(), str.end(), c), str.end());
	return str;
}
string RemoveCharFromCharArray(char c,char arr[])
{

	    char Res[strlen(arr)];
	    int Xindex=0;
	    for(int i = 0; arr[i] != '\0'; i++)
	    {

	    	if(arr[i] != c)
	    	{
	    		Res[Xindex++]=arr[i];
	    	}
	    }
	    Res[Xindex]='\0';
	    Res[Xindex+1]='\n';
	    cout<<"After remove:"<<Res<<endl;
	    return Res;
}
string ReadPosition(string Chr,int StartIndex,int EndIndex,string FAddr)
{
		cout<<"Generating chromosome in range:"<<StartIndex<<"-"<<EndIndex<<endl;
		StartIndex+=Chr.length()+2;
		EndIndex+=Chr.length()+2;

		ifstream file(FAddr);
		file.seekg(StartIndex,file.beg);
		file.clear();
		string content;
		string Res="";
	    char * buffer = new char [EndIndex-StartIndex];
	    for (int i=0;i<EndIndex-StartIndex+1 ;i++)
	    {
	    	buffer[i]='\0';
	    }
	    file.read (buffer,EndIndex-StartIndex);

	    return buffer;
}

std::string ReplaceString(std::string subject, const std::string& search,
                          const std::string& replace) {
    size_t pos = 0;
    while((pos = subject.find(search, pos)) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
    return subject;
}
void GenerateOverlappedReads_RandomSize(int TotalReads,long CenterIndex,string chr,string FAddress)
{

}
int CountWhiteSpace(string str)
{
	int sum=0;
	for (int i=0;i<str.length();i++)
	{
		if (str[i]=='\n')
			sum++;
	}
	return sum;
}
char FindVariant(char c)
{
	//return 'X';
	if (c=='A' || c=='a')
		return 'C';
	else if (c=='T' || c=='t')
		return 'A';
	else if (c=='C' || c=='c')
		return 'G';
	else if (c=='G' || c=='g')
		return 'T';
	return c;
}

void GenerateOverlappedReads_ConstantSize(string chr, int TotalReads,int Length,long startindex,long endindex,long CenterIndex,VariantType variantT,int VariantPercentage,string FAddress,string output,bool isDebug)
{
	cout<<"Generating Region is :"<<startindex<<"-"<<endindex<<"center is:"<<CenterIndex<<endl;
	string ReadRegion=ReadPosition(chr,startindex,endindex,FAddress);
	ReadRegion=RemoveCharFromString('\n',ReadRegion);

	string ReadRegion_Mu="";

	int NumberOfMutatedReads=0;
	if (variantT!=VariantTypeNone)
	{
		NumberOfMutatedReads= (TotalReads*VariantPercentage)/100;
		ReadRegion_Mu=RemoveCharFromString('\n',ReadRegion);
		if (variantT==VariantTypeSubstitution)
		{

			char c=FindVariant(ReadRegion_Mu[Length-1]);
			cout <<"Variant: Substitution at"<<Length-1<< " Original:"<<ReadRegion_Mu[Length-1]<<" New value:" <<c<<endl;
			ReadRegion_Mu[Length-1]=c;
		}
		else if (variantT==VariantTypeInsertion)
		{
			char var_c=FindVariant(ReadRegion_Mu[Length-1]);
			string var_str="";
			var_str.insert(0,1,var_c);
			cout<<"Variant: Insert "<<var_str<<endl;
			ReadRegion_Mu.insert(Length-1,var_str);
		}
		else if (variantT==VariantTypeDeletation)
		{
			cout <<"Deletion selected"<<endl;
			ReadRegion_Mu.erase(Length-1,1);
		}

		cout <<"With mutations:"<<NumberOfMutatedReads<<endl;
	}
	else
		cout <<"Variation: None"<<endl;


	int FramesNumber=Length;

	if (TotalReads>FramesNumber)
	{
		cout << "Reference is too short for the number of reads"<<endl;
		return;
	}
	cout<<"Frame numbers:"<<FramesNumber<<endl;
	//string ChrAddr=outp//GetFileDirectory(FAddress)+"Reads_"+"x"+"."+ GetFileName(FAddress)+".fa";
	ofstream outputFile(output);
	if (isDebug)
	{
		outputFile<<ReadRegion<<endl;
		outputFile<<ReadRegion_Mu<<endl<<endl;
	}
	int Steps=FramesNumber/TotalReads;
	int Iteration=1;
	int read_start=0;
	int read_end=0;
	cout<<"Steps::"<<Steps<<endl;
	for (int i=0;i<TotalReads;i++)
	{

		read_end+=Length;
		outputFile<<">"<<"Read"<<Iteration++<<"."<<read_start<<"."<<read_end<< endl;
		string ReadData="";
		if (NumberOfMutatedReads-->0)
		{
			//cout<<"Applying mutation"<<endl;
			ReadData=ReadRegion_Mu.substr(read_start,Length);
		}
		else
		{
		  ReadData=ReadRegion.substr(read_start,Length);

		}

		cout<<"Generating Read..."<< ReadData<<endl;

		outputFile<<ReadData<<endl;
		read_start+=Steps;
	}

	outputFile.close();

}

//Read Length = 0 means Random length
void GenerateReads(string chr,int ReadsNumber,int ReadLength, VariantType variantT,int VariantPercentage,string FAddress,bool Overlap,string output,bool IsDebugMode)
{
    const int ReadLength_MaxRandom=220;
	long* Boundries=GetReferenceBoundry(chr,FAddress);
	long Pos_start=Boundries[0];
	long Pos_end=Boundries[1];
	if (Pos_end==0)
		return;
	//Check Space for Randoms
	if (ReadLength==0 && Pos_end-Pos_start<450)
	{
		cout << "Not enough space for generating random reads. For random reads minimum length of the reference should be 220"<<endl;
		return;
	}
	if (Pos_end-Pos_start<2*ReadLength+1)
	{
		cout << "Not enough space for generating reads. For generating random reads "<<endl;
      return;
	}
	int MaxReadLength=ReadLength;
	if (MaxReadLength==0)
		MaxReadLength=ReadLength_MaxRandom;

	//Finding Center (overlap index)
	long Center_Boundry_Start=MaxReadLength+MaxReadLength/50;
	long Center_Boundry_End=Pos_end-(MaxReadLength+MaxReadLength/50);

	//long CenterIndex = Center_Boundry_Start+ LongRandom()% (Center_Boundry_End-Center_Boundry_Start);
	long CenterIndex=100;
	cout <<"Center Start:"<<MaxReadLength<<"-"<<Center_Boundry_End <<" centerindex:"<<CenterIndex<<endl;

	if (Center_Boundry_Start>=Center_Boundry_End)
	{
		cout <<"Error in finding boundries"<<endl;
		return;
	}
	if (ReadLength==0)
	{
		//GenerateOverlappedReads_RandomSize(ReadsNumber,CenterIndex,chr,FAddress);
	}
	else
	{
		GenerateOverlappedReads_ConstantSize(chr, ReadsNumber,ReadLength,CenterIndex-ReadLength,CenterIndex+ReadLength+2,CenterIndex,variantT,VariantPercentage,FAddress,output,IsDebugMode);
	}


}

//

