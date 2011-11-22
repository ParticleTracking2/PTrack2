/*
 * Chi2LibCudaFFTCache.h
 *
 *  Created on: 22/11/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDAFFTCACHE_H_
#define CHI2LIBCUDAFFTCACHE_H_

#include "../../Utils/FileUtils.h"
#include "Chi2HD_Cuda.h"
#include <string>
#include <sstream>

class Chi2LibCudaFFTCache {
private:
	static const unsigned int capacity = 7;
	cuMyArray2D _cache[capacity];
	bool locked[capacity];

	static Chi2LibCudaFFTCache *instance;
	Chi2LibCudaFFTCache();
public:
	virtual ~Chi2LibCudaFFTCache();

	static void erase(unsigned int slot);
	static void eraseAll();
	static void dump();
	static bool empty(unsigned int slot);
	static bool lock(unsigned int slot);
	static void lock(unsigned int slot, bool state);
	static cuMyArray2D *cache(unsigned int slot);
	static void cache(unsigned int slot, cuMyArray2D* data);
};

#endif /* CHI2LIBCUDAFFTCACHE_H_ */
