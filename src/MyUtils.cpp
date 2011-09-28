/*
 * MyUtils.cpp
 *
 *  Created on: 28/09/2011
 *      Author: ptrack
 */
#include "MyUtils.h"

void MyUtils::writeToFile(Array2D<double> *arr, string file){
	ofstream myfile;
	myfile.open(file.c_str());

	for(unsigned int x=0; x < arr->getWidth(); ++x){
		for(unsigned int y=0; y < arr->getHeight(); ++y){
			myfile << "Data[" << x << "][" << y << "]: " << arr->getValue(x,y) << ";";
		}
		myfile << endl;
	}
	myfile.close();
}

void MyUtils::writeToFile(Array2D<int> *arr, string file){
	ofstream myfile;
	myfile.open(file.c_str());

	for(unsigned int x=0; x < arr->getWidth(); ++x){
		for(unsigned int y=0; y < arr->getHeight(); ++y){
			myfile << "Data[" << x << "][" << y << "]: " << arr->getValue(x,y) << ";";
		}
		myfile << endl;
	}
	myfile.close();
}

void MyUtils::writeToFile(vector<MyPeak> vec, string file){
	ofstream myfile;
	myfile.open(file.c_str());

	for(unsigned int i=0; i < vec.size(); ++i){
		myfile << "Data[" << i << "]: ";
		myfile << "X:" << vec.at(i).getX() << " ,";
		myfile << "Y:" << vec.at(i).getY() << " ;";
		myfile << "Inten:" << vec.at(i).getIntensity() << endl;
	}

	myfile.close();
}
