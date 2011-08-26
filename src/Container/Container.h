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

class Container {
private:
	void* mydata;
	void** mydata2;
	int myint;
	double mydouble;
	string mystring;
public:
	Container();
	Container(int integer);
	Container(double dou);
	Container(string str);
	Container(void* data);
	Container(void** data);
	virtual ~Container();

	void setData(int integer);
	void setData(double dou);
	void setData(string str);
	void setData(void* data);
	void setData(void** data);

	void* getData();
	void** getData2();
	int getDataInt();
	double getDataDouble();
	string getDataString();
};

#endif
