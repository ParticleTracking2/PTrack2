################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Image/ImageReader.cpp \
../src/Image/MyImage.cpp \
../src/Image/MyImageFactory.cpp 

OBJS += \
./src/Image/ImageReader.o \
./src/Image/MyImage.o \
./src/Image/MyImageFactory.o 

CPP_DEPS += \
./src/Image/ImageReader.d \
./src/Image/MyImage.d \
./src/Image/MyImageFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/Image/%.o: ../src/Image/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/media/Datosi7/workspace/Chi2HD_Cuda/src/Headers" -I/usr/local/include -I/usr/include -I/usr/local/cuda/include -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -march=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


