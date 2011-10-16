/*
 * Chi2LibFFTWCache.h
 *
 *  Created on: 07/10/2011
 *      Author: juanin
 */
#include "../../Container/MyMatrix.h"
#include "Chi2LibMatrix.h"

#ifndef CHI2LIBFFTWCACHE
#define CHI2LIBFFTWCACHE

class Chi2LibFFTWCache {
private:
	static const unsigned int capacity = 6;
	MyMatrix<double> *_cache[capacity];

	static Chi2LibFFTWCache *instance;
	Chi2LibFFTWCache();
public:
	virtual ~Chi2LibFFTWCache();

	static void erase(unsigned int slot);
	static bool empty(unsigned int slot);
	static MyMatrix<double> * cache(unsigned int slot);
	static void cache(unsigned int slot, MyMatrix<double> * data);
};

#endif
