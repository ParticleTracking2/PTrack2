/*
 * PeaksStep.cpp
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#include "PeaksStep.h"

/**
 *******************************
 * Constructores
 *******************************
 */
PeaksStep::PeaksStep(){
	_threshold = 5;
	_minsep = 1;
	_mindistance = 5;
	chi_img = 0;
}

/**
 *******************************
 * Metodos
 *******************************
 */
void PeaksStep::handleData(ParameterContainer *pc){
	printDescription();
	chi_img = (Array2D<double> *)pc->getParam("chi_image")->getData();

	vector<MyPeak> *peaks = new vector<MyPeak>();
	clock_t start = clock();
	for(unsigned int x=0; x < chi_img->getWidth(); ++x)
		for(unsigned int y=0; y < chi_img->getHeight(); ++y){
			if(chi_img->getValue(x,y) > _threshold){
				if(findLocalMinimum(x,y)){
					MyPeak local(x,y, chi_img->getValue(x,y));
					peaks->push_back(local);
				}
			}
		}

	clock_t stop = clock();
	cout << "TimePeaks: " << ((stop-start)*1000/CLOCKS_PER_SEC) << endl;

	cout << "Peaks detected: " << peaks->size() << " Of " << chi_img->getHeight()*chi_img->getWidth() << endl;
	sort(peaks->begin(), peaks->end(), MyPeak::compareMe);

	start = clock();
	vector<MyPeak> valids = validatePeaks(peaks);
	stop = clock();

	cout << "Peaks detected valids: " << valids.size() << " Of " << chi_img->getHeight()*chi_img->getWidth() << endl;
	cout << "TimeValid: " << ((stop-start)*1000/CLOCKS_PER_SEC) << endl;
	pc->addParam("peaks", new Container(&valids), "[vector<MyPeak>] Maximos encontrados a partir de la imagen Chi2");

//	if(next)
//		next->handleData(pc);
}

// Eliminar los que no cumplen con la minima distancia
vector<MyPeak> PeaksStep::validatePeaks(vector<MyPeak> *peaks){
	int difx = 0;
	int dify = 0;
	bool valid = true;
	vector<MyPeak> valids;
	for(unsigned int i=0; i < peaks->size(); ++i){
		valid = true;
		for(unsigned int j=i+1; j < peaks->size(); ++j){
			difx = peaks->at(i).getX() - peaks->at(j).getX();
			dify = peaks->at(i).getY() - peaks->at(j).getY();

			if( (difx*difx + dify*dify) < _mindistance*_mindistance){
				valid = false;
				break;
			}
		}
		if(valid){
			valids.push_back(peaks->at(i));
		}
	}
	return valids;
}

bool PeaksStep::findLocalMinimum(unsigned int imgX, unsigned int imgY){
	int currentX = 0;
	int currentY = 0;
	for(int localX = _minsep; localX >= -_minsep; --localX){
		for(int localY = _minsep; localY >= -_minsep; --localY){
			if(localX != 0 && localY != 0){
				currentX = (imgX+localX);
				currentY = (imgY+localY);

				if(currentX < 0)
					currentX = chi_img->getWidth() + currentX;
				if(currentY < 0)
					currentY = chi_img->getHeight() + currentY;

				currentX = (currentX)% chi_img->getWidth();
				currentY = (currentY)% chi_img->getHeight();

				if(chi_img->getValue(imgX, imgY) <= chi_img->getValue(currentX, currentY))
					return false;
			}
		}
	}
	return true;
}

void PeaksStep::setThreshold(int threshold){
	_threshold = threshold;
}

void PeaksStep::setMinSeparation(int minsep){
	_minsep = minsep;
}

void PeaksStep::setMinDistance(int mindistance){
	_mindistance = mindistance;
}
