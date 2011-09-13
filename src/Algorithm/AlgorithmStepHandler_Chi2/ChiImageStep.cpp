/*
 * ChiImageStep.cpp
 *
 *  Created on: 26/08/2011
 *      Author: juanin
 */

#include "ChiImageStep.h"

/**
 *******************************
 * Metodos
 *******************************
 */

Array2D<double>* ChiImageStep::conv2d_fft(Array2D<double> *img, Array2D<double> *kernel_img){
	fftw_complex	*fft_image, *fft_kernel;
	fftw_plan       plan_forward_image, plan_forward_kernel, plan_backward;
	//auxiliary structures are necessary because fftw3 optimization plan will destroy it!
	double 			*ifft_result, *data, *kernel;
	int nwidth	=	img->getWidth()+kernel_img->getWidth()-1;
	int nheight	=	img->getHeight()+kernel_img->getHeight()-1;

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
	for(unsigned int i = 0 ; i < kernel_img->getWidth() ; ++i )
		for(unsigned int j=0; j < kernel_img->getHeight(); ++j){
			kernel[i*nwidth+ j]= kernel_img->getValue(i,j);
		}

	for(unsigned int i = 0 ; i < img->getWidth() ; ++i )
		for(unsigned int j=0; j < img->getHeight(); ++j){
			data[i*nwidth+ j]= img->getValue(i,j);
		}

	/** FFT Execute */
		//fft of image
		fftw_execute( plan_forward_image );
		//fft of kernel
		fftw_execute( plan_forward_kernel );

		//convolution in fourier domain
		for(unsigned int i=0; i< nwidth * (floor(nheight/2) + 1) ; ++i){
			fft_image[i][0]=(fft_image[i][0]*fft_kernel[i][0] - fft_image[i][1]*fft_kernel[i][1])/(nwidth*nheight);
			fft_image[i][1]=(fft_image[i][0]*fft_kernel[i][1] + fft_image[i][1]*fft_kernel[i][0])/(nwidth*nheight);
		}

		//ifft of the product
		fftw_execute( plan_backward );
	/** FFT Execute */

	Array2D<double>* output = new Array2D<double>(nwidth, nheight);
	for(unsigned int i=0 ; i < (unsigned int)nwidth ; ++i)
		for(unsigned int j=0; j < (unsigned int)nheight; ++j){
			output->setValue(i,j, ifft_result[i*nwidth+j]);
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

Array2D<double>* ChiImageStep::getFirstTerm(Array2D<double> *img, Array2D<double> *kernel_img){
//	kernel_img->setPower(2);
	Array2D<double> *kernel_img2 = new Array2D<double>(kernel_img); kernel_img2->squareIt();
	Array2D<double> *ret = conv2d_fft(img, kernel_img2);
//	kernel_img->setPower(1);
	return ret;
}
Array2D<double>* ChiImageStep::getSecondTerm(Array2D<double> *img, Array2D<double> *kernel_img){
//	img->setPower(2);
	Array2D<double> *img2 = new Array2D<double>(img); img2->squareIt();
	Array2D<double> *ret = conv2d_fft(img2, kernel_img);
//	img->setPower(1);
	return ret;
}
Array2D<double>* ChiImageStep::getThirdTerm(Array2D<double> *img, Array2D<double> *kernel_img){
//	kernel_img->setPower(3);
	Array2D<double> *kernel_img3 = new Array2D<double>(kernel_img); kernel_img3->cubeIt();
	Array2D<double> *blank = new Array2D<double>(img->getWidth(),img->getHeight(), 1.0);
	Array2D<double> *ret =  conv2d_fft(blank, kernel_img3);
//	kernel_img->setPower(1.0);
	return ret;
}

void ChiImageStep::handleData(ParameterContainer *pc){
	printDescription();
	unsigned int os = (unsigned int)pc->getParam("iOS")->getDataInt();
	unsigned int ss = (unsigned int)pc->getParam("iSS")->getDataInt();
	double d = pc->getParam("dD")->getDataDouble();
	double w = pc->getParam("dW")->getDataDouble();
	Array2D<double> *img = (Array2D<double> *)pc->getParam("normal_image")->getData();
	Array2D<double> *kernel_img = new Array2D<double>(ss,ss);

	double absolute;
	double ipfval;
	for(unsigned int x=0; x < ss; ++x)
		for(unsigned int y=0; y < ss; ++y){
			absolute = abs(sqrt((x-os)*(x-os) + (y-os)*(y-os)));
			ipfval = (1.0 - tanh((absolute - d/2.0)/w))/2.0;
			kernel_img->setValue(x,y,ipfval);
		}

	//conv2d_fft( normaldata, ipf*ipf )
	Array2D<double> *first_term 	= getFirstTerm(img, kernel_img);
	first_term->printInfo();
	//conv2d_fft( normaldata*normaldata, ipf )
	Array2D<double> *second_term 	= getSecondTerm(img, kernel_img);
	second_term->printInfo();
	//conv2d_fft( blank, ipf*ipf*ipf )
	Array2D<double> *third_term 	= getThirdTerm(img, kernel_img);
	third_term->printInfo();
	double newval;
	for(unsigned int x=0; x < first_term->getWidth(); ++x)
		for(unsigned int y=0; y < first_term->getWidth(); ++y){
			newval = 1.0/(1.0+ (-2.0*first_term->getValue(x,y) +second_term->getValue(x,y))/third_term->getValue(x,y));
			first_term->setValue(x,y, newval);
		}
	first_term->printInfo();
	pc->addParam("chi_image", new Container(first_term), "[Array2D<double>] Imagen como Chi2");

	if(next)
		next->handleData(pc);
}
