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

int main() {
	cout << "Random Read Generator initializing" << endl; // prints !!!Hello World!!!
	string RefAdr="/Users/Amir/Desktop/GATK/EXP/GATK\ Testing\ Scripts/Reference/hg19/ucsc.hg19.txt";
	long* res;
	cout <<"XXXxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	cout <<"XXXxxxxxxxxxxxxxxxSTARTxxxxxxxxxxxxxxxxxxxxxxxx";
	//dd=ReadReference(1);
	//res=GetReferenceBoundry("chrM",RefAdr);
	//PrintChromosome("chrM",res, RefAdr);
	//GenerateReads("chrM",10,100,VariantTypeInsertion,50,RefAdr,true);
	GenerateReads("chrM",10,100,VariantTypeDeletation,50,RefAdr,true);
	return 0;
}
