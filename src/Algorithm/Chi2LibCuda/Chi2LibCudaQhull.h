/*
 * Chi2LibCudaQhull.h
 *
 *  Created on: 15/12/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDAQHULL
#define CHI2LIBCUDAQHULL

#include <string>
#include <sstream>
#include <algorithm>
#include <math.h>
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "Container/cuMyPeak.h"

using namespace std;

class Chi2LibCudaQhull {
private:
	static void trim(string& str);
	static void stringSplit(string str, string delim, vector<string> *out);
	static string prepareData(cuMyPeakArray *peaks);
	static void interpretData(string *data, vector< pair<double,double> > *vertex, vector< vector<int> > *cell);
public:
	static string execQhull(string data, string params);
	static void addVoronoiAreas(cuMyPeakArray *peaks);
};

#endif
