/*
 * MyUtils.h
 *
 *  Created on: 28/09/2011
 *      Author: ptrack
 */
#include "Container/Array2D.h"
#include "Algorithm/Objects_Chi2/MyPeak.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#ifndef MYUTILS
#define MYUTILS

class MyUtils {
public:
	static void writeToFile(Array2D<double> *arr, string file);
	static void writeToFile(Array2D<int> *arr, string file);
	static void writeToFile(vector<MyPeak> vec, string file);
};

#endif /* MYUTILS */
