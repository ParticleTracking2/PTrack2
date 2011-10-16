/*
 * KeyTreat.h
 *
 *  Created on: 11/10/2011
 *      Author: juanin
 */

#include "../../Algorithm/Algorithm.h"
#include <vector>
#include <string>

#ifndef KEYTREAT
#define KEYTREAT

using namespace std;

enum TreatType{
	Require_Treat,
	Followed_String_Treat,
	Followed_Int_Treat,
	Followed_Double_Treat,
	Exist_Treat,
	Output_Treat
};

struct KeyTreat{
	string key;
	vector<TreatType> treat;
};

struct ArgObj{
	AlgorithmType type;
	vector<KeyTreat> keys_treats;
};

#endif
