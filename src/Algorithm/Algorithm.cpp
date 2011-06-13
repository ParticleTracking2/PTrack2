/*
 * Algorithm.cpp
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */

#include "Algorithm.h"
#include <iostream>
#include <string>
using namespace std;

string Algorithm::name(){
	return "Generic Algorithm";
}

Algorithm::Algorithm() {
	// TODO Auto-generated constructor stub

}

Algorithm::~Algorithm() {
	// TODO Auto-generated destructor stub
}

void Algorithm::run(){
	cout << "Running Algorithm" << endl;

}
