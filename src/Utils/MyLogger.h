/*
 * MyLogger.h
 *	Clase para Escribir en pantalla todo lo necesario ajustando niveles de importancia.
 *	Esta clase es un Singleton por lo que solo se instancia una vez.
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
	 * Genera la Única instancia de la clase y la retorna.
	 */
	static MyLogger *getInstance();

	/**
	 * Establece la prioridad de escritura que persistira en todas las llamadas.
	 * Estos niveles puede ser los siguientes en orden de importancia:
	 * EMERG  = 0,
	 * FATAL  = 0,
	 * ALERT  = 100,
	 * CRIT   = 200,
	 * ERROR  = 300,
	 * WARN   = 400,
	 * NOTICE = 500,
	 * INFO   = 600,
	 * DEBUG  = 700,
	 * NOTSET = 800
	 */
	static void setPriority(log4cpp::Priority::PriorityLevel prior);

	/**
	 * Retorna el objeto log4cpp::Category para escribir en los distintos niveles posibles.
	 */
	static log4cpp::Category* log();

	/**
	 * Retorna si se escribe en un archivo o en la salida estandar.
	 * No implemetado.
	 */
	static bool logFileData();

	/**
	 * Establece si se escribe en un archivo o en la salida estandar.
	 * No implementado.
	 */
	static void logFileData(bool data);
};

#endif /* MYLOGGER */
