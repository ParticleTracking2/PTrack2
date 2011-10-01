/*
 * AddMissedPeaksStep.cpp
 *
 *  Created on: 26/09/2011
 *      Author: ptrack
 */

#include "AddMissedPeaksStep.h"

AddMissedPeaks_Step::AddMissedPeaks_Step(){
	_chi_cut = 2;
	_minsep = 1;
	_mindistance = 5;
}

void AddMissedPeaks_Step::handleData(ParameterContainer *pc){
	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	Array2D<double> *kernel = (Array2D<double>*)pc->getData("kernel_image");
	Array2D<double> *diff = (Array2D<double>*)pc->getData("chi_difference");
	vector<MyPeak> *peaks = (vector<MyPeak>*)pc->getData("peaks");
	unsigned int os = pc->getParam("iOS")->getDataInt();
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	Array2D<double> *grid_x = (Array2D<double>*)pc->getData("grid_x");
	Array2D<double> *grid_y = (Array2D<double>*)pc->getData("grid_y");
	Array2D<int> *over = (Array2D<int>*)pc->getData("over");

	vector<double> *px = (vector<double>*)pc->getData("px");
	vector<double> *py = (vector<double>*)pc->getData("py");

	Array2D<double> *normaldata_chi = new Array2D<double>(diff->getWidth(), diff->getHeight());

	double total_found = 0;
	while(1){
		double maxval;
		double tmp;
		//scalematrix
		for(unsigned int x=0; x < diff->getWidth(); ++x)
			for(unsigned int y=0; y < diff->getHeight(); ++y){
				tmp = 4*diff->getValue(x,y)*diff->getValue(x,y);
				normaldata_chi->setValue(x,y,tmp);
			}

		//find maxima
		normaldata_chi->getHiLo();
		maxval = normaldata_chi->getHigh();

		//inverse data
		for(unsigned int x=0; x < diff->getWidth(); ++x)
			for(unsigned int y=0; y < diff->getHeight(); ++y){
				tmp = maxval - normaldata_chi->getValue(x,y);
				normaldata_chi->setValue(x,y,tmp);
			}

		//normalize data
		normaldata_chi->normalize();

		Array2D<double> *my_chi_img = ChiImageStep::getChiImage(normaldata_chi, kernel);

		vector<MyPeak> new_peaks = PeaksStep::getPeaks(my_chi_img, _chi_cut, _mindistance, _minsep);
		delete my_chi_img;

		unsigned int totalinside = 0;
		unsigned int old_size = peaks->size();
		//check if NEW points are inside the image (clean newpeaks)
		MyPeak tmppk;
		for(unsigned int i=0; i < new_peaks.size(); ++i){
			tmppk = new_peaks.at(i);
			if(	0 <= (tmppk.getX() - os) && (tmppk.getX() - os) < img->getWidth() &&
				0 <= (tmppk.getY() - os) && (tmppk.getY() - os) < img->getHeight()){
				peaks->push_back(new_peaks.at(i));
				px->push_back(1.0*new_peaks.at(i).getX());
				py->push_back(1.0*new_peaks.at(i).getY());
				totalinside++;
			}
		}
		new_peaks.clear();

		total_found += totalinside;
		cout << "Original No of Points: " << old_size << ", +" << totalinside << "; Total = " << total_found << endl;

		// Generar nueva image diferenciada con esos puntos
		ParticleGridStep::generateGrid(peaks, px, py, os, img, grid_x, grid_y, over);

//		MyUtils::writeToFile(grid_x, "grid_x2-cpp.txt");
//		MyUtils::writeToFile(grid_y, "grid_y2-cpp.txt");
//		MyUtils::writeToFile(over, "over2-cpp.txt");

		// No hay nuevos puntos
		if(totalinside <= 0)
			break;

		diff = ChiDifferenceStep::computeDifference(img, grid_x, grid_y, d, w);
	}

	sort(peaks->begin(), peaks->end(), MyPeak::compareMe);
	px->clear();
	py->clear();

	for(unsigned int i=0; i < peaks->size(); ++i){
		px->push_back(1.0*peaks->at(i).getX());
		py->push_back(1.0*peaks->at(i).getY());
	}

	pc->printInformation();

	nextStep(pc);
}

void AddMissedPeaks_Step::setChiCut(int chi_cut){
	_chi_cut = chi_cut;
}
void AddMissedPeaks_Step::setMinSep(int minsep){
	_minsep = minsep;
}
void AddMissedPeaks_Step::setMinDistance(int mindistance){
	_mindistance = mindistance;
}
