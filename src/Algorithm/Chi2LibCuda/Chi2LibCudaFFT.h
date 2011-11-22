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
#include "Chi2LibCudaFFTCache.h"

class Chi2LibCudaFFT {
private:
	enum cached{
		cached_kernel = 0,
		cached_kernel2 = 1,
		cached_kernel3 = 2,
		cached_blank = 3,
		cached_first_term = 4,
		cached_second_term = 5,
		cached_third_term = 6
	};
public:
	static void getChiImage(cuMyArray2D *kernel, cuMyArray2D *img, cuMyArray2D *out);
};

#endif /* CHI2LIBCUDAFFT_H_ */
