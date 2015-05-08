#Instalation Guide

##CUDA Version
Before compiling is necessary to install a special library called ***[wiki:en/install/chi2hdlib Chi2HD_Cuda]***.

##Version with/without CUDA
Here is a guide to install PTrack2 for [Mac OSX](install_mac.md) and [Ubuntu Linux](install_ubuntu.md).

##Verification
In order to verify that PTrack2 is working properly, the user can do a benchmark as follow:
```sh
juanin@Ubuntu-i5:~$ cd src/_data
juanin@Ubuntu-i5:~$ ./benchmarck.sh linux
```
Replacing ***linux*** with ***mac*** if is the case. This will generate a file called ***log-ref.txt*** where we can find the execution times of PTrack2 for 1 to 8 images in parallel.