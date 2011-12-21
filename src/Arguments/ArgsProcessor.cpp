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
	chi2.argkey = "chi2";
	chi2.description = "Convolution based least-squares fitting.";
	chi2.example = "chi2 -i MyImage.tif -d 9.87 -w 1.84";

	/* Parametros aceptables */
	KeyTreat img; img.key = "-i"; img.description = "Image to read.";
	img.treat.push_back(Require_Treat);
	img.treat.push_back(Followed_String_Treat);
	chi2.keys_treats.push_back(img);

	KeyTreat d; d.key = "-d"; d.description = "Diameter of an ideal particle. (Default = 9.87)";
	d.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(d);

	KeyTreat w; w.key = "-w"; w.description = "Value of how sharply the ideal particle is viewed (Focus). (Default = 1.84)";
	w.treat.push_back(Followed_Double_Treat);
	chi2.keys_treats.push_back(w);

	KeyTreat cut; cut.key = "-cut"; cut.description = "Crop image by each side";
	cut.treat.push_back(Followed_Int_Treat);
	chi2.keys_treats.push_back(cut);

	KeyTreat maxchi2miniter; maxchi2miniter.key = "-maxchi2miniter"; maxchi2miniter.description = "Limit the iteration for minimizing Chi2Error (Default = 5)";
	maxchi2miniter.treat.push_back(Followed_Int_Treat);
	chi2.keys_treats.push_back(maxchi2miniter);

	vParams.push_back(chi2);

	/**
	 *************************
	 * Argumentos para Chi2HD
	 *************************
	 */
	ArgObj chi2hd;
	chi2hd.type = Chi2HD_Algorithm;
	chi2hd.argkey = "chi2hd";
	chi2hd.description = "Convolution based least-squares fitting for High density particle systems.";
	chi2hd.example = "chi2hd -i MyImage.tif -d 9.87 -w 1.84";

	/* Parametros aceptables */
	chi2hd.keys_treats.push_back(img);
	chi2hd.keys_treats.push_back(d);
	chi2hd.keys_treats.push_back(w);
	chi2hd.keys_treats.push_back(cut);
	chi2hd.keys_treats.push_back(maxchi2miniter);

	KeyTreat chi_cut; chi_cut.key = "-chicut"; chi_cut.description = "Minimal intensity of the convolution peaks to be detected.";
	chi_cut.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(chi_cut);

	KeyTreat vor_cut; vor_cut.key = "-vorcut"; vor_cut.description = "Minimal Voronoi area acceptable of peak to be considered as peak.";
	vor_cut.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(vor_cut);

	KeyTreat vor_sl; vor_sl.key = "-vorsl"; vor_sl.description = "Voronoi area value division of solid and liquid particle.";
	vor_sl.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(vor_sl);

	KeyTreat filter2i; filter2i.key = "-2filteri"; vor_sl.description = "Second Filter of Bad particles using Image intensity Only";
	filter2i.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(filter2i);

	KeyTreat filter2v; filter2v.key = "-2filterv"; vor_sl.description = "Second Filter of Bad particles using Voronoi area Only";
	filter2v.treat.push_back(Followed_Double_Treat);
	chi2hd.keys_treats.push_back(filter2v);

	vParams.push_back(chi2hd);


	/**
	 *************************
	 * Argumentos para Chi2HD CUDA
	 *************************
	 */
	ArgObj chi2hdcuda;
	chi2hdcuda.type = Chi2HDCuda_Algorithm;
	chi2hdcuda.argkey = "chi2hdcuda";
	chi2hdcuda.description = "Convolution based least-squares fitting for High density particle systems. Using CUDA Technology";
	chi2hdcuda.example = "chi2hdcuda -i MyImage.tif -d 9.87 -w 1.84";
	chi2hdcuda.keys_treats.push_back(img);
	chi2hdcuda.keys_treats.push_back(d);
	chi2hdcuda.keys_treats.push_back(w);
	chi2hdcuda.keys_treats.push_back(cut);
	chi2hdcuda.keys_treats.push_back(maxchi2miniter);
	chi2hdcuda.keys_treats.push_back(chi_cut);
	chi2hdcuda.keys_treats.push_back(vor_cut);
	chi2hdcuda.keys_treats.push_back(vor_sl);
	chi2hdcuda.keys_treats.push_back(filter2i);
	chi2hdcuda.keys_treats.push_back(filter2v);
	// -onevalidation
	KeyTreat one_validation; one_validation.key = "-validateones"; one_validation.description = "Validate peaks minimum distance only Ones.";
	one_validation.treat.push_back(Exist_Treat);
	chi2hdcuda.keys_treats.push_back(one_validation);

	vParams.push_back(chi2hdcuda);

	/**
	 *************************
	 * Parametros generales
	 *************************
	 */
	KeyTreat silent; silent.key = "-silent"; silent.description = "Displays no text during process.";
	silent.treat.push_back(Exist_Treat);

	KeyTreat debug; debug.key = "-debug"; debug.description = "Display major process status.";
	debug.treat.push_back(Exist_Treat);

	KeyTreat debugwf; debugwf.key = "-debugwf"; debugwf.description = "Display major process status and write status files.";
	debugwf.treat.push_back(Exist_Treat);

	KeyTreat chrono; chrono.key = "-chrono"; chrono.description = "Display starting and finishing status.";
	chrono.treat.push_back(Exist_Treat);

	KeyTreat out; out.key = "-out"; out.description = "Plain Text Output file.";
	out.treat.push_back(Output_Treat);
	out.treat.push_back(Followed_String_Treat);

	KeyTreat outb; outb.key = "-outbin"; outb.description = "Binary Output file.";
	outb.treat.push_back(Output_Treat);
	outb.treat.push_back(Followed_String_Treat);

//	KeyTreat outc; outc.key = "-outcon"; outc.description = "Output Conection (Unimplemented, for future release).";
//	outc.treat.push_back(Output_Treat);

	KeyTreat nth; nth.key = "-nothreads"; nth.description = "Use no threads to calculate";
	nth.treat.push_back(Exist_Treat);

	KeyTreat dspl; dspl.key = "-display"; dspl.description = "Display Obtained Peaks into Image";
	dspl.treat.push_back(Exist_Treat);
	for(unsigned int i=0; i < vParams.size(); ++i){
		vParams.at(i).keys_treats.push_back(silent);
		vParams.at(i).keys_treats.push_back(debug);
		vParams.at(i).keys_treats.push_back(debugwf);
		vParams.at(i).keys_treats.push_back(chrono);
		vParams.at(i).keys_treats.push_back(out);
		vParams.at(i).keys_treats.push_back(outb);
//		vParams.at(i).keys_treats.push_back(outc);
		vParams.at(i).keys_treats.push_back(nth);
		vParams.at(i).keys_treats.push_back(dspl);
	}
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
	cout << "Primary use as: $ ptrack2 [Algorithm Type] [[Algorithm Argument] ..]" << endl << endl;

	// Por cada algoritmo
	for(unsigned int i=0; i < myInstance->vParams.size(); ++i){
		ArgObj alg = myInstance->vParams.at(i);
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
	currentAlgorithmType = Algorithm::translate(alg_str);
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
						printHelp();
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
							printHelp();
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
							printHelp();
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
							printHelp();
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
