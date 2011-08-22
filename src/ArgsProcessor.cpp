/*
 * ArgsProcessor.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "ArgsProcessor.h"

string ArgsProcessor::name() {
	return "ArgsProcessor";
}
/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
ArgsProcessor* ArgsProcessor::myInstance = 0;

ArgsProcessor::ArgsProcessor() {
	pc = new ParameterContainer();

	/* Parametros aceptables */
	vParams.push_back("-d");
	vParams.push_back("-w");
	vParams.push_back("-s");
	vParams.push_back("-b");
	vParams.push_back("-cutl");
	vParams.push_back("-cutr");
	vParams.push_back("-cutt");
	vParams.push_back("-cutd");
	vParams.push_back("-vorsl");
	vParams.push_back("-hdensity");
	vParams.push_back("-hchicut");
	vParams.push_back("-hvorcut");
}

ArgsProcessor::~ArgsProcessor() {
	vParams.clear();
	delete pc;
}

/**
 ******************************
 * Metodos
 ******************************
 */
void ArgsProcessor::setArgs(int argcount, char* argvalues[]){
	for(int i = 1; i < argcount; i++){
		char sufix = argvalues[i][0];
		switch(sufix){
			case '-':
				for(unsigned int s=0; s<vParams.size(); ++s){
					if(argvalues[i]==vParams.at(s)){
						pc->addParam(argvalues[i],new Container(argvalues[i+1]));
						++i;
						break;
					}
				}
				break;
			default:
				break;
		}
	}

	vector <string> currentKeys = pc->getKeys();
	for(unsigned int i=0; i<currentKeys.size(); ++i){
		cout << currentKeys.at(i) << ": " << (char*)pc->getData(currentKeys.at(i)) << endl;
	}
}

/**
 *******************************
 * Funciones
 *******************************
 */
ArgsProcessor *ArgsProcessor::getInstance(){
	if(!myInstance)
			myInstance = new ArgsProcessor();
		return myInstance;
}
