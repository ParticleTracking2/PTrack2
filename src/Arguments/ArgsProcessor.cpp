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
	currentAlgorithmType = None_Algorithm;
	currentOutputType = Standar_out;

	/**
	 *************************
	 * Argumentos para Chi2
	 *************************
	 */
	ArgObj chi2;
	chi2.type = Chi2_Algorithm;

	/* Parametros aceptables */
	KeyTreat img; img.key = "-i";
	img.treat.push_back(Require_Treat);
	img.treat.push_back(Followed_String_Treat);
	chi2.keys_treats.push_back(img);

	KeyTreat d; d.key = "-d";
	d.treat.push_back(Require_Treat);
	d.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(d);

	KeyTreat w; w.key = "-w";
	w.treat.push_back(Require_Treat);
	w.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(w);

	vParams.push_back(chi2);

	/**
	 *************************
	 * Argumentos para Chi2HD
	 *************************
	 */
	ArgObj chi2hd;
	chi2hd.type = Chi2HD_Algorithm;

	/* Parametros aceptables */
	chi2hd.keys_treats.push_back(img);
	chi2hd.keys_treats.push_back(d);
	chi2hd.keys_treats.push_back(w);

	vParams.push_back(chi2hd);

	/**
	 *************************
	 * Parametros generales
	 *************************
	 */
	KeyTreat silent; silent.key = "-silent";
	silent.treat.push_back(Exist_Treat);

	KeyTreat debug; debug.key = "-debug";
	debug.treat.push_back(Exist_Treat);

	KeyTreat debugwf; debugwf.key = "-debugwf";
	debugwf.treat.push_back(Exist_Treat);

	KeyTreat chrono; chrono.key = "-chrono";
	chrono.treat.push_back(Exist_Treat);

	KeyTreat out; out.key = "-out";
	out.treat.push_back(Output_Treat);
	out.treat.push_back(Followed_String_Treat);

	KeyTreat outb; outb.key = "-outbin";
	outb.treat.push_back(Output_Treat);
	outb.treat.push_back(Followed_String_Treat);

	KeyTreat outc; outc.key = "-outcon";
	outc.treat.push_back(Output_Treat);
	for(unsigned int i=0; i < vParams.size(); ++i){
		vParams.at(i).keys_treats.push_back(silent);
		vParams.at(i).keys_treats.push_back(debug);
		vParams.at(i).keys_treats.push_back(debugwf);
		vParams.at(i).keys_treats.push_back(chrono);
		vParams.at(i).keys_treats.push_back(out);
		vParams.at(i).keys_treats.push_back(outb);
		vParams.at(i).keys_treats.push_back(outc);
	}

//	vParams.push_back("-ot");
//	vParams.push_back("-of");
//	vParams.push_back("-debug");
//	vParams.push_back("-debugWF");
//	vParams.push_back("-chrono");
//	vParams.push_back("-cut");
//	vParams.push_back("-vorslcut");
//	vParams.push_back("-hchicut");
//	vParams.push_back("-hvorcut");
//	vParams.push_back("-hdensity");
//	vParams.push_back("-silent");
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
int ArgsProcessor::find(string key, int argcount, char* argvalues[]){
	int position = -1;

	for(int i=0; i < argcount; ++i){
		if(key.compare(toLowerCase(argvalues[i]))==0){
			position = i;
			break;
		}
	}

	return position;
}

string ArgsProcessor::toLowerCase(char *str){
	string copy;
	for(unsigned int i=0; str[i]; ++i){
		copy.insert(copy.end(), tolower(str[i]));
	}
	return copy;
}

void ArgsProcessor::toLowerCase(string &str){
	for(unsigned int i=0; i < str.length(); ++i){
		str.at(i) = tolower(str.at(i));
	}
}

void ArgsProcessor::checkArgs(ArgObj *currentArgs, int argcount, char* argvalues[]){
	bool found;
	for(int i=2; i < argcount; ++i){
		if(argvalues[i][0] == '-'){
			found = false;
			for(unsigned int ai=0; ai < currentArgs->keys_treats.size(); ++ai){
				if(currentArgs->keys_treats.at(ai).key.compare(toLowerCase(argvalues[i])) == 0){
					found = true;
					break;
				}
			}
			if(!found){
				MyLogger::log()->warn("[ArgsProcessor][checkArgs] Unknown argument: %s", argvalues[i]);
			}
		}
	}
}

void ArgsProcessor::setArgs(int argcount, char* argvalues[]){
	// Chequear primer argumento => Tipo de algoritmo
	if(argcount < 2){
		MyLogger::log()->error("[ArgsProcessor][setArgs] No Algorithm Selected");
		exit(EXIT_FAILURE);
	}

	string alg_str = argvalues[1];
	toLowerCase(alg_str);
	currentAlgorithmType = Algorithm::translate(alg_str);
	if(currentAlgorithmType == None_Algorithm){
		MyLogger::log()->error("[ArgsProcessor][setArgs] No Algorithm Selected: %s", alg_str.c_str());
		exit(EXIT_FAILURE);
	}

	// Obtener argumentos del algoritmo
	ArgObj currentArgsObj;
	bool arglist = false;
	for(unsigned int i=0; i < vParams.size(); ++i){
		if(vParams.at(i).type == currentAlgorithmType){
			currentArgsObj = vParams.at(i);
			arglist = true;
			break;
		}
	}

	checkArgs(&currentArgsObj, argcount, argvalues);

	if(!arglist){
		MyLogger::log()->error("[ArgsProcessor][setArgs] Algorithm without Arguments stablished");
		exit(EXIT_FAILURE);
	}

	// Chequear parametros
	vector<KeyTreat> currentArgs = currentArgsObj.keys_treats;

	// Por cada llave posible del algoritmo
	for(unsigned int ai=0; ai < currentArgs.size(); ++ai){

		KeyTreat currentKey = currentArgs.at(ai);
		// Dentro de cada tratamiento posible
		bool require = false;
		int currentArgPosition = find(currentKey.key, argcount, argvalues);
		for(unsigned int t=0; t < currentKey.treat.size(); ++t){
			switch (currentKey.treat.at(t)) {
				case Require_Treat:
					// Debe existir la posicion
					if(currentArgPosition == -1){
						MyLogger::log()->error("[ArgsProcessor][setArgs] Required Argument not found: %s", currentKey.key.c_str());
						exit(EXIT_FAILURE);
					}
					require = true;
					break;
				case Followed_Double_Treat:
					// Buscar el siguiente parametro para retornarlo como double
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1])
							pc->addParam(currentKey.key, new Container(atof(argvalues[currentArgPosition+1])));
						else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Followed_Int_Treat:
					// Buscar el siguiente parametro para retornarlo como Integer
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1])
							pc->addParam(currentKey.key, new Container(atoi(argvalues[currentArgPosition+1])));
						else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Followed_String_Treat:
					// Buscar el siguiente parametro para retornarlo como String
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1])
							pc->addParam(currentKey.key, new Container(argvalues[currentArgPosition+1]));
						else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Exist_Treat:
					// Solamente debe existir
					if(currentArgPosition != -1){
						pc->addParam(currentKey.key, new Container(argvalues[currentArgPosition]));
					}
					break;
				case Output_Treat:
					// Se asume que sigue con algun parametro tipo string
					if(currentArgPosition != -1){
						currentOutputType = Output::translate(toLowerCase(argvalues[currentArgPosition]));
					}
					break;
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
	return pc->getParamAsInt(key);
}

double ArgsProcessor::getArgAsDouble(string key){
	return pc->getParamAsDouble(key);
}

string ArgsProcessor::getArgAsString(string key){
	return pc->getParamAsString(key);
}

ParameterContainer *ArgsProcessor::getContainer(){
	return pc;
}

AlgorithmType ArgsProcessor::getAlgorithmType(){
	return currentAlgorithmType;
}

OutputType ArgsProcessor::getOutputType(){
	return currentOutputType;
}
