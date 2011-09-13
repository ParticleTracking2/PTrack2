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
	unsigned int _x;
	unsigned int _y;
	double _intensity;
public:
	MyPeak();
	MyPeak(unsigned int x, unsigned int y);
	MyPeak(unsigned int x, unsigned int y, double intensity);

	void setX(unsigned int x);
	void setY(unsigned int y);
	void setIntensity(double intensity);

	unsigned int getX();
	unsigned int getY();
	double getIntensity();

	static bool compare(MyPeak first, MyPeak second){
		return (first.getIntensity() > second.getIntensity());
	}
};

#endif /* MYPEAK */
