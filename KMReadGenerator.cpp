//============================================================================
// Name        : KMReadGenerator.cpp
// Author      : AmirHossein Kamali
// Version     :
// Copyright   : This project is part of a study in Victor Chang Cardiac Institue
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "RefrenceManager.h"
using namespace std;

//int* ReadReference(int a);
void ReadKeys(int argc, char* argv[])
{
	string RefAdr="";
	string Output="";
	string Chr="chrM";
	int ReadsNum=10;
	bool IsDebugMode=false;
	int ReadsLength=100;
	VariantType Variation=VariantTypeNone;
	int VariationPercentage=50;
	bool overlap=true;

	 if (argc < 3) { // Check the value of argc. If not enough parameters have been passed, inform user and exit.
	        std::cout << "Usage is -r <refrence>  -o <output>"<<endl<<endl; // Inform the user of how to use the program
	    } else { // if we got enough parameters...
	        char* myFile, myPath, myOutPath;
	        std::cout << argv[0];
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
	                	cout <<"xxxxxxok output is :"<<endl;
	               	     Output = argv[i + 1];

	               	}
	                else if (strcmp(argv[i] , "-debug")==0)
	                {

	               	     IsDebugMode = stoi(argv[i + 1]);

	               	}
	                else if (strcmp(argv[i],"-v")==0)
	                {
	                	//cout <<"Variation key";
	                	if (strcmp(argv[i+1],"s")==0)
	                		Variation=VariantTypeSubstitution;
	                	else if (strcmp(argv[i+1],"i")==0)
	                		Variation=VariantTypeInsertion;
	                	else if (strcmp(argv[i+1],"d")==0)
	                		Variation=VariantTypeDeletation;
	                	else if (strcmp(argv[i+1],"n")==0)
	                		Variation=VariantTypeNone;
	                }
	                else if (strcmp(argv[i] , "-vp")==0)
	             	 {
	                	VariationPercentage =stoi( argv[i + 1]);

	             	 }
	                else {
	                    std::cout << "Not enough or invalid arguments, please try again."<<endl;
	                    std::cout <<"PARAMETERS:"<< argv[i] << " "<<endl;
	                   // Sleep(2000);
	                    //exit(0);
	            }

	        }
	        //... some more code
	        //std::cin.get();
	       // return 0;
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
	 //cout <<"Preparing with Ref:"<<RefAdr<<endl<<"Output"<<Output<<endl;
	 GenerateReads(Chr,ReadsNum,ReadsLength,Variation,VariationPercentage,RefAdr,overlap,Output,IsDebugMode);
}

int main(int argc, char* argv[]) {
	cout <<endl<< "Random Read Generator initializing" << endl;
	ReadKeys(argc,argv);
	return 0;
}
