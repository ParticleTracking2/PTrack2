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
//	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	Array2D<double> *kernel = (Array2D<double>*)pc->getData("kernel_image");
	Array2D<double> *diff = (Array2D<double>*)pc->getData("chi_difference");
//	vector<MyPeak> *peaks = (vector<MyPeak>*)pc->getData("peaks");
//	vector<double> *px = (vector<double>*)pc->getData("px");
//	vector<double> *py = (vector<double>*)pc->getData("py");
//	double d = pc->getParam("dD")->getDataDouble();
//	double w = pc->getParam("dW")->getDataDouble();
//	int ss = pc->getParam("iSS")->getDataInt();

	Array2D<double> *normaldata_chi = new Array2D<double>(diff->getWidth(), diff->getHeight());

	bool stop = false;
	double maxval;
	while(!stop){
		//scalematrix
		for(unsigned int x=0; x < diff->getWidth(); ++x)
			for(unsigned int y=0; y < diff->getHeight(); ++y){
				normaldata_chi->setValue(x,y, 4*diff->getValue(x,y)*diff->getValue(x,y));
			}

		//find maxima
		normaldata_chi->getHiLo();
		maxval = normaldata_chi->getHigh();

		//inverse data
		for(unsigned int x=0; x < diff->getWidth(); ++x)
			for(unsigned int y=0; y < diff->getHeight(); ++y){
				normaldata_chi->setValue(x,y, maxval - normaldata_chi->getValue(x,y) );
			}

		//normalize data
		normaldata_chi->normalize();

		Array2D<double> *my_chi_img = ChiImageStep::getChiImage(normaldata_chi, kernel);
		vector<MyPeak> new_peaks = PeaksStep::getPeaks(my_chi_img, _chi_cut, _mindistance, _minsep);

		cout << "Peaks detected valids: " << new_peaks.size() << " Of " << my_chi_img->getHeight()*my_chi_img->getWidth() << endl;
		pc->printInformation();
		stop = true;
		if(next)
			next->handleData(pc);
	}
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
