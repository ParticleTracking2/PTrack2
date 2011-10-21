/*
 * Chi2LibMatrix.cpp
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "Chi2LibMatrix.h"

void Chi2LibMatrix::squareIt(MyMatrix<double> *mtrx){
//	MyLogger::log()->debug("[Chi2LibMatrix] Squaring Matrix");
	for(unsigned int x =0; x < mtrx->sX(); ++x){
		for(unsigned int y =0; y < mtrx->sY(); ++y){
			double tmp = mtrx->getValue(x,y);
			mtrx->at(x,y) = tmp*tmp;
		}
	}
//	MyLogger::log()->debug("[Chi2LibMatrix] Matrix Squared");
}

void Chi2LibMatrix::cubeIt(MyMatrix<double> *mtrx){
//	MyLogger::log()->debug("[Chi2LibMatrix] Cubing Matrix");
	for(unsigned int x =0; x < mtrx->sX(); ++x){
		for(unsigned int y =0; y < mtrx->sX(); ++y){
			double tmp = mtrx->getValue(x,y);
			mtrx->at(x,y) = tmp*tmp*tmp;
		}
	}
//	MyLogger::log()->debug("[Chi2LibMatrix] Matrix Cubed");
}

void Chi2LibMatrix::copy(MyMatrix<double> *in, MyMatrix<double> *out){
	for(unsigned int x=0; x < in->sX(); ++x){
		for(unsigned int y=0; y < in->sY(); ++y){
			out->at(x,y) = in->getValue(x,y);
		}
	}
}

void Chi2LibMatrix::copy(MyMatrix<int> *in, MyMatrix<int> *out){
	for(unsigned int x=0; x < in->sX(); ++x){
		for(unsigned int y=0; y < in->sY(); ++y){
			out->at(x,y) = in->getValue(x,y);
		}
	}
}
