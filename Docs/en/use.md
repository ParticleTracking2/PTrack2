#PTrack2 System

The 1.0 Version of PTrack2 is available for Mac OSX and Linux, while the 1.1 version using CUDA is available only for Linux.
PTrack2 can run in one computer for processing a specific images or in several computers at the same time in order to speed up the process.
The instructions of how to use it are also available in the ***man page*** that can be accessed through a terminal by typing the follow:
```sh
juanin@Ubuntu-i5:~$ man PTrack2
```
For systems with Bash Completion enabled (Ubuntu linux), is possible to access all the available parameters of the software by typing twice the **tab** key or if part of the parameter is already written is possible to auto-complete the rest by typing the **tab** key once.
For Mac is possible to install Bash Completion using ***port***:
```sh
Granos2D:~ ptrack$ sudo port install bash-completion
```
Next we must add the following lines to the **.profile** file of the user directory:
```sh
if [ -f /opt/local/etc/bash_completion ]; then
. /opt/local/etc/bash_completion
fi
```


##Primary use
The main mode of use of PTrack2 is process only one image. For this is necessary to open a terminal and run the following command:
```sh
juanin@Ubuntu-i5:~$ PTrack2 [Algorithm Type] [Algorithm options]
```

The current algorithms for particle detection are the following:
### 1. ***chi2***
 Convolution based least-squares fitting particle detection algorithm. The specific acceptable parameters are the following:

   1. ***-i***: ***Required*** parameter that indicates the image to be processed. Must be followed by a relative or absolute path of the image.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif
```

   2. ***-d***: Parameter that represents the diameter of the ideal particle to search inside the image. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***9.87***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif -d 8.5732
```

   3. ***-w***: Parameter that represents how focused is the ideal particle inside the image, also is part of the weight of the mathematical formula that generates the ideal particle. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***1.84***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif -w 1.245681
```
   4. ***-cut***: Parameter that establish the cut in the border of the image in pixels. This is useful to cut garbage in the borders or focus the detection in one specific area. Must be followed by a numerical positive integer value.
    Example:
```sh
// Cut the image 100 pixeles at the Top, Bottom, Left and Right.
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif -cut 100
```
   5. ***-maxchi2miniter***: This parameter establish the limit of the number of iterations that minimize the Chi squared error, The greater the value the longer it will take to process the image and do not ensure a better result. Te default value is 5. Must be followed by a numerical positive integer value.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif -maxchi2miniter 10
```
   6. ***-minsep***: This parameter establish the minimum distance of separation between peacks. Must be followed by a numerical positive integer value. if this parameter is not assigned, by default is establiched as ***1***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2 -i ImgA000000.tif -minsep 10
```

### 2. ***chi2hd***
 Convolution based least-squares fitting particle detection algorithm for images with high density particle systems. The specific parameters that are accepted are the follows:

   1. ***-i***: ***Required*** parameter that indicates the image to be processed. Must be followed by a relative or absolute path of the image.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif
```

   2. ***-d***: Parameter that represents the diameter of the ideal particle to search inside the image. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***9.87***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -d 8.5732
```

   3. ***-w***: Parameter that represents how focused is the ideal particle inside the image, also is part of the weight of the mathematical formula that generates the ideal particle. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***1.84***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -2 1.245681
```

   4. ***-cut***: Parameter that establish the cut in the border of the image in pixels. This is useful to cut garbage in the borders or focus the detection in one specific area. Must be followed by a numerical positive integer value.
    Example:
```sh
// Cut the image 100 pixeles at the Top, Bottom, Left and Right.
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -cut 100
```

   5. ***-maxchi2miniter***: This parameter establish the limit of the number of iterations that minimize the Chi squared error, The greater the value the longer it will take to process the image and do not ensure a better result. The Default Value is 5. Must be followed by a numerical positive integer value.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -maxchi2miniter 10
```

   6. ***-chicut***: This parameter establish the minimum intensity of the chi2 image generated to be recognized as a peak or a real particle. Must be followed by a numerical positive integer. If this parameter is not set, by default is established as ***2***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -chicut 3
```

   7. ***-vorcut***: This parameter establish the minimum value of the Voronoi area of a peak in order to be accepted as a peak or a real particle. This is the first filter that deletes false peaks or false particles detected with the help of the calculated image intensity. Must be followed by a numerical decimal value. If this parameter is not set, by default is established as ***50.0***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -vorcut 48.0
```

   8. ***-vorsl***: This parameter establish the value of the transition of the Voronoi area of a peak in order to establish its matter state as solid or liquid. Must be followed by a numerical decimal value. If this parameter is not set, by default is establish as ***75.0***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -vorsl 74.5
```

   9. ***-2filteri***: This parameter establish a second filter by intensity of image. Must be followed by a numerical decimal value between 0 and 1.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -2filteri 0.85
```

   10. ***-2filterv***: This parameter establish a second filter by Voronoi area of a peak. Must be followed by a numerical decimal value.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -2filterv 48.9
```

    11. ***-minsep***: This parameter establish the minimum distance of separation between peacks. Must be followed by a numerical positive integer value. if this parameter is not assigned, by default is establiched as ***1***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hd -i ImgA000000.tif -minsep 10
```

----

The CUDA version of PTrack2 has the same algorithms and arguments previously exposed plus an implementation that uses the GPU to process the data of chi2hd as follow:

### 3. ***chi2hdcuda***
 Convolution based least-squares fitting particle detection algorithm for images with high density particle systems using GPU to calculate data. The specific parameters that accept this algorithm are the following:

   1. ***-i***: ***Required*** parameter that indicates the image to be processed. Must be followed by a relative or absolute path of the image.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif
```

   2. ***-d***: Parameter that represents the diameter of the ideal particle to search inside the image. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***9.87***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -d 8.5732
```

   3. ***-w***: Parameter that represents how focused is the ideal particle inside the image, also is part of the weight of the mathematical formula that generates the ideal particle. Must be followed by a numerical decimal value. If this parameter is not assigned, by default is established as ***1.84***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -2 1.245681
```

   4. ***-cut***: Parameter that establish the cut in the border of the image in pixels. This is useful to cut garbage in the borders or focus the detection in one specific area. Must be followed by a numerical positive integer value.
    Example:
```sh
// Cut the image 100 pixeles at the Top, Bottom, Left and Right.
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -cut 100
```

   5. ***-maxchi2miniter***: This parameter establish the limit of the number of iterations that minimize the Chi squared error, The greater the value the longer it will take to process the image and do not ensure a better result. Te default value is 5. Must be followed by a numerical positive integer value.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -maxchi2miniter 10
```

   6. ***-chicut***: This parameter establish the minimum intensity of the chi2 image generated to be recognized as a peak or a real particle. Must be followed by a numerical positive integer. If this parameter is not set, by default is established as ***2***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -chicut 3
```

   7. ***-vorcut***: This parameter establish the minimum value of the Voronoi area of a peak in order to be accepted as a peak or a real particle. This is the first filter that deletes false peaks or false particles detected with the help of the calculated image intensity. Must be followed by a numerical decimal value. If this parameter is not set, by default is established as ***50.0***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -vorcut 48.0
```

   8. ***-vorsl***: This parameter establish the value of the transition of the Voronoi area of a peak in order to establish its matter state as solid or liquid. Must be followed by a numerical decimal value. If this parameter is not set, by default is establish as ***75.0***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -vorsl 74.5
```

   9. ***-2filteri***: This parameter establish a second filter by intensity of image. Must be followed by a numerical decimal value between 0 and 1.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -2filteri 0.85
```

   10. ***-2filterv***: This parameter establish a second filter by Voronoi area of a peak. Must be followed by a numerical decimal value.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -2filterv 48.9
```

   11. ***-validateones***: Every time during the process of detecting peaks, each peak is filtered by distance between each oder. This parameter moves the validation once all the possible peaks are found.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -validateones
```

   12. ***-device***: If there is more than one video card or if the video card possess more than one GPU, this parameter selects where the calculations takes place during the data processing. If the parameter is not set, the default value is 0 so the calculations will take place in the first available device.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -device 1
```
    13. ***-minsep***: This parameter establish the minimum distance of separation between peacks. Must be followed by a numerical positive integer value. if this parameter is not assigned, by default is establiched as ***1***.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -minsep 10
```

###General Parameters
PTrack2 accepts a series of general parameters independant to the selected algorithm:
  1. ***-silent***: If this parameter exist, there will be no message displayed in screen unless is the result of the process.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -silent
```

  2. ***-debug***: If this parameter exist, all the messages of the process will be displayed. This is useful for recognize anomalies or failures during the processing.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -debug
```

  3. ***-debugwf***: If this parameter exist, all the messages of the process will be displayed and also some specific debugging files will be created during the process such as matrixes or calculations in between. This is useful for recognize anomalies or failures during the processing and execution states.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -debugwf
```

  4. ***-chrono***: If this file exist, some important messages will be displayed such as the start of the software and the end of the processing. This is useful to obtain a reference of time that took the processing.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -chrono
```

  5. ***-display***: If this parameter exist, the processed image will be displayed including the detected particles. In red the particles in a solid state, in blue the particles in liquid state.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -display
```

  6. ***-savedisplay***: If this parameter exist, the processed image will be displayed including the detected particles. In red the particles in a solid state, in blue the particles in liquid state. The generated image will be saved in the specified path, as an example **PeaksImgA0001.png**.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -savedisplay PeaksImgA0001.png
```

  7. ***-nothreads***: If this parameter exist, all the calculations made using threads will be disabled leaving all the process in a sequential mode. This may be useful in certain computers without HT technology or when running multiple instances.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -nothreads
```

  8. ***-out***: Specify the output of the results to a file in plain text or human readable format. Must be followed by the name of the file using relative or absolute path.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -out output.txt
```

  9. ***-outbin***: Specify the output of the results to a binary file format. The format of the output is composed by a triplet of float32 indicating the **x**, **y** and solid = 1 or liquid state = 0 of the particle, followed by the next triplet and so on. Must be followed by the name of the file using relative or absolute path.
    Example:
```sh
juanin@Ubuntu-i5:~$ PTrack2 chi2hdcuda -i ImgA000000.tif -outbin output.bin
```

##Distributed Mode
PTrack2 can run in several computers at the same time, if PTrack2 is properly [wiki:en/install installed] and [wiki:en/config#Serverconfiguration configured] in each computer.
The distributed mode is called ***PTrack2Bash*** and has the following parameters that needs to be specified in order:

 1. ***Image Folder***: Is the path of the folder where to find the images to be processed.

 2. ***Result Folder***: Is the path of the folder where to save all the results of the process.

 3. ***PTrack2 Parameters***: Correspond to all the possible accepted parameters of PTrack2.

An example of the execution is the followed:
```sh
juanin@Ubuntu-i5:~$ PTrack2Bash ImgA/ XYSL -d 8.275 -w 1.245
```

##Distributed Mode Processing Several Image Folders
This mode facilitates the processing of several image folders. This mode needs a configuration file with the values of D and W for each folder as described [wiki:en/config#PTrack2BashFoldersConfiguration here]. In order to process the folders is required that these follow a specific folder structure:

+**Root Folder**
- **PTrack2BashFolders.conf**
  + ***Acq_A_001***
    + ***ImgA***
  + ***Acq_A_002***
     + ***ImgA***
  + ***Acq_A_003***
     + ***ImgA***
  - ...

Where inside each folder theres one with images, doesn't matter the name of the image folder but the name must be the same for all the folders, also the main folders must be numerated in order ending with 3 numerical digits and sharing the same prefix.
The accepted parameters are the following in order:

 1. ***Folder name prefix***: This is the prefix name of the folders to be processed, this must contain 3 digits as a suffix.

 2. ***Initial Number***: This is the number of the first folder to be processed.

 3. ***Final Number***: Correspond to the number of the final folder to be processed.

An example of the execution is the follow:
```sh
juanin@Ubuntu-i5:~$ PTrack2BashFolders Acq_A_ 1 30
```

##Batch Mode
PTrack2 can run several instances at the same time processing multiples files, this is useful if it has only one computer to process data.
This mode is called ***PTrack2Folder*** and ***PTrack2FolderCuda***. The accepted parameters are the followed in order:

 1. ***Image Folder***: Is the path of the folder where to find the images to be processed.

 2. ***Result Folder***: Is the path of the folder where to save all the results of the process.

 3. ***D***: Correspond to the parameter **-d** of PTrack2.

 4. ***W***: Correspond to the parameter **-w** of PTrack2.

 5. ***Instance Number***: This is the number of instances of PTrack2 that will be launched in parallel to process the images, each instance will process a different image.

An example of execution is the follow:
```sh
juanin@Ubuntu-i5:~$ PTrack2Folder ImgA/ XYSL 8.275 1.245 8
```
