/*
 * Chi2LibFFTW.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */
#include <cmath>
#include "../../Container/MyMatrix.h"
#include "../../Utils/MyLogger.h"
#include "../../Utils/FileUtils.h"
#include "fftw3.h"
#include "Chi2LibMatrix.h"
#include "Chi2LibFFTWCache.h"

#ifndef CHI2LIBFFTW
#define CHI2LIBFFTW

class Chi2LibFFTW {
private:
	static MyMatrix<double> getFirstTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache = true);
	static MyMatrix<double> getSecondTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache = true);
	static MyMatrix<double> getThirdTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache = true);
	static MyMatrix<double> conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache = true);
public:
	static void getChiImage(MyMatrix<double> *kernel, MyMatrix<double> *img, MyMatrix<double> *out, bool use_cache = true);
};

#endif
