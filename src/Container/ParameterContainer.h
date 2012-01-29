/*
 * ParameterContainer.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <typeinfo>
#include "Container.h"
using namespace std;

#ifndef PARAMETERCONTAINER
#define PARAMETERCONTAINER

/**
 * Clase contenedora de parametros.
 * La implementacion se realiza con un Map de una llave como String y su valor como Un contenedor de datos de distintos tipos (int, double, string).
 */
class ParameterContainer {
private:

	/**
	 * Mapa de llave como string y contenedor de datos.
	 */
	map<string, Container*> my_data;
public:

	/**
	 * Constructor vacio.
	 */
	ParameterContainer();

	/**
	 * Destructor de los datos
	 */
	virtual ~ParameterContainer();

	/**
	 * Agrega un parametro compuesto por una llave y su contenido.
	 * @param key llave unica representando el contenido.
	 * @param data contenido de datos que representa la llave
	 */
	void addParam(string key, Container* data);

	/**
	 * Agrega un parametro compuesto por una llave y su contenido y establece la descripcion de esta.
	 * @param key llave unica representando el contenido.
	 * @param data contenido de datos que representa la llave
	 * @param description descripcion del contenido que representa la llave.
	 */
	void addParam(string key, Container* data, string description);

	/**
	 * Establece el contenido de una llave, solo si esta existe.
	 * @param key llave unica representando el contenido.
	 * @param data nuevo contenido de datos que representa la llave
	 */
	void setParam(string key, Container* data);

	/**
	 * Establece el contenido de una llave y su descripcion, solo si esta existe.
	 * @param key llave unica representando el contenido.
	 * @param data nuevo contenido de datos que representa la llave
	 * @param description descripcion del nuevo contenido.
	 */
	void setParam(string key, Container* data, string description);

	/**
	 * Devuelve todas las llaves actualmente almacenadas en forma de vector.
	 * @return llaves almacenadas.
	 */
	vector <string> getKeys();

	/**
	 * Obtiene y elimina el contenido de una llave.
	 * Una vez realizada esta operacion tanto la llave como su contenido se eliminaran de este contenedor.
	 * @param key llave de datos a obtener.
	 * @return Contenedor de datos de la llave.
	 */
	Container* popParam(string key);

	/**
	 * Obtiene el contenido de una llave.
	 * @param key llave de datos a obtener.
	 * @return Contenedor de datos de la llave.
	 */
	Container* getParam(string key);

	/**
	 * Obtiene el contenido de una llave en forma de entero.
	 * Si la llave no representa un entero, entonces esta funcion puede devolver datos corruptos.
	 * @param key llave de datos a obtener.
	 * @return valor de la llave en forma de entero.
	 */
	int getParamAsInt(string key);

	/**
	 * Obtiene el contenido de una llave en forma de double.
	 * Si la llave no representa un double, entonces esta funcion puede devolver datos corruptos.
	 * @param key llave de datos a obtener.
	 * @return valor de la llave en forma de double.
	 */
	double getParamAsDouble(string key);

	/**
	 * Obtiene el contenido de una llave en forma de string.
	 * Si la llave no representa un string, entonces esta funcion puede devolver datos corruptos.
	 * @param key llave de datos a obtener.
	 * @return valor de la llave en forma de string.
	 */
	string getParamAsString(string key);

	/**
	 * Pregunta si una llave se encuentra almacenada dentro de este contenedor.
	 * Si existe esta llave, la funcion devuelve true, false en caso contrario.
	 * @param key llave a buscar.
	 * @return true si la llave se encuentra, false en caso contrario.
	 */
	bool existParam(string key);

	/**
	 * Presenta el contenido de este contenedor a la salida estandar.
	 */
	void printInformation();
};

#endif
