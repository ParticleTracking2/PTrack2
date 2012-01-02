/*
 * MyPeak.h
 *
 *  Created on: 12/09/2011
 *      Author: juanin
 */

#ifndef MYPEAK
#define MYPEAK

/**
 * Clase para representar un Peak e una Imagen.
 */
class MyPeak {
public:
	/**
	 * Posicion X del Peak como Entero.
	 */
	int x;

	/**
	 * Posicion X del Peak como double.
	 * Este posee mayor presicion.
	 */
	double px;

	/**
	 * Delta de la posicion en X.
	 * Este valor es temporal mientras se intenta centrar en la posicion correcta.
	 */
	double dpx;

	/**
	 * Posicion X del Peak como Entero.
	 */
	int y;

	/**
	 * Posicion X del Peak como double.
	 * Este posee mayor presicion.
	 */
	double py;

	/**
	 * Delta de la posicion en X.
	 * Este valor es temporal mientras se intenta centrar en la posicion correcta.
	 */
	double dpy;

	/**
	 * Intensidad de la Imagen Chi2 del Peak.
	 */
	double intensity;

	/**
	 * Intensidad de la Imagen del Peak.
	 */
	double img_intensity;

	/**
	 * Valor del area de Voronoi del Peak dentro de la Imagen.
	 */
	double vor_area;

	/**
	 * Estado del peak dentro de la Imagen.
	 * Este puede ser Solido (True) o Liquido (False).
	 */
	bool solid;

	/**
	 * Constructor Vacio.
	 */
	MyPeak();

	/**
	 * Constructor segun la posicion X e Y.
	 * @param x Posicion X del Peak.
	 * @param y Posicion Y del Peak.
	 */
	MyPeak(int x, int y);

	/**
	 * Constructor segun la posicion X e Y y la intensidad de Imagen Chi2.
	 * @param x Posicion X del Peak.
	 * @param y Posicion Y del Peak.
	 * @param intensity Intensidad de la Imagen Chi2.
	 */
	MyPeak(int x, int y, double intensity);

	/**
	 * Funcion para ordenar y comparar los Peaks segun intensidad de Imagen Chi2.
	 * Compara segun quien sea menor.
	 * @param first Primer Peak a comparar.
	 * @param first Segundo Peak a comparar.
	 */
	static bool compareMe(MyPeak first, MyPeak second){
		return first.intensity < second.intensity;
	}

	/**
	 * Funcion para ordenar y comparar los Peaks segun intensidad de Imagen.
	 * Compara segun quien sea menor.
	 * @param first Primer Peak a comparar.
	 * @param first Segundo Peak a comparar.
	 */
	static bool compareMeImg(MyPeak first, MyPeak second){
		return first.img_intensity < second.img_intensity;
	}
};

#endif /* MYPEAK */
