
#include <iostream>
#include <fstream>
#include <string>
#include <libgen.h>
#include <string.h>

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
void GenerateRefrenceIndex(string FAddress)
{
	string IndexFileAddress=FAddress+".kmdx";
	if (FileExist(IndexFileAddress))
	{
		return;
	}
	//Read file
	ifstream file(FAddress);
	string content;

	//Output index
	ofstream outputFile(FAddress+".kmdx");
	while(file >> content)
	{
		if (content.at(0)=='>')
		{
			cout << "Generating index for "<<content <<endl<<flush;
			long pos=((long)file.tellg()-(long)content.length());
			outputFile<< content <<"\t"<< pos <<endl<<flush;
		}
	}
	file.close();
	outputFile.close();
}
long* GetReferenceBoundry(string chr,string FAddress)
{
	chr=">"+chr;
	GenerateRefrenceIndex(FAddress);
	string IndexFileAddress=FAddress+".kmdx";
	ifstream file(IndexFileAddress);
	string chr_l;
	long pos_start=0;
	long pos_end=0;
	while(file >> chr_l>>pos_start)
	{
		if (chr_l.compare(chr)==0)
		{
			cout <<"hahaa:"<<chr_l<<" With pos:"<< pos_start<<endl;
			file>>chr_l>>pos_end;
			pos_end-=chr_l.length();
			break;
		}
	}
	file.close();
	long Res[2];
	Res[0]=pos_start;
	Res[1]=pos_end;
	if (pos_end==0)
	{
		cout <<"Chromosome not found or index file is not complete.";
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
void GenerateRandomReads(int ReadsNumber,string FAddress,bool Overlap)
{

}
//

