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
	//float solid = 1.0;
	//float liquid = 0.0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		float pex = (float)peaks->at(i).px;
		float pey = (float)peaks->at(i).py;
		float vor = (float)peaks->at(i).vor_area;
		myfile.write(reinterpret_cast<char*>(&pex), sizeof(float));
		myfile.write(reinterpret_cast<char*>(&pey), sizeof(float));
		myfile.write(reinterpret_cast<char*>(&vor), sizeof(double));
		//if(peaks->at(i).solid)
		//	myfile.write(reinterpret_cast<char*>(&solid), sizeof(float));
		//else
		//	myfile.write(reinterpret_cast<char*>(&liquid), sizeof(float));
	}
	myfile.close();
	MyLogger::log()->debug("[BinaryOutput][writeData] Output file written");
}
