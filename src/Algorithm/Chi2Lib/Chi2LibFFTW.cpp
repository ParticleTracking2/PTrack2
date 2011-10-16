/*
 * Chi2LibFFTW.cpp
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "Chi2LibFFTW.h"

void Chi2LibFFTW::getChiImage(MyMatrix<double> *kernel, MyMatrix<double> *img, MyMatrix<double> *out, bool use_cache){
	MyLogger::log()->debug("[Chi2LibFFTW] Generating First Convolution");
	//conv2d_fft( normaldata, ipf*ipf )
	MyMatrix<double> first_term 	= getFirstTerm(img, kernel, use_cache); // ~200 Milisegundos

	MyLogger::log()->debug("[Chi2LibFFTW] Generating Second Convolution");
	//conv2d_fft( normaldata*normaldata, ipf )
	MyMatrix<double> second_term 	= getSecondTerm(img, kernel); // ~180 Milisegundos

	MyLogger::log()->debug("[Chi2LibFFTW] Generating Third Convolution");
	//conv2d_fft( blank, ipf*ipf*ipf )
	MyMatrix<double> third_term 	= getThirdTerm(img, kernel, use_cache); // ~170 Milisegundos

	MyLogger::log()->debug("[Chi2LibFFTW] Computing result");
	for(unsigned int x=0; x < first_term.sX(); ++x)
		for(unsigned int y=0; y < first_term.sY(); ++y){
			out->at(x,y) = 1.0/(1.0+ (-2.0*first_term.getValue(x,y) +second_term.getValue(x,y))/third_term.getValue(x,y));
		}
	MyLogger::log()->debug("[Chi2LibFFTW] Result Computed");
}

MyMatrix<double> Chi2LibFFTW::getFirstTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache){
	MyMatrix<double> *kernel_img2;
	if(use_cache){
		MyLogger::log()->debug("[Chi2LibFFTW][getFirstTerm] Using cache");
		if(Chi2LibFFTWCache::empty(0)){
			kernel_img2 = new MyMatrix<double>(kernel_img->sX(), kernel_img->sY());
			Chi2LibMatrix::copy(kernel_img, kernel_img2);
			Chi2LibMatrix::squareIt(kernel_img2);
			Chi2LibFFTWCache::cache(0, kernel_img2);
		}
		kernel_img2 = Chi2LibFFTWCache::cache(0);
	}else{
		MyLogger::log()->debug("[Chi2LibFFTW][getFirstTerm] Using uncached data");
		kernel_img2 = new MyMatrix<double>(kernel_img->sX(), kernel_img->sY());
		Chi2LibMatrix::copy(kernel_img, kernel_img2);
		Chi2LibMatrix::squareIt(kernel_img2);
	}

	MyMatrix<double> ret = conv2d_fft(img, kernel_img2);
	if(!use_cache){
		delete kernel_img2;
	}
	return ret;
}

MyMatrix<double> Chi2LibFFTW::getSecondTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache){
	MyMatrix<double> *img2;
	if(use_cache){
		MyLogger::log()->debug("[Chi2LibFFTW][getSecondTerm] Using cache");
		if(Chi2LibFFTWCache::empty(1)){
			img2 = new MyMatrix<double>(img->sX(), img->sY());
			Chi2LibFFTWCache::cache(1, img2);
		}
		img2 = Chi2LibFFTWCache::cache(1);
		Chi2LibMatrix::copy(img, img2);
		Chi2LibMatrix::squareIt(img2);
	}else{
		MyLogger::log()->debug("[Chi2LibFFTW][getSecondTerm] Using uncached data");
		img2 = new MyMatrix<double>(img->sX(), img->sY());
		Chi2LibMatrix::copy(img, img2);
		Chi2LibMatrix::squareIt(img2);
	}

	MyMatrix<double> ret = conv2d_fft(img2, kernel_img);
	if(!use_cache){
		delete img2;
	}
	return ret;
}

MyMatrix<double> Chi2LibFFTW::getThirdTerm(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache){
	MyMatrix<double> *blank, *kernel_img3;
	if(use_cache){
		MyLogger::log()->debug("[Chi2LibFFTW][getThirdTerm] Using cache");
		if(Chi2LibFFTWCache::empty(2) && Chi2LibFFTWCache::empty(3)){
			blank = new MyMatrix<double>(img->sX(), img->sY(), 1.0);
			kernel_img3 = new MyMatrix<double>(kernel_img->sX(), kernel_img->sY());
			Chi2LibMatrix::copy(kernel_img, kernel_img3);
			Chi2LibMatrix::cubeIt(kernel_img3);

			Chi2LibFFTWCache::cache(2, kernel_img3);
			Chi2LibFFTWCache::cache(3, blank);
		}
		kernel_img3 = Chi2LibFFTWCache::cache(2);
		blank = Chi2LibFFTWCache::cache(3);
	}else{
		MyLogger::log()->debug("[Chi2LibFFTW][getThirdTerm] Using uncached data");
		blank = new MyMatrix<double>(img->sX(), img->sY(), 1.0);
		kernel_img3 = new MyMatrix<double>(kernel_img->sX(), kernel_img->sY());
		Chi2LibMatrix::copy(kernel_img, kernel_img3);
		Chi2LibMatrix::cubeIt(kernel_img3);
	}

	MyMatrix<double> ret = conv2d_fft(blank, kernel_img3);
	if(!use_cache){
		delete blank;
		delete kernel_img3;
	}
	return ret;
}

MyMatrix<double> Chi2LibFFTW::conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, bool use_cache){
	fftw_complex	*fft_image, *fft_kernel;
	fftw_plan       plan_forward_image, plan_forward_kernel, plan_backward;
	//auxiliary structures are necessary because fftw3 optimization plan will destroy it!
	double 			*ifft_result, *data, *kernel;
	int nwidth	=	img->sX()+kernel_img->sX()-1;
	int nheight	=	img->sY()+kernel_img->sY()-1;

	// FFTW Allocs
	//the new size includes zero padding space
	data 		= fftw_alloc_real(nwidth * nheight);
	kernel 		= fftw_alloc_real(nwidth * nheight);
	ifft_result = fftw_alloc_real(nwidth * nheight);

	//fftw handle real fft avoiding redundancy in the complex plane, therefore the nheight/2
	fft_image	= fftw_alloc_complex(nwidth*(int)(floor(nheight/2) + 1));
	fft_kernel	= fftw_alloc_complex(nwidth*(int)(floor(nheight/2) + 1));

	plan_forward_image	= fftw_plan_dft_r2c_2d( nwidth, nheight, data, fft_image, FFTW_ESTIMATE );
	plan_forward_kernel	= fftw_plan_dft_r2c_2d( nwidth, nheight, kernel, fft_kernel, FFTW_ESTIMATE );
	plan_backward		= fftw_plan_dft_c2r_2d( nwidth, nheight, fft_image, ifft_result, FFTW_ESTIMATE );

	//populate kernel and shift input
	for(unsigned int x = 0 ; x < kernel_img->sX() ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y=0; y < kernel_img->sY(); ++y){
			kernel[xnw+ y]= kernel_img->getValue(x,y);
		}
	}

	for(unsigned int x = 0 ; x < img->sX() ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y=0; y < img->sY(); ++y){
			data[xnw+ y]= img->getValue(x,y);
		}
	}

	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] Starting FFTW");
	/** FFT Execute */
		//fft of image
		fftw_execute( plan_forward_image );
		//fft of kernel
		fftw_execute( plan_forward_kernel );

		//convolution in fourier domain
		double f1, f2;
		double nwnh = nwidth*nheight;
		double limit = nwidth * (floor(nheight/2) + 1);
		for(unsigned int i=0; i< limit; ++i){
			f1 = fft_image[i][0]*fft_kernel[i][0] - fft_image[i][1]*fft_kernel[i][1];
			f2 = fft_image[i][0]*fft_kernel[i][1] + fft_image[i][1]*fft_kernel[i][0];

			fft_image[i][0]=f1/(nwnh);
			fft_image[i][1]=f2/(nwnh);
		}

		//ifft of the product
		fftw_execute( plan_backward );
	/** FFT Execute */
	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] FFTW Finished");

	MyMatrix<double> output(nwidth, nheight);
	for(unsigned int x = 0 ; x < output.sX() ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y = 0 ; y < output.sY() ; ++y ){
			output.at(x,y) = ifft_result[xnw+y];
		}
	}

    /* free memory */
    fftw_destroy_plan( plan_forward_image );
    fftw_destroy_plan( plan_forward_kernel );
    fftw_destroy_plan( plan_backward );

    fftw_free( data );
    fftw_free( kernel );
    fftw_free( ifft_result );

    fftw_free( fft_image );
    fftw_free( fft_kernel );

	return output;
}
