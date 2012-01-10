/*
 * Chi2LibCudaFFT.cpp
 *
 *  Created on: 21-11-2011
 *      Author: ptrack
 */
#ifdef CHI2CUDA
#include "Chi2LibCudaFFT.h"

void Chi2LibCudaFFT::getChiImage(cuMyMatrix *kernel, cuMyMatrix *img, cuMyMatrix *out){
	MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Using cache");
	if(Chi2LibCudaFFTCache::empty(cached_kernel)){ //Kernel
		Chi2LibCudaFFTCache::cache(cached_kernel, kernel);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_kernel2)){ //Kernel2
		cuMyMatrix* kernel_img2 = new cuMyMatrix(kernel->sizeX(), kernel->sizeY());
		Chi2LibcuMatrix::copy(kernel, kernel_img2);
		Chi2LibcuMatrix::squareIt(kernel_img2);
		Chi2LibCudaFFTCache::cache(cached_kernel2, kernel_img2);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel^2 Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_kernel3)){ //Kernel3
		cuMyMatrix* kernel_img3 = new cuMyMatrix(kernel->sizeX(), kernel->sizeY());
		Chi2LibcuMatrix::copy(kernel, kernel_img3);
		Chi2LibcuMatrix::cubeIt(kernel_img3);
		Chi2LibCudaFFTCache::cache(cached_kernel3, kernel_img3);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Kernel^3 Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_blank)){ //Blank
		cuMyMatrix* blank = new cuMyMatrix(img->sizeX(), img->sizeY(), 1.0f);
		Chi2LibCudaFFTCache::cache(cached_blank, blank);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Blank Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_first_term)){ //First Term -> conv2d_fft( normaldata, ipf*ipf )
		cuMyMatrix* first_term = new cuMyMatrix(img->sizeX()+kernel->sizeX()-1, img->sizeY()+kernel->sizeY()-1, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_first_term, first_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] First Term Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_second_term)){ //Second Term -> conv2d_fft( normaldata*normaldata, ipf )
		cuMyMatrix* second_term = new cuMyMatrix(img->sizeX()+kernel->sizeX()-1, img->sizeY()+kernel->sizeY()-1, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_second_term, second_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Second Term Cached");
	}
	if(Chi2LibCudaFFTCache::empty(cached_third_term)){ //Third Term -> conv2d_fft( blank, ipf*ipf*ipf )
		cuMyMatrix* third_term = new cuMyMatrix(img->sizeX()+kernel->sizeX()-1, img->sizeY()+kernel->sizeY()-1, 0.0f);
		Chi2LibCudaFFTCache::cache(cached_third_term, third_term);
		MyLogger::log()->debug("[Chi2LibCudaFFT][getChiImage] Third Term Cached");
	}

	MyLogger::log()->debug("[Chi2LibCudaFFT] Generating First Convolution");
	Chi2LibcuFFT::conv2D(img, Chi2LibCudaFFTCache::cache(cached_kernel2), Chi2LibCudaFFTCache::cache(cached_first_term));

	MyLogger::log()->debug("[Chi2LibCudaFFT] Generating Second Convolution");
	cuMyMatrix img2(img->sizeX(), img->sizeY());
	Chi2LibcuMatrix::copy(img, &img2);
	Chi2LibcuMatrix::squareIt(&img2);
	Chi2LibcuFFT::conv2D(&img2, Chi2LibCudaFFTCache::cache(cached_kernel), Chi2LibCudaFFTCache::cache(cached_second_term));

	if(!Chi2LibCudaFFTCache::lock(cached_third_term)){
		MyLogger::log()->debug("[Chi2LibCudaFFT] Generating Third Convolution");
		Chi2LibcuFFT::conv2D(Chi2LibCudaFFTCache::cache(cached_blank), Chi2LibCudaFFTCache::cache(cached_kernel3), Chi2LibCudaFFTCache::cache(cached_third_term));
		Chi2LibCudaFFTCache::lock(cached_third_term, true);
	}

	MyLogger::log()->debug("[Chi2LibCudaFFT] Computing result");
	Chi2LibcuFFT::fftresutl(Chi2LibCudaFFTCache::cache(cached_first_term), Chi2LibCudaFFTCache::cache(cached_second_term), Chi2LibCudaFFTCache::cache(cached_third_term), out);
	MyLogger::log()->debug("[Chi2LibCudaFFT] Result Computed");
}

#endif
