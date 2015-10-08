#! /bin/sh
MAC_PORTS="MacPorts-2.3.3.tar.gz"
IMAGEMAGICK="ImageMagick.tar.gz"
LOG4CPP="log4cpp-1.1.2rc1.tar.gz"
FFTW="fftw-3.3.4.tar.gz"
QHULL="qhull-2012.1-src.tgz"
TIFF="tiff-4.0.3.tar.gz"
PNG="libpng-1.6.16.tar.gz"
JPEG="jpegsrc.v9a.tar.gz"

InstallLibrary()
{
	local file=$1;
	local directory=$2;

	echo ">>> Installing $directory"
	cd Libs/Mac
	mkdir $directory
	tar xvf $file -C $directory --strip-components=1
	cd $directory

	./configure
	make
	sudo make install

	cd ..
	rm -rf $directory
	cd ../..
}

InstallLibraries()
{
	#Mac Ports
	InstallLibrary $MAC_PORTS MacPorts
	touch ~/.profile
	echo "PATH=\$PATH:/opt/local/bin" >> ~/.profile
	. ~/.profile
	sudo port -v selfupdate

	#TIFF
	sudo port install tiff
	InstallLibrary $TIFF TiffLib
	#PNG
	sudo port install libpng
	InstallLibrary $PNG PNGLib
	#JPEG
	sudo port install jpeg
	InstallLibrary $JPEG JPEGLib

	#Image Magick
	sudo port install ImageMagick
	InstallLibrary $IMAGEMAGICK ImageMagick
	sudo ln -s /usr/local/include/ImageMagick-6 /usr/local/include/ImageMagick
	sudo ln -s /usr/local/lib/libMagick++-6.Q16.a /usr/local/lib/libMagick++.a
	sudo ln -s /usr/local/lib/libMagick++-6.Q16.dylib /usr/local/lib/libMagick++.dylib
	sudo ln -s /usr/local/lib/libMagickCore-6.Q16.a /usr/local/lib/libMagickCore.a
	sudo ln -s /usr/local/lib/libMagickCore-6.Q16.dylib /usr/local/lib/libMagickCore.dylib
	sudo ln -s /usr/local/lib/libMagickWand-6.Q16.a /usr/local/lib/libMagickWand.a
	sudo ln -s /usr/local/lib/libMagickWand-6.Q16.dylib /usr/local/lib/libMagickWand.dylib

	#Log 4 CPP
	sudo port install log4cpp
	InstallLibrary $LOG4CPP Log4cpp

	#FFTW
	sudo port install fftw-3
	InstallLibrary $FFTW FFTW

	#QHull
	sudo port install qhull
	InstallLibrary $QHULL QHull
	sudo cp /usr/local/bin/qhull /usr/bin
}

InstallPTrack2()
{
	echo ">>> Installing PTrack2"
	cd MakeFiles\ Mac
	make clean
	make
	#sudo make install
	cd ..
}

Main()
{
	InstallLibraries
	InstallPTrack2
}

Main
