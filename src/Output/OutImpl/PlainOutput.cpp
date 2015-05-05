/*
 * PlainOutput.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "PlainOutput.h"

void PlainOutput::writeData(vector<MyPeak> *peaks, string file){
	MyLogger::log()->debug("[PlainOutput][writeData] Writing output file");
	ofstream myfile;
	myfile.open(file.c_str());
	myfile << fixed;
	for(unsigned int i=0; i < peaks->size(); ++i){
		myfile << peaks->at(i).px << "\t" << peaks->at(i).py << "\t" << peaks->at(i).vor_area << endl;
	}
	myfile.close();
	MyLogger::log()->debug("[PlainOutput][writeData] Output file written");
}
