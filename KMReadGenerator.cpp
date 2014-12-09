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
	//dd=ReadReference(1);
	res=GetReferenceBoundry("chrM",RefAdr);
	PrintChromosome("chrM",res, RefAdr);
	return 0;
}
