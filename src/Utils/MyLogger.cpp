/*
 * MyLogger.cpp
 *
 *  Created on: 02/10/2011
 *      Author: juanin
 */

#include "MyLogger.h"
/**
 *******************************
 * Constructores
 *******************************
 */
MyLogger *MyLogger::logger = 0;

MyLogger::MyLogger() {
	appender = new log4cpp::OstreamAppender("OstreamAppender",&cout);
	layout = new log4cpp::PatternLayout();
	layout->setConversionPattern("%d: %p\t- %m %n");
	category = &log4cpp::Category::getInstance("Category");

	appender->setLayout(layout);
	category->setAppender(appender);
	category->setPriority(log4cpp::Priority::INFO);
	fileData = false;
}

MyLogger::~MyLogger() {
	delete logger->appender;
	delete logger->layout;
	delete logger;
}

/**
 *******************************
 * Funciones
 *******************************
 */
MyLogger *MyLogger::getInstance(){
	if(!logger)
		logger = new MyLogger();
	return logger;
}

void MyLogger::setPriority(log4cpp::Priority::PriorityLevel prior){
	logger->category->setPriority(prior);
}

log4cpp::Category* MyLogger::log(){
	return logger->category;
}

bool MyLogger::logFileData(){
	return logger->fileData;
}

void MyLogger::logFileData(bool data){
	logger->fileData = data;
}
