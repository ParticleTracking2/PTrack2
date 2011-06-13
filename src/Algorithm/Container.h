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
public:
	Container();
	Container(void* data);
	Container(void** data);
	virtual ~Container();

	void setData(void* data);
	void setData(void** data);

	void* getData();
	void** getData2();
};

#endif
