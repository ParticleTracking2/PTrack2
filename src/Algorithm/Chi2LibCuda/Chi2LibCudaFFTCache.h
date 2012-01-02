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

/**
 * Clase Singleton de almacenamiento de datos para uso de FFTW.
 * Evita reserva y liberacion de memoria intensivamente. Esta clase solo almacena Punteros por lo que estos no se deben liberar afuera de la clase.
 */
class Chi2LibCudaFFTCache {
private:
	/**
	 * Capacidad Maxima de este contenedor (Numero arbitrario).
	 */
	static const unsigned int capacity = 7;

	/**
	 * Punteros a las Matrices almacenadas en Cache.
	 */
	cuMyMatrix* _cache[capacity];

	/**
	 * Bloquedo de datos para impedir modificaciones.
	 * Es solo una bandera, no un bloqueo imperativo.
	 */
	bool locked[capacity];

	/**
	 * Unica instancia de la clase.
	 */
	static Chi2LibCudaFFTCache *instance;

	/**
	 * Constructor privado.
	 */
	Chi2LibCudaFFTCache();
public:
	/**
	 * Destructor de la clase.
	 */
	virtual ~Chi2LibCudaFFTCache();

	/**
	 * Elimina un elemento en el cache indicado por slot.
	 * @param slot Espacio de datos a borrar.
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
	 * @param slot Espacio de datos a chequear.
	 */
	static bool empty(unsigned int slot);

	/**
	 * Verifica si un elemento puede ser modificado.
	 * @param slot Espacio de datos a verificar bloqueo.
	 */
	static bool lock(unsigned int slot);

	/**
	 * Establece el bloqueo de un elemento para ser o no modificado.
	 * @param slot Espacio de datos a bloquear.
	 */
	static void lock(unsigned int slot, bool state);

	/**
	 * Retorna el cache del determinado slot.
	 * @param slot Espacio de datos a recuperar.
	 * @return Puntero de Matriz de datos almacenada.
	 */
	static cuMyMatrix *cache(unsigned int slot);

	/**
	 * Establece los datos del slot. (Solo copia la referencia por motivos de performance, esta no debe ser borrada afuera de la clase)
	 * @param slot Espacio donde guardar los datos
	 * @para data puntero de datos a almacenar.
	 */
	static void cache(unsigned int slot, cuMyMatrix* data);
};

#endif /* CHI2LIBCUDAFFTCACHE_H_ */
