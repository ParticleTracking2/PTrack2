/*
 * Chi2Minimization.cpp
 *
 *  Created on: 01/10/2011
 *      Author: juanin
 */

#include "Chi2Minimization.h"

Chi2Minimization::Chi2Minimization(){
	_maxIterations = 5;
	_minChi2Delta = 1;
}

void Chi2Minimization::handleData(ParameterContainer *pc){
	vector<MyPeak> *peaks = (vector<MyPeak>*)pc->getData("peaks");
	vector<double> *px = (vector<double>*)pc->getData("px");
	vector<double> *py = (vector<double>*)pc->getData("py");
	Array2D<int> *over = (Array2D<int>*)pc->getData("over");
	Array2D<double> *diff = (Array2D<double>*)pc->getData("chi_difference");
	Array2D<double> *grid_x = (Array2D<double>*)pc->getData("grid_x");
	Array2D<double> *grid_y = (Array2D<double>*)pc->getData("grid_y");
	Array2D<double> *normal_image = (Array2D<double>*)pc->getData("normal_image");
	unsigned int os = pc->getParam("iOS")->getDataInt();	// shiftX shiftY
	unsigned int ss = pc->getParam("iSS")->getDataInt();	// Dp
	double currentChi2Err = pc->getParam("chi2_value")->getDataDouble();
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();

	unsigned int iterations = 0;
	double chi2Delta = currentChi2Err;

	while( fabs(chi2Delta) > _minChi2Delta &&  iterations < _maxIterations){
		// cidp2
		pair< vector<double>, vector<double> > mypair = newtonCenter(over, px, py, diff, peaks, os, d, w, ss);
		vector<double> dpx = mypair.first;
		vector<double> dpy = mypair.second;

		for(unsigned int i=0; i < peaks->size(); ++i){
			px->at(i) = px->at(i)+dpx.at(i);
			py->at(i) = py->at(i)+dpy.at(i);

			peaks->at(i).setX((unsigned int)round(px->at(i)));
			peaks->at(i).setY((unsigned int)round(py->at(i)));
		}
		dpx.clear(); dpy.clear();

		grid_x->reset(0);
		grid_y->reset(0);
		over->reset(0);

		ParticleGridStep::generateGrid(peaks,px,py,os,normal_image, grid_x, grid_y, over);

		delete diff;
		diff = 0;

		pair<Array2D<double>*, double> diffdata = ChiDifferenceStep::computeDifference(normal_image, grid_x, grid_y, d, w);
		diff = diffdata.first;
		chi2Delta = currentChi2Err - diffdata.second;
		currentChi2Err = currentChi2Err-chi2Delta;
		iterations++;
	}

	nextStep(pc);
}

pair< vector<double>, vector<double> > Chi2Minimization::newtonCenter(Array2D<int> *over, vector<double> *px, vector<double> *py, Array2D<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr){
	vector<double> dpx(peaks->size(), 0.0);
	vector<double> dpy(peaks->size(), 0.0);
	w = 1.0*w;
	int half = dp+2;

	double statchix = 0.0, statchiy= 0.0, statchixx=0.0, statchiyy=0.0, statchixy=0.0;
	double detproblem = 0;
	int total = 0;

	for(int npks = peaks->size()-1; npks >= 0; npks--){
		double chix, chiy, chixx, chiyy, chixy;
		chix = chiy = chixx = chiyy = chixy = 0;

		for(unsigned int localX=0; localX < 2*half+1; ++localX){
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				double xx, xx2, yy, yy2, rr, rr3;
				double dipx,dipy,dipxx,dipyy,dipxy;
				double sech2, tanh1;

				double currentX = (int)round(px->at(npks)) - shift + (localX - half);
				double currentY = (int)round(py->at(npks)) - shift + (localY - half);

				if( 0 <= currentX && currentX < over->getWidth() && 0 <= currentY && currentY < over->getHeight() ){
					xx 		= 1.0*localX - half + peaks->at(npks).getX() - px->at(npks);
					xx2 	= xx*xx;
					yy 		= 1.0*localY - half + peaks->at(npks).getY() - py->at(npks);
					yy2 	= yy*yy;

					rr 		= sqrt(xx2+yy2) + 2.2204E-16; // Por que ese numero?
					rr3 	= rr*rr*rr + 2.2204E-16;

					sech2	= ( 1.0/(cosh( (rr-D/2.0)*w ))  )*( 1.0/(cosh( (rr-D/2.0)*w )) );
					tanh1	= tanh( (rr-D/2.0)*w );

					dipx 	=(-w)*( xx * sech2 / 2.0 / rr);
					dipy 	=(-w)*( yy * sech2 / 2.0 / rr);
					dipxx	=( w)*sech2*(2.0*w*xx2*rr*tanh1-yy2)/2.0 /rr3;
					dipyy	=( w)*sech2*(2.0*w*yy2*rr*tanh1-xx2)/2.0 /rr3;
					dipxy	=( w)*xx*yy*sech2*(2.0*w*rr*tanh1+1.0)/2.0/ rr3;

					chix 	+= diff->getValue(currentX, currentY) * dipx;
					chiy 	+= diff->getValue(currentX, currentY) * dipy;
					chixx	+= dipx*dipx + diff->getValue(currentX, currentY)*dipxx;
					chiyy	+= dipy*dipy + diff->getValue(currentX, currentY)*dipyy;
					chixy	+= dipx*dipy + diff->getValue(currentX, currentY)*dipxy;

					total++;
				}
			}
		}

		statchix+=chix;
		statchiy+=chiy;

		statchixx+=chixx;
		statchiyy+=chiyy;
		statchixy+=chixy;

		dpx.assign(peaks->size(), 0.0);
		dpy.assign(peaks->size(), 0.0);

		double det=chixx*chiyy-chixy*chixy;
		if(fabs(det) < 1E-12){
			detproblem++;
		}else{
			dpx.at(npks) = (chix*chiyy-chiy*chixy)/det;
			dpy.at(npks) = (chix*(-chixy)+chiy*chixx)/det;

			double root = sqrt(dpx.at(npks)*dpx.at(npks) + dpy.at(npks)*dpy.at(npks));
			if(root > maxdr){
				dpx.at(npks) /= root;
				dpy.at(npks) /= root;

				cout << "Jump was too large..." << endl;
			}
		}
	}

	cout << "Total cidp2: " << 1.0*total/peaks->size() << endl;
	cout << "Total of peaks with problems : " << detproblem << endl;
	cout << "Stats: chix=" << statchix << " chiy=" << statchiy << " chixx=" << statchixx << " chiyy=" << statchiyy << " chixy=" << statchixy << endl;

	pair< vector<double>, vector<double> > ret;
	ret.first = dpx;
	ret.second = dpy;

	return ret;
}

unsigned int Chi2Minimization::getMaxIterations(){
	return _maxIterations;
}
int Chi2Minimization::getMinChi2Delta(){
	return _minChi2Delta;
}

void Chi2Minimization::setMaxIterations(unsigned int iterations){
	_maxIterations = iterations;
}
void Chi2Minimization::setMinChi2Delta(int delta){
	_minChi2Delta = delta;
}

void Chi2Minimization::printDescription(){
	cout << "6.- Encuentra una posicion más cercana al centro de las particuals detectadas y minimiza el error Chi2." << endl;
}
