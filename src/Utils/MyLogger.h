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

class MyLogger {
private:
	log4cpp::Appender *appender;
	log4cpp::PatternLayout *layout;
	log4cpp::Category *category;
	static MyLogger *logger;
	MyLogger();
	virtual ~MyLogger();
	bool fileData;
public:
	static MyLogger *getInstance();
	static void setPriority(log4cpp::Priority::PriorityLevel prior);
	static log4cpp::Category* log();
	static bool logFileData();
	static void logFileData(bool data);
};

#endif /* MYLOGGER */
