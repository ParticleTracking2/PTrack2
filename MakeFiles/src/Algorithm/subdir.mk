################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Algorithm/Algorithm.cpp \
../src/Algorithm/AlgorithmFactory.cpp \
../src/Algorithm/MyPeak.cpp 

OBJS += \
./src/Algorithm/Algorithm.o \
./src/Algorithm/AlgorithmFactory.o \
./src/Algorithm/MyPeak.o 

CPP_DEPS += \
./src/Algorithm/Algorithm.d \
./src/Algorithm/AlgorithmFactory.d \
./src/Algorithm/MyPeak.d 


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm/%.o: ../src/Algorithm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -march=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


