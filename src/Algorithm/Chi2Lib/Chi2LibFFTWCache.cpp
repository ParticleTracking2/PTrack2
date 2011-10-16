/*
 * Chi2LibFFTWCache.cpp
 *
 *  Created on: 07/10/2011
 *      Author: juanin
 */

#include "Chi2LibFFTWCache.h"

/**
 *******************************
 * Constructores y Destructores
 *******************************
 */
Chi2LibFFTWCache *Chi2LibFFTWCache::instance = 0;
Chi2LibFFTWCache::Chi2LibFFTWCache() {
	for(unsigned int i = 0; i < capacity; ++i){
		_cache[i] = 0;
	}
}

Chi2LibFFTWCache::~Chi2LibFFTWCache() {
	for(unsigned int i = 0; i < capacity; ++i){
		if(_cache[i])
			delete _cache[i];
	}
}

/**
 *******************************
 * Funciones
 *******************************
 */
void Chi2LibFFTWCache::erase(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	if(0 <= slot && slot <= instance->capacity){
		if(instance->_cache[slot]){
			delete instance->_cache[slot];
			instance->_cache[slot] = 0;
		}
	}
}

bool Chi2LibFFTWCache::empty(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	if(0 <= slot && slot <= instance->capacity){
		if(!instance->_cache[slot])
			return true;
		else
			return false;
	}
	return true;
}

MyMatrix<double> * Chi2LibFFTWCache::cache(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();

	if(0 <= slot && slot <= instance->capacity)
		return instance->_cache[slot];
	return 0;
}

void Chi2LibFFTWCache::cache(unsigned int slot, MyMatrix<double> * data){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();

	if(0 <= slot && slot <= instance->capacity){
		// Borrar si existe
		if(instance->_cache[slot])
			delete instance->_cache[slot];

		instance->_cache[slot] = new MyMatrix<double>(data->sX(), data->sY());
		Chi2LibMatrix::copy(data, instance->_cache[slot]);
	}
}