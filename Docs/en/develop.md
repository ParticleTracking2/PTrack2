#Developing Particle Tracking 2 under Ubuntu 11.10 x64

>Regarding Ubuntu 11.10, it comes with a series of unstable changes, between those there is a common failure in relation with the connection with proxy servers. A common error is that the packet installer apt-get doesn’t recognize the system proxy so the user needs to modify the following file:

```sh
sudo gedit /etc/apt/apt.conf.d/02proxy
```
Next we need to add the following line:
```sh
Acquire::http::Proxy "http://my-proxy:my-port";
```
>Where *my-proxy* needs to be replaced by the proxy that we are going to use, same as *my-port* where generally this is 8080, 8000, 3128.


##Pre Requirements
 1. Install the proprietary video driver from Nvidia
 2. Install Java JDK as follow:
```sh
sudo add-apt-repository ppa:ferramroberto/java
sudo apt-get update
sudo apt-get install sun-java6-jre sun-java6-jdk
```
 3. Install SVN as follow:
```sh
sudo apt-get install subversion
```
 4. Install the compiler G++ as follow:
```sh
sudo apt-get install g++
```


##Develop using eclipse

 1. Install Eclipse 64bits from [Eclipse Downloads](http://www.eclipse.org/cdt/downloads.php)
> Eclipse in it’s 64bits version using Java from Sun Microsystems has a well known failure that causes the software to suddenly crash. To fix this issue is necessary to modify the file *eclipse.ini* and add at the end the following line **-XX:-!UseCompressedOops**
 2. Install the necessary plugins for SVN - ***SVN Team Provider*** 
 3. Install the necessary SVN connector - ***SVN Kit 1.3.5***
 4. Create a new project from a SVN repository from [http://subversion.assembla.com/svn/particle-tracking-2/] and do a checkout from [http://subversion.assembla.com/svn/particle-tracking-2/trunk]


##Developing using  eclipse with CUDA
***Before installing the CUDA SDK you need to install and activate Nvidia proprietary driver***
 1. Install CUDA SDK.
  1. Download from [Cuda Zone](http://developer.nvidia.com/cuda-toolkit-40) *CUDA Toolkit for Ubuntu Linux 10.10* and *GPU Computing SDK - complete package including all code samples*
  2. Install as follow:
```sh
# Follow the instructions and leave everything by default
sudo ./cudatoolkit_4.0.17_linux_64_ubuntu10.10.run 
# Follow the instructions and leave everything by default
sudo ./gpucomputingsdk_4.0.17_linux.run 
# juanin is the user, change accordingly 
sudo chown juanin:juanin NVIDIA_GPU_Computing_SDK/ 
```
  3. A very important step is download and install GCC and G++ version 4.4 max:
```sh
# Install GCC-4.4 and G++-4.4 if applicable
sudo apt-get install gcc-4.4 g++-4.4
# Link gcc and g++ to version 4.4
sudo rm /usr/bin/gcc /usr/bin/g++
sudo ln -s /usr/bin/gcc-4.4 /usr/bin/gcc
sudo ln -s /usr/bin/g++-4.4 /usr/bin/g++
```
 2. Establish the appropriate system PATH as follow:
```sh
sudo nano /etc/enviroment
```
and add this line to PATH: ***/usr/local/cuda/bin***. In order to check the result we need to go to our personal folder and type ***nvcc --version*** and it will display something like this:
```sh
juanin@Ubuntu-i5:~$ nvcc --version
nvcc: NVIDIA (R) Cuda compiler driver
Copyright (c) 2005-2011 NVIDIA Corporation
Built on Thu_May_12_11:09:45_PDT_2011
Cuda compilation tools, release 4.0, V0.2.1221
```

 3. Establish the path for the dynamic link of the libraries:
```sh
sudo touch /etc/ld.so.conf.d/nvidia_cuda.conf
sudo nano /etc/ld.so.conf.d/nvidia_cuda.conf
```
and add this line: ***/usr/local/cuda/lib64/*** next execute:
```sh
sudo ldconfig
```
 4. Test CUDA examples as follow:
```sh
cd NVIDIA_GPU_Computing_SDK/
sudo apt-get install libxmu-dev
make
```
Verify that everything compiles successfully and test the examples from ***NVIDIA_GPU_Computing_SDK/C/bin/linux/release/*** like this one:
```sh
./deviceQuery
```
and it should display something like [this](../CUDA_Query.txt).

