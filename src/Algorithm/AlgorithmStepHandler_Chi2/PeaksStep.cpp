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
}

/**
 *******************************
 * Metodos
 *******************************
 */
void PeaksStep::handleData(ParameterContainer *pc){
	Array2D<double> *chi_img = (Array2D<double> *)pc->getParam("chi_image")->getData();

	vector<MyPeak> valids = PeaksStep::getPeaks(chi_img, _threshold, _mindistance, _minsep);

//	MyUtils::writeToFile(valids, "peaks1-cpp.txt");
	pc->addParam("peaks", new Container(&valids), "[vector<MyPeak>] Maximos encontrados a partir de la imagen Chi2");

	nextStep(pc);
}

vector<MyPeak> PeaksStep::getPeaks(Array2D<double> *img, int threshold, int mindistance, int minsep){
	cout << "threshold: " << threshold << ", mindistance:" << mindistance << ", minsep: " << minsep << endl;

	vector<MyPeak> *peaks = new vector<MyPeak>();
	for(unsigned int x=0; x < img->getWidth(); ++x)
		for(unsigned int y=0; y < img->getHeight(); ++y){
			if(img->getValue(x,y) > threshold){
				if(findLocalMinimum(img, x,y, minsep)){
					MyPeak local(x,y, img->getValue(x,y));
					peaks->push_back(local);
				}
			}
		}

	cout << "Peaks detected: " << peaks->size() << " Of " << img->getWidth()*img->getHeight() << endl;
	sort(peaks->begin(), peaks->end(), MyPeak::compareMe);
	vector<MyPeak> valids = validatePeaks(peaks, mindistance);

	cout << "Peaks detected valids: " << valids.size() << " Of " << peaks->size() << endl;
	return valids;
}

// Eliminar los que no cumplen con la minima distancia
vector<MyPeak> PeaksStep::validatePeaks(vector<MyPeak> *peaks, int mindistance){
	int difx = 0;
	int dify = 0;
	bool valid = true;
	vector<MyPeak> valids;
	for(unsigned int i=0; i < peaks->size(); ++i){
		valid = true;
		for(unsigned int j=i+1; j < peaks->size(); ++j){
			difx = peaks->at(i).getX() - peaks->at(j).getX();
			dify = peaks->at(i).getY() - peaks->at(j).getY();

			if( (difx*difx + dify*dify) < mindistance*mindistance){
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

bool PeaksStep::findLocalMinimum(Array2D<double> *img, unsigned int imgX, unsigned int imgY, int minsep){
	int currentX = 0;
	int currentY = 0;
	for(int localX = minsep; localX >= -minsep; --localX){
		for(int localY = minsep; localY >= -minsep; --localY){
			if(!(localX == 0 && localY == 0)){
				currentX = (imgX+localX);
				currentY = (imgY+localY);

				if(currentX < 0)
					currentX = img->getWidth() + currentX;
				if(currentY < 0)
					currentY = img->getHeight() + currentY;

				currentX = (currentX)% img->getWidth();
				currentY = (currentY)% img->getHeight();

				if(img->getValue(imgX, imgY) <= img->getValue(currentX, currentY))
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

void PeaksStep::printDescription(){
	cout << "3.- Obtener los maximos locales (representantes de particulas)" << endl;
}
