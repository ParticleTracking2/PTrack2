/*
 * Container.h
 *
 *  Created on: 12-06-2011
 *      Author: juanin
 */
#include <string>
using namespace std;

#ifndef CONTAINER
#define CONTAINER

/**
 * Clase contenedora de datos basicos
 */
class Container {
private:
	/**
	 * Datos de tipo entero
	 */
	int myint;

	/**
	 * Datos de tipo double
	 */
	double mydouble;

	/**
	 * Datos de tipo string
	 */
	string mystring;

	/**
	 * Descripcion del contenido
	 */
	string _description;
public:

	/**
	 * Constructor vacio
	 */
	Container();

	/**
	 * Constructor de tipo entero
	 */
	Container(int integer);

	/**
	 * Constructor de tipo double
	 */
	Container(double dou);

	/**
	 * Constructor de tipo string
	 */
	Container(string str);

	/**
	 * Constructor de tipo char* que se almacena como string
	 */
	Container(char *str);

	/**
	 * Destructor
	 */
	virtual ~Container();

	/**
	 * Reinicia todo el contenido de este contenedor.
	 */
	void clear();

	/**
	 * Establece el dato almacenado de tipo entero al nuevo valor
	 * @param integer Entero a almacenar o reestablecer
	 */
	void setData(int integer);

	/**
	 * Establece el dato almacenado de tipo double al nuevo valor
	 * @param dou Double a almacenar o reestablecer
	 */
	void setData(double dou);

	/**
	 * Establece el dato almacenado de tipo string al nuevo valor
	 * @param str String a almacenar o reestablecer
	 */
	void setData(string str);

	/**
	 * Establece el dato almacenado de tipo string al nuevo valor
	 * @param str Char* a almacenar o reestablecer como string
	 */
	void setData(char *str);

	/**
	 * Establece la descripcion del contenido del contenedor.
	 * @param desc Descripcion del contenido
	 */
	void setDescription(string desc);

	/**
	 * Obtiene los datos almacenados de tipo entero
	 * @return Entero almacenado
	 */
	int getDataInt();

	/**
	 * Obtiene los datos almacenados de tipo double
	 * @return Double almacenado
	 */
	double getDataDouble();

	/**
	 * Obtiene los datos almacenados de tipo string
	 * @return String almacenado
	 */
	string getDataString();

	/**
	 * Obtiene la descripcion de los datos almacenados
	 * @return Descripcion de los datos.
	 */
	string getDescription();
};

#endif
