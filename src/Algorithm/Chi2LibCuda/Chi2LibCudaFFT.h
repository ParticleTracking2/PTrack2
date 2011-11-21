/*
 * Chi2LibCudaFFT.h
 *
 *  Created on: 21-11-2011
 *      Author: ptrack
 */

#ifndef CHI2LIBCUDAFFT_H_
#define CHI2LIBCUDAFFT_H_

#include "Chi2HD_Cuda.h"
#include "../../Utils/MyLogger.h"

class Chi2LibCudaFFT {
private:
	void conv2d_fft(cuMyArray2D *kernel, cuMyArray2D *img, cuMyArray2D *out);
public:
	static void getChiImage(cuMyArray2D *kernel, cuMyArray2D *img, cuMyArray2D *out);
};

#endif /* CHI2LIBCUDAFFT_H_ */
