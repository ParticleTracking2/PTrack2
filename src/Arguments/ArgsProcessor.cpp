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

	vParams = AlgorithmExecutor::getAllArguments();

	/**
	 *************************
	 * Parametros generales
	 *************************
	 */
	KeyTreat silent; silent.key = "-silent"; silent.description = "Displays no text during process.";
	silent.treat.push_back(Exist_Treat);
	gParams.push_back(silent);

	KeyTreat debug; debug.key = "-debug"; debug.description = "Display major process status.";
	debug.treat.push_back(Exist_Treat);
	gParams.push_back(debug);

	KeyTreat debugwf; debugwf.key = "-debugwf"; debugwf.description = "Display major process status and write status files.";
	debugwf.treat.push_back(Exist_Treat);
	gParams.push_back(debugwf);

	KeyTreat chrono; chrono.key = "-chrono"; chrono.description = "Display starting and finishing status.";
	chrono.treat.push_back(Exist_Treat);
	gParams.push_back(chrono);

	KeyTreat out; out.key = "-out"; out.description = "Plain Text Output file.";
	out.treat.push_back(Output_Treat);
	out.treat.push_back(Followed_String_Treat);
	gParams.push_back(out);

	KeyTreat outb; outb.key = "-outbin"; outb.description = "Binary Output file.";
	outb.treat.push_back(Output_Treat);
	outb.treat.push_back(Followed_String_Treat);
	gParams.push_back(outb);

	KeyTreat nth; nth.key = "-nothreads"; nth.description = "Use no threads to calculate.";
	nth.treat.push_back(Exist_Treat);
	gParams.push_back(nth);

	KeyTreat dspl; dspl.key = "-display"; dspl.description = "Display Obtained Peaks into Image.";
	dspl.treat.push_back(Exist_Treat);
	gParams.push_back(dspl);
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
void ArgsProcessor::printHelp(){
	cout << "Primary use as: $ ptrack2 [Algorithm Type] [[Algorithm Argument] ..]" << endl;

	// Por cada algoritmo
	for(unsigned int i=0; i < myInstance->vParams.size(); ++i){
		printHelp(myInstance->vParams.at(i));
	}

	// Parametros generales
	printGeneralHelp();
}

void ArgsProcessor::printHelp(ArgObj currentArgs){
	ArgObj alg = currentArgs;
	cout << endl;
	cout << "Type:\t" << alg.argkey << endl;
	cout << "Description: " << alg.description << endl;
	cout << "Typical use: " << alg.example << endl;

	// Por cada argumento del algoritmo
	for(unsigned int ks=0; ks < alg.keys_treats.size(); ++ks){

		cout << "\t[" << alg.keys_treats.at(ks).key << "]\t";
		// Por cada opcion de tratamiento del argumento
		string treats = "";
		for(unsigned int tr=0; tr < alg.keys_treats.at(ks).treat.size(); ++tr){
			KeyTreat kt = alg.keys_treats.at(ks);
			switch (kt.treat.at(tr)) {
				case Require_Treat:
					treats.append("REQUIRED, ");
					break;
				case Exist_Treat:
					treats.append("Existance Only, ");
					break;
				case Followed_Double_Treat:
					treats.append("Followed by Double value, ");
					break;
				case Followed_Int_Treat:
					treats.append("Followed by Integer value, ");
					break;
				case Followed_String_Treat:
					treats.append("Followed by String value, ");
					break;
				case Output_Treat:
					treats.append("Result Output, ");
					break;
			}
		}
		cout << "[" << treats.substr(0, treats.size()-2) << "] ";
		cout << alg.keys_treats.at(ks).description;
		if(!alg.keys_treats.at(ks).example.empty())
			cout << endl << "\t\t\t //Example: " << alg.keys_treats.at(ks).example;
		cout << endl;
	}
	cout << endl;
}

void ArgsProcessor::printGeneralHelp(){
	// Parametros generales
	cout << "General Arguments:" << endl;
	for(unsigned int ks=0; ks < myInstance->gParams.size(); ++ks){
		cout << "\t[" << myInstance->gParams.at(ks).key << "]\t";
		// Por cada opcion de tratamiento del argumento
		string treats = "";
		for(unsigned int tr=0; tr < myInstance->gParams.at(ks).treat.size(); ++tr){
			KeyTreat kt = myInstance->gParams.at(ks);
			switch (kt.treat.at(tr)) {
				case Require_Treat:
					treats.append("REQUIRED, ");
					break;
				case Exist_Treat:
					treats.append("Existance Only, ");
					break;
				case Followed_Double_Treat:
					treats.append("Followed by Double value, ");
					break;
				case Followed_Int_Treat:
					treats.append("Followed by Integer value, ");
					break;
				case Followed_String_Treat:
					treats.append("Followed by String value, ");
					break;
				case Output_Treat:
					treats.append("Result Output, ");
					break;
			}
		}
		cout << "[" << treats.substr(0, treats.size()-2) << "] ";
		cout << myInstance->gParams.at(ks).description;
		if(!myInstance->gParams.at(ks).example.empty())
			cout << endl << "\t\t\t //Example: " << myInstance->gParams.at(ks).example;
		cout << endl;
	}
}

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
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void ArgsProcessor::checkArgs(ArgObj *currentArgs, int argcount, char* argvalues[]){
	bool found;

	for(unsigned int i=0; i < myInstance->gParams.size(); ++i){
		currentArgs->keys_treats.push_back(myInstance->gParams.at(i));
	}

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
				MyLogger::log()->warn("**************************************************************");
				MyLogger::log()->warn("[ArgsProcessor][checkArgs] Unknown argument: %s", argvalues[i]);
				MyLogger::log()->warn("**************************************************************");
			}
		}
	}
}

void ArgsProcessor::setArgs(int argcount, char* argvalues[]){
	// Chequear primer argumento => Tipo de algoritmo
	if(argcount < 2){
		MyLogger::log()->error("[ArgsProcessor][setArgs] No Algorithm Selected");
		printHelp();
		exit(EXIT_FAILURE);
	}

	string alg_str = argvalues[1];
	toLowerCase(alg_str);
	currentAlgorithmType = AlgorithmExecutor::translate(alg_str);
	if(currentAlgorithmType == None_Algorithm){
		MyLogger::log()->error("[ArgsProcessor][setArgs] No Algorithm Selected: %s", alg_str.c_str());
		printHelp();
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
		printHelp();
		exit(EXIT_FAILURE);
	}

	// Chequear parametros
	vector<KeyTreat> currentArgs = currentArgsObj.keys_treats;

	// Por cada llave posible del algoritmo
	for(unsigned int ai=0; ai < currentArgs.size(); ++ai){

		KeyTreat currentKey = currentArgs.at(ai);
		// Dentro de cada tratamiento posible
		int currentArgPosition = find(currentKey.key, argcount, argvalues);
		for(unsigned int t=0; t < currentKey.treat.size(); ++t){
			switch (currentKey.treat.at(t)) {
				case Require_Treat:
					// Debe existir la posicion
					if(currentArgPosition == -1){
						MyLogger::log()->error("[ArgsProcessor][setArgs] Required Argument not found: %s", currentKey.key.c_str());
						printHelp(currentArgsObj);
						exit(EXIT_FAILURE);
					}
					MyLogger::log()->debug("[ArgsProcessor][setArgs] %s Required", currentKey.key.c_str());
					break;
				case Followed_Double_Treat:
					// Buscar el siguiente parametro para retornarlo como double
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1] && atof(argvalues[currentArgPosition+1])!= 0){
							MyLogger::log()->debug("[ArgsProcessor][setArgs] %s=%f", currentKey.key.c_str(), atof(argvalues[currentArgPosition+1]));
							pc->addParam(currentKey.key, new Container(atof(argvalues[currentArgPosition+1])));
						}else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							printHelp(currentArgsObj);
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Followed_Int_Treat:
					// Buscar el siguiente parametro para retornarlo como Integer
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1] && atoi(argvalues[currentArgPosition+1])!= 0){
							MyLogger::log()->debug("[ArgsProcessor][setArgs] %s=%i", currentKey.key.c_str(), atoi(argvalues[currentArgPosition+1]));
							pc->addParam(currentKey.key, new Container(atoi(argvalues[currentArgPosition+1])));
						}else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							printHelp(currentArgsObj);
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Followed_String_Treat:
					// Buscar el siguiente parametro para retornarlo como String
					if(currentArgPosition != -1){
						if(argvalues[currentArgPosition+1]){
							MyLogger::log()->debug("[ArgsProcessor][setArgs] %s=%s", currentKey.key.c_str(), argvalues[currentArgPosition+1]);
							pc->addParam(currentKey.key, new Container(argvalues[currentArgPosition+1]));
						}else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							printHelp(currentArgsObj);
							exit(EXIT_FAILURE);
						}
					}
					break;
				case Exist_Treat:
					// Solamente debe existir
					if(currentArgPosition != -1){
						MyLogger::log()->debug("[ArgsProcessor][setArgs] %s Exist", currentKey.key.c_str());
						pc->addParam(currentKey.key, new Container(argvalues[currentArgPosition]));
					}
					break;
				case Output_Treat:
					// Se asume que sigue con algun parametro tipo string
					if(currentArgPosition != -1){
						MyLogger::log()->debug("[ArgsProcessor][setArgs] %s Output", currentKey.key.c_str());
						currentOutputType = Output::translate(toLowerCase(argvalues[currentArgPosition]));
						if(argvalues[currentArgPosition+1]){
							MyLogger::log()->debug("[ArgsProcessor][setArgs] %s=%s", currentKey.key.c_str(), argvalues[currentArgPosition+1]);
							currentOutputFile = argvalues[currentArgPosition+1];
						}else{
							MyLogger::log()->error("[ArgsProcessor][setArgs] Required Folowed Argument not found: %s", currentKey.key.c_str());
							printHelp(currentArgsObj);
							exit(EXIT_FAILURE);
						}
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

vector<string> ArgsProcessor::getKeys(){
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

string ArgsProcessor::getOutputString(){
	return currentOutputFile;
}

