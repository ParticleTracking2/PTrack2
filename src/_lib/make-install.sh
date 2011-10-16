#!/bin/bash

sudo echo "Sudo required ok"
text="lib_install.log"

touch $text
fftw="fftw-3.3"
zlib="zlib-1.2.5"
lpng="libpng-1.5.4"
ltiff="tiff-3.9.5"
ljpg="jpeg-8"
imgmagick="ImageMagick-6.7.1-10"
qh="qhull-2011.1"

function make_me {
	echo ">>Making $1"
	make
	echo ">>Installing $1"
	sudo make install
	cd ..
	echo ">>$1 Complete"
}

function config_me {
	echo ">>Configuring $1"
	./configure
}

function install_fftw {
	echo ">>Processing FFTW"
	cd $fftw
	echo ">>Configuring FFTW"
	./configure --enable-threads # Para linux x86
	#./configure --enable-threads CC="gcc -arch i386 -arch x86_64 -m32" CXX="g++ -arch i386 -arch x86_64 -m32" CPP="gcc -E" CXXCPP="g++ -E" # Para MacOSX
	make_me "FFTW"
}

function install_zlib {
	cd $zlib
	config_me $zlib
	make_me $zlib
}

function install_png {
	cd $lpng
	config_me $lpng
	make_me $lpng
}

function install_tiff {
	cd $ltiff
	config_me $ltiff
	make_me $ltiff
}

function install_jpg {
	cd $ljpg
	config_me $ljpg
	make_me $ljpg
}

function install_im {
	cd $imgmagick
	config_me $imgmagick
	make_me $imgmagick
	sudo ldconfig /usr/local/lib
	sudo ldconfig /usr/lib
}

function install_qh {
	cd $qh
	make_me $qh
}

echo "**************"
echo "*    FFTW    *"
echo "**************"
install_fftw >> $text

echo "**************"
echo "*    ZLIB    *"
echo "**************"
install_zlib >> $text
echo "**************"
echo "*    LPNG    *"
echo "**************"
install_png >> $text
echo "**************"
echo "*    LTIFF   *"
echo "**************"
install_tiff >> $text
echo "**************"
echo "*    LJPG    *"
echo "**************"
install_jpg >> $text
echo "**************"
echo "* ImageMagick*"
echo "**************"
install_im >> $text

echo "**************"
echo "*  QuickHull *"
echo "**************"
install_qh >> $text
echo "Done!"
