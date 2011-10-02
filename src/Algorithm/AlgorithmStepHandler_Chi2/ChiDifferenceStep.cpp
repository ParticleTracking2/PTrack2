/*
 * ChiDifferenceStep.cpp
 *
 *  Created on: 26/09/2011
 *      Author: ptrack
 */

#include "ChiDifferenceStep.h"

void ChiDifferenceStep::handleData(ParameterContainer *pc){
	Array2D<double> *img = (Array2D<double>*)pc->getData("normal_image");
	Array2D<double> *grid_x = (Array2D<double>*)pc->getData("grid_x");
	Array2D<double> *grid_y = (Array2D<double>*)pc->getData("grid_y");
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	Array2D<double> *diff = computeDifference(img, grid_x, grid_y, d, w).first;

	pc->addParam("chi_difference", new Container(diff), "[Array2D<double>] Diferencia entre la imagen normalizada y la imagen Chi2 generada");
	pc->addParam("chi2_value", new Container(2132.123), "[double] Sumatoria de los valores de chi_difference");

	nextStep(pc);
}

pair<Array2D<double>*, double> ChiDifferenceStep::computeDifference(Array2D<double> *img, Array2D<double> *grid_x, Array2D<double> *grid_y, double d, double w){
	Array2D<double> *diff = new Array2D<double>(img->getWidth(), img->getHeight(), 0.0);
	double x2y2 = 0.0;
	double temp = 0.0;

	double chi2err = 0.0;
	for(unsigned int x=0; x < img->getWidth(); ++x)
		for(unsigned int y=0; y < img->getWidth(); ++y){
			x2y2 = sqrt(1.0*grid_x->getValue(x,y)*grid_x->getValue(x,y) + 1.0*grid_y->getValue(x,y)*grid_y->getValue(x,y));
			temp = ((1.0-tanh( (x2y2-d/2.0)/w )) - 2.0*img->getValue(x,y))/2.0;

			diff->setValue(x,y,temp);
			chi2err += temp*temp;
		}
	cout << "Chi2 Error:" << chi2err << endl;

	pair<Array2D<double>*, double> ret;
	ret.first = diff;
	ret.second = chi2err;
	return ret;
}

void ChiDifferenceStep::printDescription(){
	cout << "5.- Calcula la imagen de diferencia entre la original y la grilla de particulas ideales con los maximos encontrados" << endl;
}
