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
	struct PartitionFFT{
		MyMatrix<double> *img;
		MyMatrix<double> *kernel_img;
		MyMatrix<double> *output;
	};
	enum cached{
		cached_kernel = 0,
		cached_kernel2 = 1,
		cached_kernel3 = 2,
		cached_blank = 3,
		cached_first_term = 4,
		cached_second_term = 5,
		cached_third_term = 6,
	};
	static pthread_mutex_t mutex1;
	static void *conv2d_fftThread(void *ptr);
	static void conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, MyMatrix<double> *output);
public:
	static void getChiImage(MyMatrix<double> *kernel, MyMatrix<double> *img, MyMatrix<double> *out);
};

#endif
