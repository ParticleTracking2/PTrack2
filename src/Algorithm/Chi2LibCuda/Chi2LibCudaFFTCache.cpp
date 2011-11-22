/*
 * Chi2LibCudaFFTCache.cpp
 *
 *  Created on: 22/11/2011
 *      Author: juanin
 */

#include "Chi2LibCudaFFTCache.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Chi2LibCudaFFTCache *Chi2LibCudaFFTCache::instance = 0;
Chi2LibCudaFFTCache::Chi2LibCudaFFTCache() {
	for(unsigned int i = 0; i < capacity; ++i){
		_cache[i] = 0;
		locked[i] = false;
	}
}

Chi2LibCudaFFTCache::~Chi2LibCudaFFTCache() {
	for(unsigned int i = 0; i < capacity; ++i){
		if(_cache[i])
			CHI2HD_destroyArray(_cache[i]);
	}
}

/**
 *******************************
 * Funciones
 *******************************
 */
void Chi2LibCudaFFTCache::erase(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	if(slot <= instance->capacity){
		if(instance->_cache[slot]){
			CHI2HD_destroyArray(instance->_cache[slot]);
			instance->_cache[slot] = 0;
		}
	}
}

void Chi2LibCudaFFTCache::eraseAll(){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	for( unsigned int slot = 0; slot < instance->capacity; ++slot){
		if(instance->_cache[slot])
			CHI2HD_destroyArray(instance->_cache[slot]);
	}
}

void Chi2LibCudaFFTCache::dump(){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	for( unsigned int slot = 0; slot < instance->capacity; ++slot){
		if(instance->_cache[slot]){
//			stringstream ss;
//			ss << "cache-" << slot << ".txt";
//			FileUtils::writeToFileM(instance->_cache[slot], ss.str().c_str());
		}
	}
}

bool Chi2LibCudaFFTCache::empty(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	if(slot <= instance->capacity){
		if(!instance->_cache[slot])
			return true;
		else
			return false;
	}
	return true;
}

bool Chi2LibCudaFFTCache::lock(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	if(slot <= instance->capacity){
		return instance->locked[slot];
	}else
		return true;
}

void Chi2LibCudaFFTCache::lock(unsigned int slot, bool state){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();
	if(slot <= instance->capacity){
		instance->locked[slot] = state;
	}
}

cuMyArray2D *Chi2LibCudaFFTCache::cache(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();

	if(slot <= instance->capacity)
		return instance->_cache[slot];
	return 0;
}

void Chi2LibCudaFFTCache::cache(unsigned int slot, cuMyArray2D* data){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibCudaFFTCache();

	if(slot <= instance->capacity){
		// Borrar si existe
		if(instance->_cache[slot])
			CHI2HD_destroyArray(instance->_cache[slot]);

		instance->_cache[slot] = CHI2HD_createArrayPointer(data->_sizeX, data->_sizeY);
		CHI2HD_copy(data, instance->_cache[slot]);
	}
}
