/*
 * BinaryOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "BinaryOutput.h"

void BinaryOutput::writeData(vector<MyPeak> *peaks, string file){
	MyLogger::log()->debug("[BinaryOutput][writeData] Writing output file: %s", file.c_str());
	ofstream myfile;
	myfile.open(file.c_str(), ios_base::out | ios_base::binary);
	if(!myfile){
		MyLogger::log()->error("[BinaryOutput][writeData] Cannot open file %s", file.c_str());
		return;
	}
	double solid = 0.0;
	double liquid = 1.0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		myfile.write(reinterpret_cast<char*>(&peaks->at(i).px), sizeof(double));
		myfile.write(reinterpret_cast<char*>(&peaks->at(i).py), sizeof(double));
		if(peaks->at(i).solid)
			myfile.write(reinterpret_cast<char*>(&solid), sizeof(double));
		else
			myfile.write(reinterpret_cast<char*>(&liquid), sizeof(double));
	}
	myfile.close();
	MyLogger::log()->debug("[BinaryOutput][writeData] Output file written");
}
