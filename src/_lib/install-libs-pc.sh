#!/bin/bash

sudo echo "Sudo required ok"
text="lib_install.log"

touch $text

echo "**************"
echo "*    FFTW    *"
echo "**************"
install_fftw >> $text

echo "**************"
echo "*    ZLIB    *"
echo "**************"
install_zlib >> $text
echo "**************"
echo "*    LPNG    *"
echo "**************"
install_png >> $text
echo "**************"
echo "*    LTIFF   *"
echo "**************"
install_tiff >> $text
echo "**************"
echo "*    LJPG    *"
echo "**************"
install_jpg >> $text
echo "**************"
echo "* ImageMagick*"
echo "**************"
install_im >> $text

echo "**************"
echo "*  QuickHull *"
echo "**************"
install_qh >> $text
echo "Done!"
