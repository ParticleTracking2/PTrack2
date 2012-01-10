################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Image/ImageReader/JPGImageReader.cpp \
../src/Image/ImageReader/PNGImageReader.cpp \
../src/Image/ImageReader/TIFFImageReader.cpp 

OBJS += \
./src/Image/ImageReader/JPGImageReader.o \
./src/Image/ImageReader/PNGImageReader.o \
./src/Image/ImageReader/TIFFImageReader.o 

CPP_DEPS += \
./src/Image/ImageReader/JPGImageReader.d \
./src/Image/ImageReader/PNGImageReader.d \
./src/Image/ImageReader/TIFFImageReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/Image/ImageReader/%.o: ../src/Image/ImageReader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DCHI2CUDA -I/usr/local/include -I/usr/include -I/usr/local/cuda/include -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -march=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


