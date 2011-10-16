/*
 * Output.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "Output.h"

OutputType Output::translate(string out){
	MyLogger::log()->debug("[Output][translate] Translating string Output type: %s", out.c_str());
	OutputType ret = Standar_out;

	if(out.compare("-out") == 0){
		MyLogger::log()->debug("[Output][translate] Translated to: Plain Output");
		ret = Plain_out;
	}
	if(out.compare("-outbin") == 0){
		MyLogger::log()->debug("[Output][translate] Translated to: Binary Output");
		ret = Binary_out;
	}
	if(out.compare("-outcon") == 0){
		MyLogger::log()->debug("[Output][translate] Translated to: Connector Output");
		ret = Connector_out;
	}

	return ret;
}

void Output::writeData(vector<MyPeak> *peaks, string file){
	MyLogger::log()->error("[Output][writeData] Output type not implemented, please implement this function");
}
