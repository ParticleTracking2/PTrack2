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

/**
 * Clase Singleton de almacenamiento de datos para uso de FFTW.
 * Evita reserva y liberacion de memoria intensivamente. Esta clase solo almacena Punteros por lo que estos no se deben liberar afuera de la clase.
 */
class Chi2LibFFTWCache {
private:

	/**
	 * Maxima Capacidad de datos.
	 */
	static const unsigned int capacity = 5;

	/**
	 * Punteros a las Matrices almacenadas en Cache.
	 */
	MyMatrix<double> *_cache[capacity];

	/**
	 * Bloquedo de datos para impedir modificaciones.
	 * Es solo una bandera, no un bloqueo imperativo.
	 */
	bool locked[capacity];

	/**
	 * Unica instancia de la clase.
	 */
	static Chi2LibFFTWCache *instance;

	/**
	 * Constructor privado.
	 */
	Chi2LibFFTWCache();
public:

	/**
	 * Destructor de la clase.
	 */
	virtual ~Chi2LibFFTWCache();

	/**
	 * Elimina un espacio en el cache indicado por slot.
	 * @param slot Espacio de datos a borrar.
	 */
	static void erase(unsigned int slot);

	/**
	 * Elimina todos los datos almacenados.
	 */
	static void eraseAll();

	/**
	 * Guarda en archivos representados como Matrices todos los datos almacenados actualmente.
	 */
	static void dump();

	/**
	 * Verifica si un espacio se encuentra vacio para almacenar.
	 * @param slot Espacio de datos a chequear.
	 */
	static bool empty(unsigned int slot);

	/**
	 * Verifica el bloqueo de datos dentro de un espacio.
	 * @param slot Espacio de datos a verificar bloqueo.
	 */
	static bool lock(unsigned int slot);

	/**
	 * Establece el bloqueo de datos dentro de un espacio.
	 * @param slot Espacio de datos a establecer bloqueo.
	 */
	static void lock(unsigned int slot, bool state);

	/**
	 * Recupera los datos almacenados dentro del espacio indicado.
	 * @param slot Espacio de datos a recuperar.
	 * @return Puntero de Matriz de datos almacenada.
	 */
	static MyMatrix<double> * cache(unsigned int slot);

	/**
	 * Establece los datos de almacenamiento dentro del espacio indicado.
	 * @param slot Espacio donde guardar los datos
	 * @para data puntero de datos a almacenar.
	 */
	static void cache(unsigned int slot, MyMatrix<double> * data);
};

#endif
