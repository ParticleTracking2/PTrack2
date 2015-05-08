#!/bin/sh

echo "🔄 Linking Magick++ Library"
sudo ln -s /usr/local/lib/libMagick++-6.Q16.6.dylib /usr/local/lib/libMagick++.dylib
sudo ln -s /usr/local/lib/libMagick++-6.Q16.a /usr/local/lib/libMagick++.a
sudo ln -s /usr/local/lib/libMagick++-6.Q16.la /usr/local/lib/libMagick++.la
echo "✅"

echo "🔄 Linking MagickCore Library"
sudo ln -s /usr/local/lib/libMagickCore-6.Q16.2.dylib /usr/local/lib/libMagickCore.dylib
sudo ln -s /usr/local/lib/libMagickCore-6.Q16.a /usr/local/lib/libMagickCore.a
sudo ln -s /usr/local/lib/libMagickCore-6.Q16.la /usr/local/lib/libMagickCore.la
echo "✅"

echo "🔄 Linking MagickWand Library"
sudo ln -s /usr/local/lib/libMagickWand-6.Q16.2.dylib /usr/local/lib/libMagickWand.dylib
sudo ln -s /usr/local/lib/libMagickWand-6.Q16.a /usr/local/lib/libMagickWand.a
sudo ln -s /usr/local/lib/libMagickWand-6.Q16.la /usr/local/lib/libMagickWand.la
echo "✅"

echo "🔄 Linking ImageMagick Headers"
sudo ln -s /usr/local/include/ImageMagick-6 /usr/local/include/ImageMagick
echo "✅"