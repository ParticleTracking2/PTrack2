#Install PTrack2 under MAC OSX

## Pre requirements
In order to install PTrack2 is necessary have installed the last version of ***Xcode*** that can be downloaded from [http://developer.apple.com/xcode/]

##Instalation
To install PTrack2 under Mac OSX is necessary execute the following steps:

 1. ***Install Mac Ports***
   Obtain the package installer for your OSX version from [http://www.macports.org/install.php]

 2. ***Install the image manipulation library ImageMagick***
   This is done in a terminal as follow
   ```sh
sudo port install ImageMagick
```
   Next, Obtain the source code from [http://www.imagemagick.org/script/install-source.php#unix] and type in a terminal:
   ```sh
tar xvf ImageMagick.tar.gz
cd ImageMagick-6.7.3
./configure
make
sudo make install
```

 3. ***Install the logging Log4cpp 1.0 Library***
   Obtain the library from [http://sourceforge.net/projects/log4cpp/files/] and follow the next steps in a terminal as follow:
   ```sh
tar xvf log4cpp-1.0.tar.gz
cd log4cpp-1.0
./configure
make
sudo make install
```

 4. ***Install the fourier transform library FFTW 3.3***
   Obtain the library from [http://www.fftw.org/download.html] and follow the next steps in a terminal as follow:
   ```sh
tar xvf fftw-3.3.tar.gz
cd fftw-3.3
./configure
make
sudo make install
```

 5. ***Install the Convex Hull library qhull-2011.1***
   Obtain the Unix version of the library from [http://www.qhull.org/download/] and follow the next steps in a terminal:
   ```sh
tar xvf qhull-2011.1-src.tgz
cd qhull-2011.1
make
sudo make install
sudo cp /usr/local/bin/qhull /usr/bin
```

 6. ***Obtain the source code of PTrack2 and install***
   Obtain the source code of the last [stable version](../../../../releases) and follow the steps in a terminal. The versions with suffix CUDA has enabled this technology and are not exclusive, this is, a computer without CUDA can work without any problems with this software version:
   ```sh
cd MakeFiles\ Mac
make
sudo make install
```
