/*
 * ArgsProcessor.cpp
 *
 *  Created on: 13-06-2011
 *      Author: juanin
 */

#include "ArgsProcessor.h"

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
	vParams.push_back("-ot");
	vParams.push_back("-of");
	vParams.push_back("-i");
	vParams.push_back("-cut");
	vParams.push_back("-vorslcut");
	vParams.push_back("-hchicut");
	vParams.push_back("-hvorcut");
	vParams.push_back("-hdensity");
	vParams.push_back("-silent");
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
	// Chequear parametros
	bool exist = false;
	char suffix = ' ';
	for(int i = 1; i < argcount; i++){
		suffix = argvalues[i][0];
		exist = false;
		if(suffix == '-'){
			for(unsigned int s=0; s<vParams.size(); ++s)
				if(argvalues[i]==vParams.at(s)){
					exist = true;
					break;
				}
			if(!exist){
				cout << "Bad argument: " << argvalues[i] << endl;
				exit(EXIT_FAILURE);
			}
		}
	}

	// Procesar Argumentos
	for(int i = 1; i < argcount; i++){
		suffix = argvalues[i][0];
		stringstream tmp;
		string arg;
		tmp << argvalues[i];
		tmp >> arg;
		if(suffix == '-'){
			// Diametro || Peso || Output Tipe [Binary|Plain|Connect] || Output File
			// Corte para representar Solido o liquido. || Corte para Chi :S || Corte para Area de voronoi y particulas inexistentes
			if(!arg.compare("-d") || !arg.compare("-w") || !arg.compare("-ot") || !arg.compare("-of") || !arg.compare("-i")
				|| !arg.compare("-vorslcut") || !arg.compare("-hchicut") || !arg.compare("-hvorcut")){
				pc->addParam(argvalues[i],new Container(argvalues[i+1]));
				++i;continue;
			}
			// Cut Image Cortar: arriba, abajo, derecha, izquierda
			if(!arg.compare("-cut")){
				pc->addParam(argvalues[i],new Container(argvalues[i+1]));
				continue;
			}
			// High Density || Silencio, No debug
			if(arg.compare("-silent") || !arg.compare("-hdensity")){
				pc->addParam(argvalues[i],new Container());
				continue;
			}
		}
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

vector <string> ArgsProcessor::getKeys(){
	return pc->getKeys();
}

bool ArgsProcessor::hasKey(string key){
	bool ret = false;
	vector <string> currentKeys = pc->getKeys();
	for(unsigned int i=0; i<currentKeys.size(); ++i){
		if(currentKeys.at(i)==key){
			return true;
		}
	}
	return ret;
}

int ArgsProcessor::getArgAsInt(string key){
	void* data = pc->getData(key);
	int ret = atoi((char*)data);

	return ret;
}

double ArgsProcessor::getArgAsDouble(string key){
	void* data = pc->getData(key);
	double ret = atof((char*)data);

	return ret;
}

string ArgsProcessor::getArgAsString(string key){
	void* data = pc->getData(key);
	stringstream sret;
	string ret;

	sret << (char*)data;
	sret >> ret;

	return ret;
}
