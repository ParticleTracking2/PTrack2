/*
 * ReComputeGridAndDiff.cpp
 *
 *  Created on: 01/10/2011
 *      Author: juanin
 */

#include "ReComputeGridAndDiff.h"

void ReComputeGridAndDiff::handleData(ParameterContainer *pc){
	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	Array2D<double> *diff = (Array2D<double>*)pc->getData("chi_difference");
	vector<MyPeak> *peaks = (vector<MyPeak>*)pc->getData("peaks");
	unsigned int os = pc->getParam("iOS")->getDataInt();

	Array2D<double> *grid_x = (Array2D<double>*)pc->getData("grid_x");
	Array2D<double> *grid_y = (Array2D<double>*)pc->getData("grid_y");
	Array2D<int> *over = (Array2D<int>*)pc->getData("over");

	vector<double> *px = (vector<double>*)pc->getData("px");
	vector<double> *py = (vector<double>*)pc->getData("py");
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	ParticleGridStep::generateGrid(peaks, px, py, os, img, grid_x, grid_y, over);
	delete diff;
	diff = 0;
	pair <Array2D<double> *, double> mypair= ChiDifferenceStep::computeDifference(img, grid_x, grid_y, d, w);
	diff = mypair.first;

	pc->setParam("chi_difference", new Container(diff));
	pc->addParam("chi2_value", new Container(mypair.second), "[double] Sumatoria de los cuadrados de los valores de chi_difference");

	px->clear();
	py->clear();
	for(unsigned int i=0; i < peaks->size(); ++i){
		px->push_back(1.0*peaks->at(i).getX());
		py->push_back(1.0*peaks->at(i).getY());
	}

	nextStep(pc);
}

void ReComputeGridAndDiff::printDescription(){
	cout << "5.2.- Recalcula las matrices auxiliares grid_x, grid_y, over y recalcula la image de diferencia Chi2" << endl;
}
