################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm/Chi2Lib/Chi2Lib.cpp \
../src/Algorithm/Chi2Lib/Chi2LibFFTW.cpp \
../src/Algorithm/Chi2Lib/Chi2LibFFTWCache.cpp \
../src/Algorithm/Chi2Lib/Chi2LibHighDensity.cpp \
../src/Algorithm/Chi2Lib/Chi2LibMatrix.cpp \
../src/Algorithm/Chi2Lib/Chi2LibQhull.cpp 

OBJS += \
./src/Algorithm/Chi2Lib/Chi2Lib.o \
./src/Algorithm/Chi2Lib/Chi2LibFFTW.o \
./src/Algorithm/Chi2Lib/Chi2LibFFTWCache.o \
./src/Algorithm/Chi2Lib/Chi2LibHighDensity.o \
./src/Algorithm/Chi2Lib/Chi2LibMatrix.o \
./src/Algorithm/Chi2Lib/Chi2LibQhull.o 

CPP_DEPS += \
./src/Algorithm/Chi2Lib/Chi2Lib.d \
./src/Algorithm/Chi2Lib/Chi2LibFFTW.d \
./src/Algorithm/Chi2Lib/Chi2LibFFTWCache.d \
./src/Algorithm/Chi2Lib/Chi2LibHighDensity.d \
./src/Algorithm/Chi2Lib/Chi2LibMatrix.d \
./src/Algorithm/Chi2Lib/Chi2LibQhull.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm/Chi2Lib/%.o: ../src/Algorithm/Chi2Lib/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -mtune=native -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


