/*
 * Chi2LibQhull.h
 *
 *  Created on: 08/10/2011
 *      Author: juanin
 */

#ifndef CHI2LIBQHULL
#define CHI2LIBQHULL

#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "../MyPeak.h"

using namespace std;

class Chi2LibQhull {
private:
	static void stringSplit(string str, string delim, vector<string> *out);
	static string prepareData(vector<MyPeak> *peaks);
	static void interpretData(string *data, vector< pair<double,double> > *vertex, vector< vector<int> > *cell);
public:
	static string execQhull(string data, string params);
	static void addVoronoiAreas(vector<MyPeak> *peaks);
};

#endif
