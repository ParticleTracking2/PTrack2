#Configuration guide
PTrack2 same as the last modified version of *ptracking* can be run in multiple machines and also several instances at the same time, for this, we need to configure some files in order to set servers, instances and others. 
 
##Server configuration
Every server where we run PTrack2 and process images must be configured properly. For this the following steps must be follow: 
 1. The machine must have a user called ***ptrack*** with any password. 
 2. The machine must have installed PTrack2 as appears in [Instalation Guide](install.md) 
 3. In the user folder from ***ptrack*** we must create a folder called ***Out*** with the rights to read and write for the user ***ptrack*** 
 4. Must have access to ***SSH*** though a public key. As explained [Here](http://codeandfury.blogspot.com/2007/01/bash-hacks-scripting-with-ssh.html)
 5. If a Machine will run more than 10 instances of PTrack2 and is not the Host machine, we need to configure the file ***/etc/ssh/sshd_config*** setting the following parameters: 
```sh 
MaxSessions 10 
MaxStartups 10 
``` 
 replacing the number 10 by the necessary quantity. 
 
 >Important: If the machine has Linux installed it needs to have a symbolic link to the user folder as follow: 
```sh 
sudo ln -s /home/ /Users 
``` 
 
##Configure PTrack2Bash
***PTrack2gBash*** has a configuration file inside the user folder called ***.PTrack2Bash.conf*** who is hidden from a normal view. The configuration is explained inside the same file but here we explain with more detail. Note that every line end with the character ***;*** : 
 
 * ***Server IP***: Here we add the IP numbers of the servers that we will use to process data. HOST is the only one who needs to remain unmodified, the rest are optional and the names are arbitrary but are used to identify the server. 
```perl 
#--------------------------------------------- 
# Server IPs 
$HOST='LocalHost'; 
$CUASI1D='172.17.55.7'; 
$GRANOS2D='172.17.55.91'; 
$MPLMFE='172.17.55.65'; 
$COREI7='172.17.55.236'; 
``` 
 
 * ***Servers to use***: This variable represents the order and the servers that we are going to use, the servers needs to be set before in the file and we need to call them with a suffix ***$*** similar to this example. 
```perl 
#--------------------------------------------- 
# Server Array 
@SERVER = ($HOST, $CUASI1D, $MPLMFE, $COREI7); 
``` 
 
 * ***Process Limit***: This values indicates how many images are going to be processed in parallel by each server, the order must match the previous configuration. 
```perl 
#---------------------------------------------------------- 
# Process limit by server to be used. Same order as before 
@PARALLEL_LIMIT = (8, 4, 4, 8); 
``` 
 
 * ***CUDA Servers***: In order to process in a Server with CUDA is necessary to tell the program to use this option, for this is necessary configure with **1** if the server has and is going to use CUDA or **0** otherwise. 
```perl 
#--------------------
# CUDA Enabled 
@CUDA = (0, 0, 0, 1); 
``` 
 
 * ***CUDA Device number***: CUDA can use multiple video cards to process data, in the case of PTrack2, it uses only one device per execution, however, the device to use can be selected as a parameter. To indicate how many devices the server has, we use the parameter **CUDA_DEV**. If the server does not has a CUDA device the value is se to **0**, otherwise we set the value to the number of CUDA devices available. In the case that the server has more than 1 device, the image processing will rotate between the number of devices, for example if there are 2 devices, the first image will be processed using the Device 0, the second image will be processed in the Device 1, the third image will be processed in the Device 0 and so on. 
```perl 
#-----------------------------
# CUDA Device Quantity 
@CUDA_DEV = (0, 0, 0, 2); 
``` 
 
 
 * ***Try Limit***: ***TRY_LIMIT*** represents the number of retries before stop trying to process an image, so, if the time limit expire or there is an error processing the image, the program will try as many times as indicated before discarding. 
```sh 
# Try limit to process an image 
$TRY_LIMIT=3; 
``` 
 
 
 * ***User***: This is the user name that ***ptrackingBash*** will use to connect to all other server. 
```sh 
# User name to connect to other machines 
$USER="ptrack"; 
``` 
 
 
##PTrack2BashFolders Configuration
PTrack2BashFolders needs a configuration file containing the parameters ***D*** and ***W*** for each image folder. Also needs a folder name where to find all the images to process and a folder name where to place all the results for each subfolder. 
 
 1. ***Folder inside a Parent folder where to find the images to process*** 
```sh 
#--------------------------------------- 
IMG_FOLDER="ImgA" 
``` 
 
 2. ***Folder where to save the results inside the Parent Folder*** 
```sh 
#--------------------------------------- 
DEST="XYSL" 
``` 
 
 3. ***D Parameter for each folder to process*** 
```sh 
#-------------- 
# D Values 
Data_D[0]=8.00 
Data_D[1]=8.01 
Data_D[2]=8.02 
... 
``` 
 
 4. ***W Values for each folder to process*** 
```sh 
#-------------- 
# W Values 
Data_W[0]=1.00 
Data_W[1]=1.01 
Data_W[2]=1.02 
... 
```