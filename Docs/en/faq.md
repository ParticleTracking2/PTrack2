#Common Errors

1. ***Cannot read the image file***
```
terminate called after throwing an instance of 'Magick::ErrorMissingDelegate'
  what():  Magick: no decode delegate for this image format `/path/of/image/ImgA000000.tif' @ error/constitute.c/ReadImage/532
```

 ***Solution***
Install the appropriate delegate library: libtiff, libpng, libjpg. All can be downloaded from [Here](http://www.imagemagick.org/download/delegates/) and reinstall [ImageMagick](http://www.imagemagick.org/script/install-source.php).

2. ***Cannot read the image file***
```
terminate called after throwing an instance of 'Magick::ErrorBlob'
  what():  Magick: unable to open image `/path/of/image/ImgA000000.tif':  @ error/blob.c/OpenBlob/2489
```

 ***Solution***
Verify the image path. This can be done by the relative or absolute path of the image.

3. ***Adding the option -display the image is not shown***
***Solution***
Install the library **x11proto-core-dev**. In linux (Ubuntu) as follow:
```
sudo apt-get install x11proto-core-dev
```
next reinstall [ImageMagick](http://www.imagemagick.org/script/install-source.php).

4. ***The selected algorithm is not recognized***
```
2012-01-07 23:40:39,870: ERROR	- [ArgsProcessor][setArgs] No Algorithm Selected: chi2hdcuda 
Primary use as: $ PTrack2 [Algorithm Type] [[Algorithm Argument] ..]
```

 ***Solution***
Verify the version of PTrack2, some version has minor differences. Verify the existence of the algorithm displaying the help of PTrack2 by running it without parameters, or review [wiki:en/use Use].