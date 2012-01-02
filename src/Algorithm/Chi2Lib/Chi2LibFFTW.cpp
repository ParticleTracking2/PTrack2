/*
 * Chi2LibFFTW.cpp
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "Chi2LibFFTW.h"
pthread_mutex_t Chi2LibFFTW::mutex1 = PTHREAD_MUTEX_INITIALIZER;

void Chi2LibFFTW::getChiImage(MyMatrix<double> *kernel, MyMatrix<double> *img, MyMatrix<double> *out, bool use_thread){
	MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Using cache");
	if(Chi2LibFFTWCache::empty(cached_kernel)){ //Kernel
		MyMatrix<double> *kernel_img = new MyMatrix<double>(kernel->sX(), kernel->sY());
		Chi2LibMatrix::copy(kernel, kernel_img);
		Chi2LibFFTWCache::cache(cached_kernel, kernel_img);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Kernel Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_kernel2)){ //Kernel2
		MyMatrix<double> *kernel_img2 = new MyMatrix<double>(kernel->sX(), kernel->sY());
		Chi2LibMatrix::copy(kernel, kernel_img2);
		Chi2LibMatrix::squareIt(kernel_img2);
		Chi2LibFFTWCache::cache(cached_kernel2, kernel_img2);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Kernel^2 Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_kernel3)){ //Kernel3
		MyMatrix<double> *kernel_img3 = new MyMatrix<double>(kernel->sX(), kernel->sY());
		Chi2LibMatrix::copy(kernel, kernel_img3);
		Chi2LibMatrix::cubeIt(kernel_img3);
		Chi2LibFFTWCache::cache(cached_kernel3, kernel_img3);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Kernel^3 Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_blank)){ //Blank
		MyMatrix<double> *blank = new MyMatrix<double>(img->sX(), img->sY(), 1.0);
		Chi2LibFFTWCache::cache(cached_blank, blank);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Blank Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_first_term)){ //First Term -> conv2d_fft( normaldata, ipf*ipf )
		MyMatrix<double> *first_term = new MyMatrix<double>(img->sX()+kernel->sX()-1, img->sY()+kernel->sY()-1);
		Chi2LibFFTWCache::cache(cached_first_term, first_term);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] First Term Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_second_term)){ //Second Term -> conv2d_fft( normaldata*normaldata, ipf )
		MyMatrix<double> *second_term = new MyMatrix<double>(img->sX()+kernel->sX()-1, img->sY()+kernel->sY()-1);
		Chi2LibFFTWCache::cache(cached_second_term, second_term);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Second Term Cached");
	}
	if(Chi2LibFFTWCache::empty(cached_third_term)){ //Third Term -> conv2d_fft( blank, ipf*ipf*ipf )
		MyMatrix<double> *third_term = new MyMatrix<double>(img->sX()+kernel->sX()-1, img->sY()+kernel->sY()-1);
		Chi2LibFFTWCache::cache(cached_third_term, third_term);
		MyLogger::log()->debug("[Chi2LibFFTW][getChiImage] Third Term Cached");
	}

	if(use_thread){
		PartitionFFT p1;
		p1.img = img;
		p1.kernel_img = Chi2LibFFTWCache::cache(cached_kernel2);
		p1.output = Chi2LibFFTWCache::cache(cached_first_term);

		PartitionFFT p2;
		MyMatrix<double> img2(img->sX(), img->sY());
		Chi2LibMatrix::copy(img, &img2);
		Chi2LibMatrix::squareIt(&img2);
		p2.img = &img2;
		p2.kernel_img = Chi2LibFFTWCache::cache(cached_kernel);
		p2.output = Chi2LibFFTWCache::cache(cached_second_term);

		pthread_t thread1, thread2, thread3;
		MyLogger::log()->debug("[Chi2LibFFTW] Generating First Convolution");
		pthread_create(&thread1, NULL, conv2d_fftThread, (void *)&p1);
		MyLogger::log()->debug("[Chi2LibFFTW] Generating Second Convolution");
		pthread_create(&thread2, NULL, conv2d_fftThread, (void *)&p2);

		if(!Chi2LibFFTWCache::lock(cached_third_term)){
			PartitionFFT p3;
			p3.img = Chi2LibFFTWCache::cache(cached_blank);
			p3.kernel_img = Chi2LibFFTWCache::cache(cached_kernel3);
			p3.output = Chi2LibFFTWCache::cache(cached_third_term);

			MyLogger::log()->debug("[Chi2LibFFTW] Generating Third Convolution");
			pthread_create(&thread3, NULL, conv2d_fftThread, (void *)&p3);

			pthread_join(thread3, NULL);
			Chi2LibFFTWCache::lock(cached_third_term, true);
		}

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

	}else{
		MyLogger::log()->debug("[Chi2LibFFTW] Generating First Convolution");
		conv2d_fft(img, Chi2LibFFTWCache::cache(cached_kernel2), Chi2LibFFTWCache::cache(cached_first_term));	// ~200 Milisegundos

		MyLogger::log()->debug("[Chi2LibFFTW] Generating Second Convolution");
		MyMatrix<double> img2(img->sX(), img->sY());
		Chi2LibMatrix::copy(img, &img2);
		Chi2LibMatrix::squareIt(&img2);
		conv2d_fft(&img2, Chi2LibFFTWCache::cache(cached_kernel), Chi2LibFFTWCache::cache(cached_second_term)); // ~180 Milisegundos

		if(!Chi2LibFFTWCache::lock(cached_third_term)){
			MyLogger::log()->debug("[Chi2LibFFTW] Generating Third Convolution");
			conv2d_fft(Chi2LibFFTWCache::cache(cached_blank), Chi2LibFFTWCache::cache(cached_kernel3), Chi2LibFFTWCache::cache(cached_third_term)); // ~170 Milisegundos
			Chi2LibFFTWCache::lock(cached_third_term, true);
		}
	}

	MyMatrix<double> *first_term = Chi2LibFFTWCache::cache(cached_first_term);
	MyMatrix<double> *second_term = Chi2LibFFTWCache::cache(cached_second_term);
	MyMatrix<double> *third_term = Chi2LibFFTWCache::cache(cached_third_term);

	MyLogger::log()->debug("[Chi2LibFFTW] Computing result");
	for(unsigned int x=0; x < first_term->sX(); ++x)
		for(unsigned int y=0; y < first_term->sY(); ++y){
			out->at(x,y) = 1.0/(1.0+ (-2.0*first_term->getValue(x,y) +second_term->getValue(x,y))/third_term->getValue(x,y));
		}
	MyLogger::log()->debug("[Chi2LibFFTW] Result Computed");
}

void *Chi2LibFFTW::conv2d_fftThread(void * ptr){
	PartitionFFT *part = (PartitionFFT*)ptr;
	conv2d_fft(part->img, part->kernel_img, part->output);
	return 0;
}

/*****************
 * Version DOUBLE
 *****************/
void Chi2LibFFTW::conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, MyMatrix<double> *output){
	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] Generating Convolution using FFTW");
	fftw_complex	*fft_image, *fft_kernel;
	fftw_plan       plan_forward_image, plan_forward_kernel, plan_backward;
	//auxiliary structures are necessary because fftw3 optimization plan will destroy it!
	double 			*ifft_result, *data, *kernel;
	int nwidth 	=	(int)(img->sX()+kernel_img->sX()-1);
	int nheight	=	(int)(img->sY()+kernel_img->sY()-1);

	pthread_mutex_lock( &mutex1 );
	// FFTW Allocs
	size_t size = (size_t)(nwidth * nheight);
	//the new size includes zero padding space
	data 		= fftw_alloc_real(size);
	kernel 		= fftw_alloc_real(size);
	ifft_result = fftw_alloc_real(size);

	//fftw handle real fft avoiding redundancy in the complex plane, therefore the nheight/2
	size = (size_t)(nwidth*(floor(nheight/2) + 1));
	fft_image	= fftw_alloc_complex(size);
	fft_kernel	= fftw_alloc_complex(size);

	plan_forward_image	= fftw_plan_dft_r2c_2d( nwidth, nheight, data, fft_image, FFTW_ESTIMATE );
	plan_forward_kernel	= fftw_plan_dft_r2c_2d( nwidth, nheight, kernel, fft_kernel, FFTW_ESTIMATE );
	plan_backward		= fftw_plan_dft_c2r_2d( nwidth, nheight, fft_image, ifft_result, FFTW_ESTIMATE );

	pthread_mutex_unlock( &mutex1 );

	//populate kernel and shift input
	for(unsigned int x = 0 ; x < (unsigned int)nwidth ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y=0; y < (unsigned int)nheight; ++y){
			if(x < kernel_img->sX() && y < kernel_img->sY())
				kernel[xnw+ y] = kernel_img->getValue(x,y);
			else
				kernel[xnw+ y] = 0;
		}
	}

	for(unsigned int x = 0 ; x < (unsigned int)nwidth ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y=0; y < (unsigned int)nheight; ++y){
			if(x < img->sX() && y < img->sY())
				data[xnw+ y] = img->getValue(x,y);
			else
				data[xnw+ y] = 0;
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
		double nwnh = (double)(nwidth*nheight);
		unsigned int limit = (unsigned int)(nwidth * (floor(nheight/2) + 1));
		for(unsigned int i=0; i< limit; ++i){
			f1 = fft_image[i][0]*fft_kernel[i][0] - fft_image[i][1]*fft_kernel[i][1];
			f2 = fft_image[i][0]*fft_kernel[i][1] + fft_image[i][1]*fft_kernel[i][0];

			fft_image[i][0]=f1/nwnh;
			fft_image[i][1]=f2/nwnh;
		}

		//ifft of the product
		fftw_execute( plan_backward );
	/** FFT Execute */
	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] FFTW Finished");

	if(output->sX() == (unsigned int)nwidth && output->sY() == (unsigned int)nheight)
	for(unsigned int x = 0 ; x < output->sX() ; ++x ){
		unsigned int xnw = x*nwidth;
		for(unsigned int y = 0 ; y < output->sY() ; ++y ){
			output->at(x,y) = ifft_result[xnw+y];
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
}

/*****************
 * Version FLOAT
 *****************/
//void Chi2LibFFTW::conv2d_fft(MyMatrix<double> *img, MyMatrix<double> *kernel_img, MyMatrix<double> *output){
//	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] Generating Convolution using FFTW");
//	fftwf_complex	*fft_image, *fft_kernel;
//	fftwf_plan       plan_forward_image, plan_forward_kernel, plan_backward;
//	//auxiliary structures are necessary because fftw3 optimization plan will destroy it!
//	float 			*ifft_result, *data, *kernel;
//	int nwidth 	=	(int)(img->sX()+kernel_img->sX()-1);
//	int nheight	=	(int)(img->sY()+kernel_img->sY()-1);
//
//	pthread_mutex_lock( &mutex1 );
//	// FFTW Allocs
//	size_t size = (size_t)(nwidth * nheight);
//	//the new size includes zero padding space
//	data 		= fftwf_alloc_real(size);
//	kernel 		= fftwf_alloc_real(size);
//	ifft_result = fftwf_alloc_real(size);
//
//	//fftw handle real fft avoiding redundancy in the complex plane, therefore the nheight/2
//	size = (size_t)(nwidth*(floor(nheight/2) + 1));
//	fft_image	= fftwf_alloc_complex(size);
//	fft_kernel	= fftwf_alloc_complex(size);
//
//	plan_forward_image	= fftwf_plan_dft_r2c_2d( nwidth, nheight, data, fft_image, FFTW_ESTIMATE );
//	plan_forward_kernel	= fftwf_plan_dft_r2c_2d( nwidth, nheight, kernel, fft_kernel, FFTW_ESTIMATE );
//	plan_backward		= fftwf_plan_dft_c2r_2d( nwidth, nheight, fft_image, ifft_result, FFTW_ESTIMATE );
//
//	pthread_mutex_unlock( &mutex1 );
//
//	//populate kernel and shift input
//	for(unsigned int x = 0 ; x < (unsigned int)nwidth ; ++x ){
//		unsigned int xnw = x*nwidth;
//		for(unsigned int y=0; y < (unsigned int)nheight; ++y){
//			if(x < kernel_img->sX() && y < kernel_img->sY())
//				kernel[xnw+ y] = (float)kernel_img->getValue(x,y);
//			else
//				kernel[xnw+ y] = 0;
//		}
//	}
//
//	for(unsigned int x = 0 ; x < (unsigned int)nwidth ; ++x ){
//		unsigned int xnw = x*nwidth;
//		for(unsigned int y=0; y < (unsigned int)nheight; ++y){
//			if(x < img->sX() && y < img->sY())
//				data[xnw+ y] = (float)img->getValue(x,y);
//			else
//				data[xnw+ y] = 0;
//		}
//	}
//
//	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] Starting FFTW");
//	/** FFT Execute */
//		//fft of image
//		fftwf_execute( plan_forward_image );
//		//fft of kernel
//		fftwf_execute( plan_forward_kernel );
//
//		//convolution in fourier domain
//		float f1, f2;
//		float nwnh = (float)(nwidth*nheight);
//		unsigned int limit = (unsigned int)(nwidth * (floor(nheight/2) + 1));
//		for(unsigned int i=0; i< limit; ++i){
//			f1 = fft_image[i][0]*fft_kernel[i][0] - fft_image[i][1]*fft_kernel[i][1];
//			f2 = fft_image[i][0]*fft_kernel[i][1] + fft_image[i][1]*fft_kernel[i][0];
//
//			fft_image[i][0]=f1/nwnh;
//			fft_image[i][1]=f2/nwnh;
//		}
//
//		//ifft of the product
//		fftwf_execute( plan_backward );
//	/** FFT Execute */
//	MyLogger::log()->debug("[Chi2LibFFTW][conv2d_fft] FFTW Finished");
//
//	if(output->sX() == (unsigned int)nwidth && output->sY() == (unsigned int)nheight)
//	for(unsigned int x = 0 ; x < output->sX() ; ++x ){
//		unsigned int xnw = x*nwidth;
//		for(unsigned int y = 0 ; y < output->sY() ; ++y ){
//			output->at(x,y) = ifft_result[xnw+y];
//		}
//	}
//
//    /* free memory */
//    fftwf_destroy_plan( plan_forward_image );
//    fftwf_destroy_plan( plan_forward_kernel );
//    fftwf_destroy_plan( plan_backward );
//
//    fftwf_free( data );
//    fftwf_free( kernel );
//    fftwf_free( ifft_result );
//
//    fftwf_free( fft_image );
//    fftwf_free( fft_kernel );
//}
