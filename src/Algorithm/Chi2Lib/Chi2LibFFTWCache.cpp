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
		locked[i] = false;
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
	if(slot <= instance->capacity){
		if(instance->_cache[slot]){
			delete instance->_cache[slot];
			instance->_cache[slot] = 0;
		}
		instance->locked[slot] = false;
	}
}

void Chi2LibFFTWCache::eraseAll(){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	for( unsigned int slot = 0; slot < instance->capacity; ++slot){
		if(instance->_cache[slot])
			delete instance->_cache[slot];
		instance->locked[slot] = false;
	}
}

void Chi2LibFFTWCache::dump(){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	for( unsigned int slot = 0; slot < instance->capacity; ++slot){
		if(instance->_cache[slot]){
			stringstream ss;
			ss << "cache-" << slot << ".txt";
			FileUtils::writeToFileM(instance->_cache[slot], ss.str().c_str());
		}
	}
}

bool Chi2LibFFTWCache::empty(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	if(slot <= instance->capacity){
		if(!instance->_cache[slot])
			return true;
		else
			return false;
	}
	return true;
}

bool Chi2LibFFTWCache::lock(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	if(slot <= instance->capacity){
		return instance->locked[slot];
	}else
		return true;
}

void Chi2LibFFTWCache::lock(unsigned int slot, bool state){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();
	if(slot <= instance->capacity){
		instance->locked[slot] = state;
	}
}

MyMatrix<double> * Chi2LibFFTWCache::cache(unsigned int slot){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();

	if(slot <= instance->capacity)
		return instance->_cache[slot];
	return 0;
}

void Chi2LibFFTWCache::cache(unsigned int slot, MyMatrix<double> * data){
	// Crear si no existe.
	if(!instance)
		instance = new Chi2LibFFTWCache();

	if(slot <= instance->capacity){
		// Borrar si existe
		if(instance->_cache[slot])
			delete instance->_cache[slot];

		instance->_cache[slot] = new MyMatrix<double>(data->sX(), data->sY());
		Chi2LibMatrix::copy(data, instance->_cache[slot]);
	}
}
