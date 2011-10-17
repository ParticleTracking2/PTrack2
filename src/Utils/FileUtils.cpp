/*
 * MyUtils.cpp
 *
 *  Created on: 28/09/2011
 *      Author: ptrack
 */
#include "FileUtils.h"

void FileUtils::writeToFile(string str, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);
		myfile << str;
		myfile.close();
	}
}

void FileUtils::writeToFileM(vector< pair<double,double> > *vertex, vector< vector<int> > *cell, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		myfile << vertex->size() << endl;
		for(unsigned int i=0; i < vertex->size(); ++i){
			myfile << fixed << vertex->at(i).first << " " << vertex->at(i).second << endl;
		}

		myfile << cell->size() << endl;
		for(unsigned int i=0; i < cell->size(); ++i){
			vector<int> data = cell->at(i);
			myfile << data.size() << " ";
			for(unsigned int d=0; d < data.size(); ++d){
				myfile << data.at(d) << " ";
			}
			myfile << endl;
		}

		myfile.close();
	}
}

void FileUtils::writeToFileM(MyMatrix<double> *arr, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int x=0; x < arr->sX(); ++x){
			for(unsigned int y=0; y < arr->sY(); ++y){
				myfile << fixed << arr->getValue(x,y) << ";";
			}
			myfile << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFile(MyMatrix<double> *arr, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int x=0; x < arr->sX(); ++x){
			for(unsigned int y=0; y < arr->sY(); ++y){
				myfile << "Data[" << x << "][" << y << "]: " << arr->getValue(x,y) << ";";
			}
			myfile << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFileM(MyMatrix<int> *arr, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int x=0; x < arr->sX(); ++x){
			for(unsigned int y=0; y < arr->sY(); ++y){
				myfile << fixed << arr->getValue(x,y) << ";";
			}
			myfile << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFile(MyMatrix<int> *arr, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int x=0; x < arr->sX(); ++x){
			for(unsigned int y=0; y < arr->sY(); ++y){
				myfile << "Data[" << x << "][" << y << "]: " << arr->getValue(x,y) << ";";
			}
			myfile << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFile(vector<MyPeak> *peaks, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int i=0; i < peaks->size(); ++i){
			myfile << fixed << "Data[" << i << "]: X:" << peaks->at(i).x << ",Y:" << peaks->at(i).y << "; Inten:" << peaks->at(i).intensity << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFileM(vector<MyPeak> *peaks, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		myfile << fixed;
		for(unsigned int i=0; i < peaks->size(); ++i){
			myfile << peaks->at(i).x << "\t";
//			myfile << peaks->at(i).px << "\t" << peaks->at(i).dpx << "\t";
			myfile << peaks->at(i).y << "\t";
//			myfile << peaks->at(i).py << "\t" << peaks->at(i).dpy << "\t";
			myfile << peaks->at(i).intensity << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFileMA(vector<MyPeak> *peaks, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		myfile << fixed;
		for(unsigned int i=0; i < peaks->size(); ++i){
			myfile << peaks->at(i).vor_area << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFile(vector<double> *vec, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int i=0; i < vec->size(); ++i){
			myfile << "Data[" << i << "]: " << vec->at(i) << endl;
		}
		myfile.close();
	}
}

void FileUtils::writeToFileM(vector<double> *vec, const char* file){
	if(MyLogger::logFileData()){
		ofstream myfile;
		myfile.open(file);

		for(unsigned int i=0; i < vec->size(); ++i){
			myfile << fixed << vec->at(i) << endl;
		}
		myfile.close();
	}
}
