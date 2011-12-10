/*
 * Chi2LibCudaFFT.h
 *
 *  Created on: 21-11-2011
 *      Author: ptrack
 */

#ifndef CHI2LIBCUDAFFT_H_
#define CHI2LIBCUDAFFT_H_

#include "Container/cuMyMatrix.h"
#include "Chi2LibcuMatrix.h"
#include "Chi2LibcuFFT.h"

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
	static void getChiImage(cuMyMatrix *kernel, cuMyMatrix *img, cuMyMatrix *out);
};

#endif /* CHI2LIBCUDAFFT_H_ */
