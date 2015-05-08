# Install PTrack2 under Ubuntu Linux 11.10

## Pre Requirements
In a clean instalation of Ubuntu is necessary to install ***g++*** from the package manager or in a terminal as follow:
```sh
sudo apt-get install g++
```

## Instalation
 1. Install Library ***ImageMagick***
```sh
sudo apt-get install imagemagick libmagick++3 libmagick++-dev
```
 2. Install Library ***FFTW***
```sh
sudo apt-get install libfftw3-3 libfftw3-dev
```
After, Download and uncompress the file ***[fftw-3.3.tar.gz](http://www.fftw.org/fftw-3.3.tar.gz)***, install as follow:
```sh
tar xvf fftw-3.3.tar.gz
cd fftw-3.3
./configure
make
sudo make install
```
 3. Install Library ***Qhull***
```sh
sudo apt-get install qhull-bin libqhull5 libqhull-dev
```
 4. Install Library ***Log4cpp***
```sh
sudo apt-get install liblog4cpp-dev liblog4cpp5
```
 5. ***Obtain the source code of PTrack2 and install***
   Obtain the last [stable version](../../../../releases) of the code and follow the next steps in a terminal:
```sh
cd MakeFiles
make
sudo make install
```