/*
 * Chi2LibCudaFFTCache.h
 *
 *  Created on: 22/11/2011
 *      Author: juanin
 */

#ifndef CHI2LIBCUDAFFTCACHE_H_
#define CHI2LIBCUDAFFTCACHE_H_

#include "../../Utils/FileUtils.h"
#include "Container/cuMyMatrix.h"
#include "Chi2LibcuMatrix.h"

#include <string>
#include <sstream>

class Chi2LibCudaFFTCache {
private:
	/**
	 * Capacidad Maxima de este contenedor (Numero arbitrario).
	 */
	static const unsigned int capacity = 7;

	/**
	 * Arreglo de punteros.
	 */
	cuMyMatrix* _cache[capacity];

	/**
	 * Arreglo de locks para impedir o chequear la existencia inalterable de un elemento del cache.
	 */
	bool locked[capacity];

	/**
	 * Singleton para este objeto.
	 */
	static Chi2LibCudaFFTCache *instance;

	/**
	 * Constructor privado.
	 */
	Chi2LibCudaFFTCache();
public:
	/**
	 * Destructor virtual.
	 */
	virtual ~Chi2LibCudaFFTCache();

	/**
	 * Elimina un elemento del cache.
	 */
	static void erase(unsigned int slot);

	/**
	 * Elimina todos los elementos del cache.
	 */
	static void eraseAll();

	/**
	 * Escribe en varios archivos el contenido de cada uno de los cache.
	 */
	static void dump();

	/**
	 * Chequea si un slot dentro del contenedor esta vacio.
	 */
	static bool empty(unsigned int slot);

	/**
	 * Bloquea un elemento para no ser modificado.
	 */
	static bool lock(unsigned int slot);

	/**
	 * Establece el bloqueo de un elemento para ser o no modificado.
	 */
	static void lock(unsigned int slot, bool state);

	/**
	 * Retorna el cache del determinado slot.
	 */
	static cuMyMatrix *cache(unsigned int slot);

	/**
	 * Establece los datos del slot. (Solo copia la referencia por motivos de performance, esta no debe ser borrada afuera de la clase)
	 */
	static void cache(unsigned int slot, cuMyMatrix* data);
};

#endif /* CHI2LIBCUDAFFTCACHE_H_ */
