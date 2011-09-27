/*
 * MyPeak.h
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#ifndef MYPEAK
#define MYPEAK

class MyPeak {
private:
	double _x;
	double _y;
	double _intensity;
public:
	MyPeak();
	MyPeak(double x, double y);
	MyPeak(double x, double y, double intensity);

	void setX(double x);
	void setY(double y);
	void setIntensity(double intensity);

	double getX();
	double getY();
	double getIntensity();

	static bool compareMe(MyPeak first, MyPeak second){
		return first.getIntensity() < second.getIntensity();
	}
};

#endif /* MYPEAK */
