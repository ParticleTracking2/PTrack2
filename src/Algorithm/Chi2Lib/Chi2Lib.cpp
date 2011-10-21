/*
 * Chi2Lib.cpp
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "Chi2Lib.h"

pair<double, double> Chi2Lib::getHighLow(MyMatrix<double> *mtrx){
	MyLogger::log()->debug("[Chi2Lib][getHighLow] Finding Maximum and Minimum values");
	// Obtener Maximos y Minimos
	double max = mtrx->at(0,0);
	double min = mtrx->at(0,0);
	for(unsigned int x =0; x < mtrx->sX(); ++x){
		for(unsigned int y =0; y < mtrx->sY(); ++y){
			double img_xy = mtrx->at(x,y);
			if(max < img_xy)
				max = img_xy;
			if(min > img_xy)
				min = img_xy;
		}
	}
	MyLogger::log()->debug("[Chi2Lib][getHighLow] Maximum and Minimum values Found: %f and %f", max, min);
	pair<double, double> ret;
	ret.first = max;
	ret.second = min;
	return ret;
}

void Chi2Lib::normalizeImage(MyMatrix<double> *mtrx, double maximum, double minimum){
	MyLogger::log()->debug("[Chi2Lib][normalizeImage] Normalizing data");
	double max, min, dif;
	if(maximum == -1 && minimum == -1){
		pair<double, double> maxMin = getHighLow(mtrx);
		max = maxMin.first;
		min = maxMin.second;
	}else{
		max = maximum;
		min = minimum;
	}
	dif = max-min;

	for(unsigned int x =0; x < mtrx->sX(); ++x){
		for(unsigned int y =0; y < mtrx->sY(); ++y){
			double newval = (1.0*max - mtrx->at(x,y)*1.0)/dif;
			mtrx->at(x,y) = newval;
		}
	}
	MyLogger::log()->debug("[Chi2Lib][normalizeImage] Data Normalized");
}

MyMatrix<double> Chi2Lib::generateKernel(unsigned int ss, unsigned int os, double d, double w){
	MyLogger::log()->debug("[Chi2Lib][generateKernel] Building kernel with ss=%i; os=%i; d=%f; w=%f",ss,os,d,w);

	MyMatrix<double> kernel(ss,ss);
	for(unsigned int x=0; x < ss; ++x)
		for(unsigned int y=0; y < ss; ++y){
			double absolute = abs(sqrt((x-os)*(x-os) + (y-os)*(y-os)));
			double ipfval = (1.0 - tanh((absolute - d/2.0)/w))/2.0;
			kernel.at(x,y) = ipfval;
		}

	MyLogger::log()->debug("[Chi2Lib][generateKernel] Kernel successfuly built");
	return kernel;
}

vector<MyPeak> Chi2Lib::getPeaks(MyMatrix<double> *img, int threshold, int mindistance, int minsep, bool use_threads){
	MyLogger::log()->debug("[Chi2Lib][getPeaks] Obtaining peaks threshold=%i; mindistance=%i; minsep=%i",threshold, mindistance, minsep);

	vector<MyPeak> peaks;
	for(unsigned int x=0; x < img->sX(); ++x){
		for(unsigned int y=0; y < img->sY(); ++y){
			double img_xy = img->getValue(x,y);
			if(img_xy > threshold){
				if(findLocalMinimum(img, x,y, minsep)){
					MyPeak local(x,y, img_xy);
					peaks.push_back(local);
				}
			}
		}
	}

	unsigned int detected = peaks.size();
	MyLogger::log()->info("[Chi2Lib][getPeaks] Peaks detected: %i of %i", detected, img->sX()*img->sY());
	sort(peaks.begin(), peaks.end(), MyPeak::compareMe);
	vector<MyPeak> valids;

	if(use_threads){
		PartitionPeaks p1;
		p1.peaks = &peaks; p1.init = 0; p1.end = peaks.size()/2;
		vector<MyPeak> valids1;
		p1.valids = &valids1; p1.mindistance = mindistance;

		PartitionPeaks p2;
		p2.peaks = &peaks; p2.init = peaks.size()/2; p2.end = peaks.size();
		vector<MyPeak> valids2;
		p2.valids = &valids2; p2.mindistance = mindistance;

		pthread_t thread1, thread2;
		pthread_create(&thread1, NULL, validatePeaksThread, (void *)&p1);
		pthread_create(&thread2, NULL, validatePeaksThread, (void *)&p2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

		for(unsigned int i=0; i<valids1.size(); ++i){
			valids.push_back(valids1.at(i));
		}
		for(unsigned int i=0; i<valids2.size(); ++i){
			valids.push_back(valids2.at(i));
		}
	}else{
		validatePeaks(&peaks, 0, peaks.size(), mindistance, &valids);
	}

	unsigned int valid = valids.size();
	MyLogger::log()->info("[Chi2Lib][getPeaks] Peaks detected valids: %i of %i", valid, detected);
	return valids;
}

bool Chi2Lib::findLocalMinimum(MyMatrix<double> *img, unsigned int imgX, unsigned int imgY, int minsep){
	for(int localX = minsep; localX >= -minsep; --localX){
		for(int localY = minsep; localY >= -minsep; --localY){
			if(!(localX == 0 && localY == 0)){
				int currentX = (imgX+localX);
				int currentY = (imgY+localY);

				if(currentX < 0)
					currentX = img->sX() + currentX;
				if(currentY < 0)
					currentY = img->sY() + currentY;

				currentX = (currentX)% img->sX();
				currentY = (currentY)% img->sY();

				if(img->at(imgX, imgY) <= img->getValue(currentX, currentY))
					return false;
			}
		}
	}
	return true;
}

void Chi2Lib::validatePeaks(vector<MyPeak> *peaks, int init, int end, int mindistance, vector<MyPeak> *valids){
	MyLogger::log()->debug("[Chi2Lib][validatePeaks] Validating Peaks ");
	bool valid = true;
	int mindistance2 = mindistance*mindistance;
	for(int i=init; i < end; ++i){
		valid = true;
		for(unsigned int j=i+1; j < peaks->size(); ++j){
			int difx = peaks->at(i).x - peaks->at(j).x;
			int dify = peaks->at(i).y - peaks->at(j).y;

			if( (difx*difx + dify*dify) < mindistance2){
				valid = false;
				break;
			}
		}
		if(valid){
			valids->push_back(peaks->at(i));
		}
	}

	MyLogger::log()->debug("[Chi2Lib][validatePeaks] Peaks Validated");
}

void *Chi2Lib::validatePeaksThread( void* ptr){
	MyLogger::log()->debug("[Chi2Lib][validatePeaksThread] Validating Peaks ");
	PartitionPeaks *part = (PartitionPeaks*)ptr;
	validatePeaks(part->peaks, part->init, part->end, part->mindistance, part->valids);
	return 0;
}

void Chi2Lib::generateGridImpl(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, int x1, int x2, int y1, int y2, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over){
	unsigned int half=(shift+2);
	MyLogger::log()->debug("[Chi2Lib][generateGridImpl] Half=%i, SS=%i", half, shift);
	unsigned int counter = 0;
	int currentX, currentY;
	double currentDistance = 0.0;
	double currentDistanceAux = 0.0;

	if(!peaks->empty())
	for(int npks = peaks->size()-1; npks >= 0; npks--){
		for(unsigned int localX=0; localX < 2*half+1; ++localX)
			for(unsigned int localY=0; localY < 2*half+1; ++localY){
				MyPeak currentPeak = peaks->at(npks);
				currentX = (int)round(currentPeak.px) - shift + (localX - half);
				currentY = (int)round(currentPeak.py) - shift + (localY - half);

				if( x1 <= currentX && currentX < x2 && y1 <= currentY && currentY < y2 ){
					currentDistance =
							sqrt(grid_x->getValue(currentX, currentY)*grid_x->getValue(currentX, currentY)
								+ grid_y->getValue(currentX, currentY)*grid_y->getValue(currentX, currentY));

					currentDistanceAux =
							sqrt(1.0*(1.0*localX-half+currentPeak.x - currentPeak.px)*(1.0*localX-half+currentPeak.x - currentPeak.px) +
								 1.0*(1.0*localY-half+currentPeak.y - currentPeak.py)*(1.0*localY-half+currentPeak.y - currentPeak.py));

					if(currentDistance >= currentDistanceAux){
						over->at(currentX, currentY) = npks+1;
						grid_x->at(currentX, currentY) = (1.0*localX-half+currentPeak.x)-currentPeak.px;
						grid_y->at(currentX, currentY) = (1.0*localY-half+currentPeak.y)-currentPeak.py;
						counter++;
					}
				}

			}
	}
	MyLogger::log()->debug("[Chi2Lib][generateGridImpl] Auxiliary Matrix Generation Complete");
	MyLogger::log()->debug("[Chi2Lib][generateGridImpl] Total pgrid= %f; Counter= %i", 1.0*counter/peaks->size(), counter);
}

void Chi2Lib::generateGrid(vector<MyPeak> *peaks, unsigned int shift, MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, MyMatrix<int> *over, bool use_threads){
	MyLogger::log()->debug("[Chi2Lib][generateGrid] Generating Auxiliary Matrix");
	unsigned int maxDimension = img->sX() > img->sY() ? img->sX() : img->sY();
	grid_x->reset(maxDimension);
	grid_y->reset(maxDimension);
	over->reset(0);

	if(use_threads){
		PartitionGrid p1; p1.shift = shift;
		p1.peaks = peaks; p1.grid_x = grid_x; p1.grid_y = grid_y; p1.over = over;
		p1.img = img;
		p1.x1 = 0; p1.x2 = img->sX()/2;
		p1.y1 = 0; p1.y2 = img->sY();

		PartitionGrid p2; p2.shift = shift;
		p2.peaks = peaks; p2.grid_x = grid_x; p2.grid_y = grid_y; p2.over = over;
		p2.img = img;
		p2.x1 = img->sX()/2; p2.x2 = img->sX();
		p2.y1 = 0; p2.y2 = img->sY();

		pthread_t thread1, thread2;
		pthread_create(&thread1, NULL, generateGridThread, (void *)&p1);
		pthread_create(&thread2, NULL, generateGridThread, (void *)&p2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		// No quedan iguales, algunos valores se sobreescriben
	}else{
		generateGridImpl(peaks, shift, img, 0, img->sX(), 0 , img->sY(), grid_x, grid_y, over);
	}
}

void *Chi2Lib::generateGridThread( void* ptr){
	PartitionGrid* part = (PartitionGrid *)ptr;
	generateGridImpl(part->peaks, part->shift, part->img, part->x1, part->x2, part->y1, part->y2, part->grid_x, part->grid_y, part->over);
	return 0;
}

double Chi2Lib::computeDifference(MyMatrix<double> *img, MyMatrix<double> *grid_x, MyMatrix<double> *grid_y, double d, double w, MyMatrix<double> *diffout, bool use_threads){
	if(use_threads){
		PartitionDiff p1;
		p1.x1 = 0; p1.x2 = img->sX()/2;
		p1.y1 = 0; p1.y2 = img->sY();
		p1.d = d; p1.w = w;
		p1.img = img; p1.grid_x = grid_x; p1.grid_y = grid_y;
		p1.diffout = diffout;

		PartitionDiff p2;
		p2.x1 = img->sX()/2; p2.x2 = img->sX();
		p2.y1 = 0; p2.y2 = img->sY();
		p2.d = d; p2.w = w;
		p2.img = img; p2.grid_x = grid_x; p2.grid_y = grid_y;
		p2.diffout = diffout;

		pthread_t thread1, thread2;
		pthread_create(&thread1, NULL, computeDifferenceThread, (void *)&p1);
		pthread_create(&thread2, NULL, computeDifferenceThread, (void *)&p2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

		MyLogger::log()->info("[Chi2Lib][computeDifference] Chi2 Error: %f", p1.err + p2.err);
		return p1.err + p2.err;

	}else{
		MyLogger::log()->debug("[Chi2Lib][computeDifference] Computing Chi2 Difference");
		double chi2err = 0.0;
		for(unsigned int x=0; x < img->sX(); ++x){
			for(unsigned int y=0; y < img->sY(); ++y){
				double x2y2 = sqrt(1.0*grid_x->getValue(x,y)*grid_x->getValue(x,y) + 1.0*grid_y->getValue(x,y)*grid_y->getValue(x,y));
				double temp = ((1.0-tanh( (x2y2-d/2.0)/w )) - 2.0*img->getValue(x,y))/2.0;

				diffout->at(x,y) = temp;
				chi2err += temp*temp;
			}
		}
		MyLogger::log()->info("[Chi2Lib][computeDifference] Chi2 Error: %f", chi2err);
		return chi2err;
	}
}

void * Chi2Lib::computeDifferenceThread( void* ptr){
	PartitionDiff *part = (PartitionDiff*) ptr;
	MyMatrix<double> *img = part->img;
	MyMatrix<double> *grid_x = part->grid_x;
	MyMatrix<double> *grid_y = part->grid_y;
	double d = part->d;
	double w = part->w;
	MyMatrix<double> *diffout = part->diffout;

	MyLogger::log()->debug("[Chi2Lib][computeDifferenceThread] Computing Chi2 Difference");
	double chi2err = 0.0;
	for(unsigned int x=part->x1; x < part->x2; ++x){
		for(unsigned int y=part->y1; y < part->y2; ++y){
			double x2y2 = sqrt(1.0*grid_x->getValue(x,y)*grid_x->getValue(x,y) + 1.0*grid_y->getValue(x,y)*grid_y->getValue(x,y));
			double temp = ((1.0-tanh( (x2y2-d/2.0)/w )) - 2.0*img->getValue(x,y))/2.0;

			diffout->at(x,y) = temp;
			chi2err += temp*temp;
		}
	}
	MyLogger::log()->debug("[Chi2Lib][computeDifferenceThread] Chi2 Error: %f", chi2err);

	part->err = chi2err;
	return 0;
}

void Chi2Lib::newtonCenterImpl(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int init, int end,  int shift, double D, double w, double dp, double maxdr){
	MyLogger::log()->debug("[Chi2Lib][newtonCenterImpl] Starting Newton Minimization");
	w = 1.0/w;
	int half = shift+2;

	double statchix = 0.0, statchiy= 0.0, statchixx=0.0, statchiyy=0.0, statchixy=0.0;
	double detproblem = 0;
	int total = 0;

	for(int npks = end-1; npks >= init; npks--){
		double chix, chiy, chixx, chiyy, chixy;
		chix = chiy = chixx = chiyy = chixy = 0;

		for(unsigned int localX=0; localX < (unsigned int)(2*half+1); ++localX){
			for(unsigned int localY=0; localY < (unsigned int)(2*half+1); ++localY){
				double xx, xx2, yy, yy2, rr, rr3;
				double dipx,dipy,dipxx,dipyy,dipxy;
				double sech2, tanh1;

				double currentX = (int)round(peaks->at(npks).px) - shift + (localX - half);
				double currentY = (int)round(peaks->at(npks).py) - shift + (localY - half);

				if( 0 <= currentX && currentX < over->sX() && 0 <= currentY && currentY < over->sY() && over->getValue(currentX,currentY) == npks +1){
					xx 		= 1.0*localX - half + peaks->at(npks).x - peaks->at(npks).px;
					xx2 	= xx*xx;
					yy 		= 1.0*localY - half + peaks->at(npks).y - peaks->at(npks).py;
					yy2 	= yy*yy;

					rr 		= sqrt(xx2+yy2) + 2.2204E-16; // Por que ese numero?
					rr3 	= rr*rr*rr + 2.2204E-16;

					sech2	= ( 1.0/(cosh( (rr-D/2.0)*w ))  )*( 1.0/(cosh( (rr-D/2.0)*w )) );
					tanh1	= tanh( (rr-D/2.0)*w );

					dipx 	=(-w)*( xx * sech2 / 2.0 / rr);
					dipy 	=(-w)*( yy * sech2 / 2.0 / rr);
					dipxx	=( w)*sech2*(2.0*w*xx2*rr*tanh1-yy2)/2.0 /rr3;
					dipyy	=( w)*sech2*(2.0*w*yy2*rr*tanh1-xx2)/2.0 /rr3;
					dipxy	=( w)*xx*yy*sech2*(2.0*w*rr*tanh1+1.0)/2.0/ rr3;

					chix 	+= diff->getValue(currentX, currentY) * dipx;
					chiy 	+= diff->getValue(currentX, currentY) * dipy;
					chixx	+= dipx*dipx + diff->getValue(currentX, currentY)*dipxx;
					chiyy	+= dipy*dipy + diff->getValue(currentX, currentY)*dipyy;
					chixy	+= dipx*dipy + diff->getValue(currentX, currentY)*dipxy;

					total++;
				}
			}
		}

		statchix+=chix;
		statchiy+=chiy;

		statchixx+=chixx;
		statchiyy+=chiyy;
		statchixy+=chixy;

		peaks->at(npks).dpx = 0.0;
		peaks->at(npks).dpy = 0.0;

		double det=chixx*chiyy-chixy*chixy;
		if(fabs(det) < 1E-12){
			detproblem++;
		}else{
			peaks->at(npks).dpx = (chix*chiyy-chiy*chixy)/det;
			peaks->at(npks).dpy = (chix*(-chixy)+chiy*chixx)/det;

			double currentDPX = peaks->at(npks).dpx;
			double currentDPY = peaks->at(npks).dpy;
			double root = sqrt(currentDPX*currentDPX + currentDPY*currentDPY);
			if(root > maxdr){
				peaks->at(npks).dpx /= root;
				peaks->at(npks).dpy /= root;

				MyLogger::log()->debug("[Chi2Lib][newtonCenter] Jump was too large...");
			}
		}
	}
	MyLogger::log()->debug("[Chi2Lib][newtonCenter] Newton Minimization Finished");

	MyLogger::log()->debug("[Chi2Lib][newtonCenter] Total cidp2 : %f", 1.0*total/peaks->size());
	MyLogger::log()->debug("[Chi2Lib][newtonCenter] Total of peaks with problems : %i", detproblem);
	MyLogger::log()->debug("[Chi2Lib][newtonCenter] Stats: chix= %f chiy= %f chixx= %f chiyy= %f chixy = %f", statchix, statchiy, statchixx, statchiyy, statchixy);
}

void Chi2Lib::newtonCenter(MyMatrix<int> *over, MyMatrix<double> *diff, vector<MyPeak> *peaks, int shift, double D, double w, double dp, double maxdr, bool use_threads){
	if(use_threads){
		PartitionNC p1;
		p1.diff = diff; p1.over = over;
		p1.dp = dp;	p1.D = D;
		p1.i_end = peaks->size()/2;	p1.i_ini = 0;
		p1.maxdr = maxdr; p1.peaks = peaks;
		p1.shift = shift; p1.w = w;

		PartitionNC p2;
		p2.diff = diff; p2.over = over;
		p2.dp = dp; p2.D = D;
		p2.i_end = peaks->size();	p2.i_ini = peaks->size()/2;
		p2.maxdr = maxdr; p2.peaks = peaks;
		p2.shift = shift; p2.w = w;

		pthread_t thread1, thread2;
		pthread_create(&thread1, NULL, newtonCenterThread, (void *)&p1);
		pthread_create(&thread2, NULL, newtonCenterThread, (void *)&p2);

		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);

	}else{
		newtonCenterImpl(over, diff, peaks, 0, peaks->size(), shift, D, w, dp, maxdr);
	}
}

void *Chi2Lib::newtonCenterThread( void* ptr){
	PartitionNC *part = (PartitionNC*)ptr;
	MyLogger::log()->debug("[Chi2Lib][newtonCenterThread] Starting Newton Minimization");
	newtonCenterImpl(part->over, part->diff, part->peaks, part->i_ini, part->i_end, part->shift, part->D, part->w, part->dp, part->maxdr);

	return 0;
}

void Chi2Lib::transformPeaks(vector<MyPeak> *peaks, unsigned int ss, unsigned int width, double vor_areaSL){
	MyLogger::log()->info("[Chi2Lib][transformPeaks] Transforming peaks");
	double swap = 0.0;
	for(unsigned int i=0; i < peaks->size(); ++i){
		swap = peaks->at(i).py - ss+1;
		peaks->at(i).py = width - (peaks->at(i).px-ss);
		peaks->at(i).px = swap;
		if(peaks->at(i).vor_area < vor_areaSL && peaks->at(i).vor_area > 0)
			peaks->at(i).solid = true;
	}
	MyLogger::log()->info("[Chi2Lib][transformPeaks] Peaks transformed");
}
