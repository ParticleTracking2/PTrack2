#! /bin/sh


InstallDependingLibraries()
{
	echo "========================"
	echo " Installing required libraries (Ubuntu 16.04)"
	sudo apt-get install gcc g++ imagemagick libmagick++-dev libmagickwand-dev libfftw3-dev liblog4cpp5v5 liblog4cpp5-dev libxmu-dev libxi-dev freeglut3 freeglut3-dev libqhull-dev

}

InstallPTrack2()
{
	echo "========================"
	echo " Installing PTrack2"
	make clean
	make
	sudo make install
}

TestPTrack2()
{
	echo "========================"
	echo " Testing PTrack2"
	cd src/_data
	PTrack2 chi2hd -i ImgA000000.tif -out data.txt -savedisplay ImgResult.png
	PTrack2 chi2hdcuda -i ImgA000000.tif -out data_cuda.txt -savedisplay ImgResult_cuda.png
	cd ../..
}

PrintUsage()
{
	echo "Automated Install Process"
	echo "This program will install all the components necesary to compile and Run PTrack2"
	echo "The platform target is Ubuntu."
}

Main()
{
	PrintUsage
	echo "========================"
	echo " Installing PTrack2"

	InstallDependingLibraries
	InstallPTrack2
	TestPTrack2
}

Main
