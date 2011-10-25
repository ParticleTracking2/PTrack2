################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Image/ImageReader/ImageReader.cpp \
../src/Image/ImageReader/JPGImageReader.cpp \
../src/Image/ImageReader/PNGImageReader.cpp \
../src/Image/ImageReader/TIFFImageReader.cpp 

OBJS += \
./src/Image/ImageReader/ImageReader.o \
./src/Image/ImageReader/JPGImageReader.o \
./src/Image/ImageReader/PNGImageReader.o \
./src/Image/ImageReader/TIFFImageReader.o 

CPP_DEPS += \
./src/Image/ImageReader/ImageReader.d \
./src/Image/ImageReader/JPGImageReader.d \
./src/Image/ImageReader/PNGImageReader.d \
./src/Image/ImageReader/TIFFImageReader.d 


# Each subdirectory must supply rules for building sources it contributes
src/Image/ImageReader/%.o: ../src/Image/ImageReader/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/ImageMagick -O2 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


