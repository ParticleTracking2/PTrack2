/*
 * Image.h
 *
 *  Created on: 11-06-2011
 *      Author: juanin
 */
#include "TIFFImageReader.h"

/**
 *******************************
 * Metodos
 *******************************
 */

void *TIFFImageReader::populate(void *ptr){
	Partition* part = (Partition*) ptr;

	MyLogger::log()->debug("[TIFFImageReader][populate] Populating: X1=%i; X2=%i, Y1=%i, Y2=%i", part->x1, part->x2, part->y1 ,part->y2);
	Magick::ColorRGB my_color;
	for(int x = part->x1; x < part->x2; ++x)
		for(int y = part->y1; y < part->y2; ++y){
			my_color = part->mimg->pixelColor(x,y);
			part->img->operator ()(x,y) = my_color.green();
		}
	MyLogger::log()->debug("[TIFFImageReader][populate] Populated");
	return 0;
}

MyImage TIFFImageReader::decodeImageGray(string file){
	MyLogger::log()->debug("[TIFFImageReader] Decoding TIFF Image: %s", file.c_str());
	Magick::Image my_image1, my_image2;
	my_image1.read(file);
	my_image2.read(file);

	my_image1.rotate(90);
	my_image2.rotate(90);


	unsigned int max_x = my_image1.rows();
	unsigned int max_y = my_image1.columns();

	MyImage ret(max_x, max_y);

	Partition p1; p1.img = &ret; p1.mimg = &my_image1;
	p1.x1 = 0; 			p1.x2 = max_x/2;
	p1.y1 = 0; 			p1.y2 = max_y;

	Partition p2; p2.img = &ret; p2.mimg = &my_image2;
	p2.x1 = max_x/2;	p2.x2 = max_x;
	p2.y1 = 0; 			p2.y2 = max_y;

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, populate, (void *)&p1);
	pthread_create(&thread2, NULL, populate, (void *)&p2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	MyLogger::log()->debug("[TIFFImageReader] TIFF Image Decoded");
	return ret;
}

MyImage TIFFImageReader::decodeImageGray(string file, unsigned int cut){
	MyLogger::log()->debug("[TIFFImageReader] Decoding TIFF Image: %s; Cut=%i", file.c_str(), cut);
	Magick::Image my_image1, my_image2;
	my_image1.read(file);
	my_image2.read(file);
	my_image1.crop( Magick::Geometry(my_image1.columns()-2*cut,my_image1.rows()-2*cut,cut, cut, false, false));
	my_image2.crop( Magick::Geometry(my_image2.columns()-2*cut,my_image2.rows()-2*cut,cut, cut, false, false));

	my_image1.rotate(90);
	my_image2.rotate(90);


	unsigned int max_x = my_image1.rows();
	unsigned int max_y = my_image1.columns();

	MyImage ret(max_x, max_y);

	Partition p1; p1.img = &ret; p1.mimg = &my_image1;
	p1.x1 = 0; 			p1.x2 = max_x/2;
	p1.y1 = 0; 			p1.y2 = max_y;

	Partition p2; p2.img = &ret; p2.mimg = &my_image2;
	p2.x1 = max_x/2;	p2.x2 = max_x;
	p2.y1 = 0; 			p2.y2 = max_y;

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, populate, (void *)&p1);
	pthread_create(&thread2, NULL, populate, (void *)&p2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	MyLogger::log()->debug("[TIFFImageReader] TIFF Image Decoded");
	return ret;
}

MyImage TIFFImageReader::decodeImageGray(string file, unsigned int top, unsigned int bottom, unsigned int left, unsigned int right){
	MyLogger::log()->debug("[TIFFImageReader] Decoding TIFF Image: %s", file.c_str());
	Magick::Image my_image1, my_image2;
	my_image1.read(file);
	my_image2.read(file);
	my_image1.crop( Magick::Geometry(my_image1.columns()-left-right,my_image1.rows()-top-bottom,left, top, false, false));
	my_image2.crop( Magick::Geometry(my_image2.columns()-left-right,my_image2.rows()-top-bottom,left, top, false, false));

	my_image1.rotate(90);
	my_image2.rotate(90);


	unsigned int max_x = my_image1.rows();
	unsigned int max_y = my_image1.columns();

	MyImage ret(max_x, max_y);

	Partition p1; p1.img = &ret; p1.mimg = &my_image1;
	p1.x1 = 0; 			p1.x2 = max_x/2;
	p1.y1 = 0; 			p1.y2 = max_y;

	Partition p2; p2.img = &ret; p2.mimg = &my_image2;
	p2.x1 = max_x/2;	p2.x2 = max_x;
	p2.y1 = 0; 			p2.y2 = max_y;

	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, populate, (void *)&p1);
	pthread_create(&thread2, NULL, populate, (void *)&p2);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	MyLogger::log()->debug("[TIFFImageReader] TIFF Image Decoded");
	return ret;
}
