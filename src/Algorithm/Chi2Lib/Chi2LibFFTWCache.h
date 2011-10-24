/*
 * Chi2LibFFTWCache.h
 *
 *  Created on: 07/10/2011
 *      Author: juanin
 */
#include "../../Utils/FileUtils.h"
#include "../../Container/MyMatrix.h"
#include "Chi2LibMatrix.h"
#include <string>
#include <sstream>

#ifndef CHI2LIBFFTWCACHE
#define CHI2LIBFFTWCACHE

class Chi2LibFFTWCache {
private:
	static const unsigned int capacity = 7;
	MyMatrix<double> *_cache[capacity];
	bool locked[capacity];

	static Chi2LibFFTWCache *instance;
	Chi2LibFFTWCache();
public:
	virtual ~Chi2LibFFTWCache();

	static void erase(unsigned int slot);
	static void eraseAll();
	static void dump();
	static bool empty(unsigned int slot);
	static bool lock(unsigned int slot);
	static void lock(unsigned int slot, bool state);
	static MyMatrix<double> * cache(unsigned int slot);
	static void cache(unsigned int slot, MyMatrix<double> * data);
};

#endif
