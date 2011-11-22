/*
 * Chi2LibCudaFFT.cpp
 *
 *  Created on: 21-11-2011
 *      Author: ptrack
 */

#include "Chi2LibCudaFFT.h"

void Chi2LibCudaFFT::getChiImage(cuMyArray2D *kernel, cuMyArray2D *img, cuMyArray2D *out){
	MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Using cache");
	if(Chi2LibCudaFFTCache::empty(cached_kernel)){ //Kernel
		Chi2LibCudaFFTCache::cache(cached_kernel, kernel);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_kernel2)){ //Kernel2
		cuMyArray2D kernel_img2 = CHI2HD_createArray(kernel->_sizeX, kernel->_sizeY);
		CHI2HD_copy(kernel, &kernel_img2);
		CHI2HD_squareIt(&kernel_img2);
		Chi2LibCudaFFTCache::cache(cached_kernel2, &kernel_img2);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel^2 Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_kernel3)){ //Kernel3
		cuMyArray2D kernel_img3 = CHI2HD_createArray(kernel->_sizeX, kernel->_sizeY);
		CHI2HD_copy(kernel, &kernel_img3);
		CHI2HD_cubeIt(&kernel_img3);
		Chi2LibCudaFFTCache::cache(cached_kernel3, &kernel_img3);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel^3 Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_blank)){ //Blank
		cuMyArray2D blank = CHI2HD_createArray(img->_sizeX, img->_sizeY);
		CHI2HD_reset(&blank, 1.0f);
		Chi2LibCudaFFTCache::cache(cached_blank, &blank);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Blank Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_first_term)){ //First Term -> conv2d_fft( normaldata, ipf*ipf )
		cuMyArray2D first_term = CHI2HD_createArray(img->_sizeX+kernel->_sizeX-1, img->_sizeY+kernel->_sizeY-1);
		CHI2HD_reset(&first_term, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_first_term, &first_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] First Term Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_second_term)){ //Second Term -> conv2d_fft( normaldata*normaldata, ipf )
		cuMyArray2D second_term = CHI2HD_createArray(img->_sizeX+kernel->_sizeX-1, img->_sizeY+kernel->_sizeY-11);
		CHI2HD_reset(&second_term, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_second_term, &second_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Second Term Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_third_term)){ //Third Term -> conv2d_fft( blank, ipf*ipf*ipf )
		cuMyArray2D third_term = CHI2HD_createArray(img->_sizeX+kernel->_sizeX-1, img->_sizeY+kernel->_sizeY-1);
		CHI2HD_reset(&third_term, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_third_term, &third_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Third Term Cached");
	}

	MyLogger::log()->debug("[Chi2LibCudaFFT] Generating First Convolution");
	CHI2HD_conv2D(img, Chi2LibCudaFFTCache::cache(cached_kernel2), Chi2LibCudaFFTCache::cache(cached_first_term));

	MyLogger::log()->debug("[Chi2LibCudaFFT] Generating Second Convolution");
	cuMyArray2D img2 = CHI2HD_createArray(img->_sizeX, img->_sizeY);
	CHI2HD_copy(img, &img2);
	CHI2HD_squareIt(&img2);
	CHI2HD_conv2D(&img2, Chi2LibCudaFFTCache::cache(cached_kernel), Chi2LibCudaFFTCache::cache(cached_second_term));

	if(!Chi2LibCudaFFTCache::lock(cached_third_term)){
		MyLogger::log()->debug("[Chi2LibCudaFFT] Generating Third Convolution");
		CHI2HD_conv2D(Chi2LibCudaFFTCache::cache(cached_blank), Chi2LibCudaFFTCache::cache(cached_kernel3), Chi2LibCudaFFTCache::cache(cached_third_term));
		Chi2LibCudaFFTCache::lock(cached_third_term, true);
	}

	MyLogger::log()->debug("[Chi2LibCudaFFT] Computing result");
	CHI2HD_fftresutl(Chi2LibCudaFFTCache::cache(cached_first_term), Chi2LibCudaFFTCache::cache(cached_second_term), Chi2LibCudaFFTCache::cache(cached_third_term), out);
	MyLogger::log()->debug("[Chi2LibCudaFFT] Result Computed");
}
