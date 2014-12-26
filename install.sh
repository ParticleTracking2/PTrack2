#! /bin/sh

InstallCompilers()
{
	echo "========================"
	echo " Installing G++ Verion 4.4 and 4.8"
	sudo apt-get install g++-4.4
	sudo apt-get install g++-4.8

	echo "========================"
	echo " Installing GCC Verion 4.4 and 4.8"
	sudo apt-get install gcc-4.4
	sudo apt-get install gcc-4.8
}

SwitchTo44()
{
	echo "========================"
	echo " Switching to G++ 4.4 and GCC 4.4"
	sudo rm /usr/bin/gcc
	sudo rm /usr/bin/g++
	sudo ln -s /usr/bin/gcc-4.4 /usr/bin/gcc
	sudo ln -s /usr/bin/g++-4.4 /usr/bin/g++
}

SwitchTo48()
{
	echo "========================"
	echo " Switching to G++ 4.8 and GCC 4.8"
	sudo rm /usr/bin/gcc
	sudo rm /usr/bin/g++
	sudo ln -s /usr/bin/gcc-4.8 /usr/bin/gcc
	sudo ln -s /usr/bin/g++-4.8 /usr/bin/g++
}

AddRepositories()
{
	echo "========================"
	echo " Adding Precise Repository"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ precise universe multiverse"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ precise-updates universe multiverse"

	echo "========================"
	echo " Adding Trusty Repository"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ trusty universe multiverse"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ trusty-updates universe multiverse"

	echo "========================"
	echo " Adding Lucid Repository"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ lucid universe multiverse"
	sudo add-apt-repository "deb http://us.archive.ubuntu.com/ubuntu/ lucid-updates universe multiverse"

	sudo apt-get update
}

InstallDependingLibraries()
{
	echo "========================"
	echo " Installing ImageMagick"
	sudo apt-get install imagemagick libmagick++5 libmagick++-dev

	echo "========================"
	echo " Installing FFTW3"
	sudo apt-get install libfftw3-3 libfftw3-dev
	wget http://www.fftw.org/fftw-3.3.tar.gz
	tar xvf fftw-3.3.tar.gz
	cd fftw-3.3
	./configure
	make
	sudo make install
	cd ..

	echo "========================"
	echo " Installing QHull"
	sudo apt-get install qhull-bin libqhull5 libqhull-dev

	echo "========================"
	echo " Installing Log4Cpp"
	sudo apt-get install liblog4cpp5-dev liblog4cpp5
}

InstallPTrack2()
{
	echo "========================"
	echo " Installing PTrack2"
	cd MakeFiles
	make
	sudo make install
	cd ..
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

	InstallCompilers
	SwitchTo48
	AddRepositories
	InstallDependingLibraries
	SwitchTo44
	InstallPTrack2
	TestPTrack2
}

Main