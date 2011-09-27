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
	unsigned int ss = pc->getParam("iSS")->getDataInt();
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	Array2D<double> *grid_x = (Array2D<double>*)pc->getData("grid_x");
	Array2D<double> *grid_y = (Array2D<double>*)pc->getData("grid_y");
	Array2D<int> *over = (Array2D<int>*)pc->getData("over");

	Array2D<double> *normaldata_chi = new Array2D<double>(diff->getWidth(), diff->getHeight());

	double maxval;
	while(1){
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

		MyPeak tmp;
		unsigned int old_size = peaks->size();
		//check if NEW points are inside the image (clean newpeaks)
		for(unsigned int i=0; i < new_peaks.size(); ++i){
			tmp = new_peaks.at(i);
			if(	0 <= (tmp.getX() - ss) && (tmp.getX() - ss) < img->getWidth() &&
				0 <= (tmp.getY() - ss) && (tmp.getY() - ss) < img->getHeight()){
				peaks->push_back(new_peaks.at(i));
			}
		}
		unsigned int new_size = peaks->size();

		// No hay nuevos puntos
		if(old_size == new_size)
			break;

		// Generar nueva image diferenciada con esos puntos
		unsigned int counter = ParticleGridStep::generateGrid(peaks, ss, img, grid_x, grid_y, over);
		cout << "Total pgrid: " << 1.0*counter/peaks->size() << "; counter: " << counter << endl;
		diff = ChiDifferenceStep::computeDifference(img,grid_x, grid_y, d, w);
	}

	sort(peaks->begin(), peaks->end(), MyPeak::compareMe);
	pc->printInformation();
	if(next)
		next->handleData(pc);
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
