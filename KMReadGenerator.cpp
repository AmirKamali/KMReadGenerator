//============================================================================
// Name        : KMReadGenerator.cpp
// Author      : AmirHossein Kamali
// Version     :
// Copyright   : This project is part of a study in Victor Chang Cardiac Institue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "RefrenceManager.h"
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <boost/tokenizer.hpp>


using namespace std;
using namespace boost;


//int* ReadReference(int a);
void ReadKeys(int argc, char* argv[])
{
	string RefAdr="";
	string Output="";
	string Chr="chrM";
	string ReadQuality="h";
	string OutputFormat="fasta";
	string Prefix="Read_";
	int ReadsNum=10;
	bool IsDebugMode=false;
	string SampleVariationPattern[1]={"s1"};
	string *OverLapAndSpaceRegion=SampleVariationPattern;

	int RegionNumber=0;
	int ReadsLength=100;
	int VariationPercentage=50;
	bool overlap=true;

	 if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
	        std::cout << "Usage is -r <refrence>  -o <output>"<<endl<<endl; // Inform the user of how to use the program
	    } else { // if we got enough parameters...

	        for (int i = 1; i < argc; i+=2) { /* We will iterate over argv[] to get the parameters stored inside.
	                                          * Note that we're starting on 1 because we don't need to know the
	                                          * path of the program, which is stored in argv[0] */
	            if (i + 1 != argc) // Check that we haven't finished parsing already
	                if (strcmp(argv[i] ,"-r")==0) {
	                    // We know the next argument *should* be the filename:
	                    RefAdr = argv[i + 1];
	                }
	                else if (strcmp(argv[i] , "-n")==0) {
	                    ReadsNum = stoi( argv[i + 1]);
	                }
	                else if (strcmp(argv[i], "-l")==0) {
	                    ReadsLength = stoi(argv[i + 1]);
	                }
	                else if (strcmp(argv[i] , "-o")==0)
	                {
	               	     Output = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-of")==0)// Outputformat
	                {
	               	     OutputFormat = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-chr")==0)
	                {
	               	     Chr = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-pfx")==0)
	                {
	               	     Prefix = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-debug")==0)
	                {

	               	     IsDebugMode = stoi(argv[i + 1]);

	               	}
	                else if (strcmp(argv[i] , "-rq")==0)
	                {

	               	     ReadQuality = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-ol")==0)
	   	            {

	                	overlap = stoi(argv[i + 1]);

	   	            }
	                else if (strcmp(argv[i] , "-vp")==0)
	             	 {
	                	VariationPercentage =stoi( argv[i + 1]);

	             	 }
	                else if (strcmp(argv[i] , "-vpt")==0)
	             	 {
	                	//Overlapping_Lenk =stoi( argv[i + 1]);


	                    string text = argv[i + 1];

	                    char_separator<char> sep("-");
	                    tokenizer<char_separator<char> > tokens(text, sep);
	                    int TokenCount=0;
	                    for (const auto& t : tokens) {
	                    	TokenCount++;
	                        //cout << t << "." << endl;
	                    }
	                    RegionNumber=TokenCount;

	                    OverLapAndSpaceRegion= new string[TokenCount]; //
	                    TokenCount=0;
	                    for (const auto& t : tokens)
	                    {
	                    	OverLapAndSpaceRegion[TokenCount++]=t;
	                    }
	             	 }
	                else {
	                    std::cout <<"Invalid PARAMETERS:"<< argv[i] << " "<<endl;
	            }

	        }
	    }
	 if (Output.length()==0)
	 {
		 cout <<"Output address is not specified."<<endl;
		 return;
	 }
	 else if (RefAdr.length()==0)
	 {
		 cout <<"Reference address is not specified."<<endl;
		 return;
	 }
	 else if (ReadsLength<3)
	 {
		 cout <<"Reads length can not be less than 3";
		 return;
	 }
	 else if (ReadsNum<1)
	 {
		 cout <<"Reads can not be less than 1";
		 return;
	 }
	 else if (VariationPercentage<0 || VariationPercentage>100)
	 {
		 cout <<"Variant percentage should fall in [0-100] range";
		 return;
	 }
	 //GenerateReads("1",2,2,VariantTypeSubstitution,10,"ss",true,0,0,"ss",true);
	 //string chr,
	 //int ReadsNumber
	 //,int ReadLength,
	 //int VariantPercentage,
	 //string FAddress,
	 //bool Overlap,
	 //int* OverLapAndSpaceRegion,
	 //int RegionNumber,
	 //string output,
	 //bool IsDebugMode);
	 if (!overlap)
		 cout<<"NON OVERLAPPP"<<endl;

	// cout <<"READ QUALITY:"<<ReadQuality<<endl;
	 GenerateReads(
			 Prefix,
			 Chr,
			 ReadsNum,
			 ReadsLength,
			 ReadQuality,
			 VariationPercentage,
			 RefAdr,
			 overlap,
			 OverLapAndSpaceRegion,
			 RegionNumber,
			 Output,
			 OutputFormat,
			 IsDebugMode);
}

int main(int argc, char* argv[]) {
	cout <<endl<< "Random Read Generator initializing" << endl;
	ReadKeys(argc,argv);
	//long int myarray[] = {41256422,41256498};
	//PrintChromosome("chr1",myarray,"/Users/Amir/Desktop/ref/ucsc.hg19.fasta");

	return 0;
}
