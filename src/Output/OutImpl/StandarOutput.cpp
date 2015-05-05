/*
 * StandarOutput.cpp
 *
 *  Created on: 13/10/2011
 *      Author: ptrack
 */

#include "StandarOutput.h"

void StandarOutput::writeData(vector<MyPeak> *peaks, string file){
	MyLogger::log()->notice("[StandarOutput][writeData] Writing output file");
	cout << fixed;
	for(unsigned int i=0; i < peaks->size(); ++i){
		cout << peaks->at(i).px << "\t" << peaks->at(i).py << "\t" << peaks->at(i).vor_area << endl;
	}
	MyLogger::log()->notice("[StandarOutput][writeData] Output file written");
}
