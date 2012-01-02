/*
 * MyLogger.h
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "log4cpp/Category.hh"
#include "log4cpp/CategoryStream.hh"
#include "log4cpp/OstreamAppender.hh"
#include "log4cpp/PatternLayout.hh"

#ifndef MYLOGGER
#define MYLOGGER

using namespace std;

/**
 * Clase para Escribir en pantalla todo lo necesario ajustando niveles de importancia.
 * Esta clase es un Singleton por lo que solo se instancia una vez y utiliza log4cpp para escribir los datos.
 * Un ejemplo de instancia y uso es la siguiente:
 *
 * MyLogger *mylog = MyLogger::getInstance();
 * mylog->setPriority(log4cpp::Priority::NOTICE);
 *
 * -- Este mensaje se muestra en pantalla.
 * mylog->log()->notice("Hola Mundo!");
 *
 * -- Este mensaje no, debido a la prioridad establecida antes.
 * mylog->log()->debug("Hola Debug");
 */
class MyLogger {
private:
	/**
	 * Elementos importantes de log4cpp
	 */
	log4cpp::Appender *appender;
	log4cpp::PatternLayout *layout;
	log4cpp::Category *category;

	/**
	 * Instancia Unica
	 */
	static MyLogger *logger;

	/**
	 * Constructor privado
	 */
	MyLogger();

	/**
	 * Destructor privado
	 */
	virtual ~MyLogger();

	/**
	 * Indicador de escritura en archivo o no. No se ocupa actualmente.
	 */
	bool fileData;
public:

	/**
	 * Genera una Única instancia de la clase con todos los parametros necesarios para poder ocuparla y la retorna.
	 * @return Única instancia de MyLogger
	 */
	static MyLogger *getInstance();

	/**
	 * Establece la prioridad de escritura que persistira en todas las llamadas.
	 * Estos niveles puede ser los siguientes en orden de importancia:
	 * EMERG, FATAL, ALERT, CRIT, ERROR, WARN, NOTICE, INFO, DEBUG, NOTSET.
	 * @param prior La prioridad de escritura de la clase.
	 */
	static void setPriority(log4cpp::Priority::PriorityLevel prior);

	/**
	 * Retorna el objeto log4cpp::Category para escribir en los distintos niveles posibles.
	 * @return Objeto log4cpp::Category
	 */
	static log4cpp::Category* log();

	/**
	 * Retorna si se escribe en un archivo o en la salida estandar.
	 * No implemetado, Sin embargo se utiliza como flag para escribir en archivos de debug usando la clase FileUtils.
	 * @see FileUtils
	 * @return bool representando si se escribe en un archivo o no.
	 */
	static bool logFileData();

	/**
	 * Establece si se escribe en un archivo o en la salida estandar.
	 * No implementado, Sin embargo se utiliza como flag para escribir en archivos de debug usando la clase FileUtils.
	 * @param data Parametro que determina si escribir en un archivo o salida estandar.
	 */
	static void logFileData(bool data);
};

#endif /* MYLOGGER */
