#!/bin/sh

echo "📦 Installing ImageMagick"
sudo port install ImageMagick
echo "✅"

echo "🔄 Linking Magick++ Library"
sudo ln -s /opt/local/lib/libMagick++-6.Q16.5.dylib /opt/local/lib/libMagick++.dylib
sudo ln -s /opt/local/lib/libMagick++-6.Q16.a /opt/local/lib/libMagick++.a
sudo ln -s /opt/local/lib/libMagick++-6.Q16.la /opt/local/lib/libMagick++.la
echo "✅"

echo "🔄 Linking MagickCore Library"
sudo ln -s /opt/local/lib/libMagickCore-6.Q16.2.dylib /opt/local/lib/libMagickCore.dylib
sudo ln -s /opt/local/lib/libMagickCore-6.Q16.a /opt/local/lib/libMagickCore.a
sudo ln -s /opt/local/lib/libMagickCore-6.Q16.la /opt/local/lib/libMagickCore.la
echo "✅"

echo "🔄 Linking MagickWand Library"
sudo ln -s /opt/local/lib/libMagickWand-6.Q16.2.dylib /opt/local/lib/libMagickWand.dylib
sudo ln -s /opt/local/lib/libMagickWand-6.Q16.a /opt/local/lib/libMagickWand.a
sudo ln -s /opt/local/lib/libMagickWand-6.Q16.la /opt/local/lib/libMagickWand.la
echo "✅"

echo "🔄 Linking ImageMagick Headers"
sudo ln -s /opt/local/include/ImageMagick-6 /opt/local/include/ImageMagick
echo "✅"

echo "ImageMagick Installed 🎉"