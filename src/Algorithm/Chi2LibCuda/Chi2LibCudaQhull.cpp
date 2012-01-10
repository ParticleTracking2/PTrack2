/*
 * Chi2LibCudaQhull.cpp
 *
 *  Created on: 15/12/2011
 *      Author: juanin
 */
#ifdef CHI2CUDA
#include "Chi2LibCudaQhull.h"

void Chi2LibCudaQhull::trim(string& str){
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

void Chi2LibCudaQhull::stringSplit(string str, string delim, vector<string> *out){
	out->clear();
	trim(str);
	unsigned int oldend = 0;
	unsigned int end = 0;
	for(unsigned int i=0; i < str.size(); ++i){
		end = str.find(delim, i);
		if(end == oldend)
			break;
		oldend = end;
		out->push_back(str.substr(i,end-i));
		if(end > i && end < str.size())
			i = end;
	}
}

string Chi2LibCudaQhull::prepareData(cuMyPeakArray *peaks){
	stringstream ret;
	MyLogger::log()->debug("[Chi2LibCudaQhull][prepareData] Preparing data");
	peaks->copyToHost();
	ret << "2" << endl;
	ret << peaks->size() << endl;
	ret << fixed;
	for(unsigned int i = 0; i < peaks->size(); ++i){
		ret << peaks->getHostValue(i).fx << " " << peaks->getHostValue(i).fy << endl;
	}
	MyLogger::log()->debug("[Chi2LibCudaQhull][prepareData] Data Prepared");
	return ret.str();
}

void Chi2LibCudaQhull::interpretData(string *data, vector< pair<double,double> > *vertex, vector< vector<int> > *cells){
	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Interpreting data");
	stringstream ss(data->c_str());
	string stmp;

	getline(ss, stmp);	// Dim.. Constant = 2 for this
	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Dimension: %s", stmp.c_str());

	getline(ss, stmp);	// Data length
	unsigned int vSize = atoi(stmp.c_str());
	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Vertexs: %i", vSize);
	vertex->reserve(vSize);

	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Vertex reserved Size");
	vector<string> splited;
	for(unsigned int i = 0; i < vSize; ++i){
		getline(ss, stmp);
		// Vertex
		stringSplit(stmp, " ", &splited);
		pair<double,double> v_xy;
		v_xy.first = atof(splited.at(0).c_str());
		v_xy.second = atof(splited.at(1).c_str());
		vertex->push_back(v_xy);
	}
	getline(ss, stmp);
	unsigned int cSize = atoi(stmp.c_str());
	cells->reserve(cSize);
	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Cells: %i", cSize);
	for(unsigned int i = 0; i < cSize; ++i){
		getline(ss, stmp);
		// Cells
		stringSplit(stmp, " ", &splited);

		// Allocate data
		vector<int> cells_data;
		int res = atoi(splited.at(0).c_str());
		cells_data.reserve(res);

		// En caso de no tener celdas dejar como -1
		if(res == 0)
			cells_data.push_back(-1);
		// Populate
		for(unsigned int i=1; i < splited.size(); ++i){
			cells_data.push_back(atoi(splited.at(i).c_str()));
		}

		// Append
		cells->push_back(cells_data);
	}

	MyLogger::log()->debug("[Chi2LibCudaQhull][interpretData] Interpretation complete: Vertexs=%i; Cells=%i", vertex->size(), cells->size());
}

string Chi2LibCudaQhull::execQhull(string data, string params){
	string ret;
	string qhull_params = "qhull ";
	qhull_params.append(params);

	int qhull_in[2], qhull_out[2];
	pid_t qhullid;
	MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] Executing Qhull");

	if(pipe(qhull_in) != 0)
		MyLogger::log()->error("[Chi2LibCudaQhull][execQhull] Error Creating Input pipe");
	if(pipe(qhull_out))
		MyLogger::log()->error("[Chi2LibCudaQhull][execQhull] Error Creating Output pipe");

	if((qhullid = fork()) == -1){
		MyLogger::log()->error("[Chi2LibCudaQhull][execQhull] Error Forking");
	}

	// The child part
	if(qhullid == 0){
		MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] (Child) Entering");
		/**
		 * qhull >--> qhull_out >--> This
		 * qhull <--< qhull_in <--< This
		 */
		close(qhull_in[1]); 	close(qhull_out[0]);
		dup2(qhull_in[0],0);	dup2(qhull_out[1],1);
		close(qhull_in[0]); 	close(qhull_out[1]);
		execlp("qhull", qhull_params.c_str() , NULL); // Original qhull v Qbb p FN
		MyLogger::log()->error("[Chi2LibCudaQhull][execQhull] (Child) Error in execlp()");
		exit(1);
	}else{
		MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] (Parent) Entering");
		/**
		 * This <--< qhull_out <--< qhull
		 * This >--> qhull_in >--> qhull
		 */
		close(qhull_in[0]); 	close(qhull_out[1]);
		if(write(qhull_in[1], data.c_str(), data.size()) == (int)data.size()){
			MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] (Parent) Passing data correct");
		}
		close(qhull_in[1]);
		char readbuffer[256];
		int nbytes = 0;
		MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] (Parent) Waiting data from qhull");
		while((nbytes = read(qhull_out[0], readbuffer, sizeof(readbuffer))) > 0){
			ret.append(readbuffer, nbytes);
		}
	}
	MyLogger::log()->debug("[Chi2LibCudaQhull][execQhull] Executing Qhull Ended");
	return ret;
}

void Chi2LibCudaQhull::addVoronoiAreas(cuMyPeakArray *peaks){
	MyLogger::log()->debug("[Chi2LibCudaQhull][addVoronoiAreas] Adding Voronoi Areas to peaks. Size=%i", peaks->size());
	string prep = prepareData(peaks);
	string rawData = execQhull(prep, "v Qbb p FN");	// v = Voronoi; Qbb = Qbb-scale-last; p = points; FN = FNeigh-vertex;

	vector< pair<double,double> > vertex;
	vector< vector<int> > cells;
	interpretData(&rawData, &vertex, &cells);

	MyLogger::log()->debug("[Chi2LibCudaQhull][addVoronoiAreas] Iterating over cells");
	double xold = 0, yold = 0;
	double currentArea;
	bool mArea;
	for(unsigned int i=0; i < cells.size(); ++i){
		currentArea = 0;
		mArea = false;
		vector<int> currentCell = cells.at(i);
		// for each cell
		for(unsigned int c=0; c < currentCell.size(); ++c){
			if(currentCell[c] < 0){
				mArea = true;
				break;
			}
			if(c == 0){
				xold = vertex.at(currentCell[0]).first;
				yold = vertex.at(currentCell[0]).second;
			}else{
				currentArea += (xold*vertex.at(currentCell[c]).second - yold*vertex.at(currentCell[c]).first)*0.5;
				xold = vertex.at(currentCell[c]).first;
				yold = vertex.at(currentCell[c]).second;
			}
		}

		if(mArea){
			currentArea = -1;
			peaks->atHost(i).vor_area = (float)currentArea;
		}else{
			currentArea += (xold*vertex.at(currentCell[0]).second - yold*vertex.at(currentCell[0]).first)*0.5;
			peaks->atHost(i).vor_area = (float)fabs(currentArea);
		}
	}
	MyLogger::log()->debug("[Chi2LibCudaQhull][addVoronoiAreas] Adding Areas Complete!");
}
#endif
