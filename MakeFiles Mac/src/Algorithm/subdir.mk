################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
CPP_SRCS += \
../src/Algorithm/Algorithm.cpp \
../src/Algorithm/AlgorithmExecutor.cpp \
../src/Algorithm/MyPeak.cpp

OBJS += \
./src/Algorithm/Algorithm.o \
./src/Algorithm/AlgorithmExecutor.o \
./src/Algorithm/MyPeak.o

CPP_DEPS += \
./src/Algorithm/Algorithm.d \
./src/Algorithm/AlgorithmExecutor.d \
./src/Algorithm/MyPeak.d


# Each subdirectory must supply rules for building sources it contributes
src/Algorithm/%.o: ../src/Algorithm/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include -I/usr/include -I/usr/local/include/ImageMagick-6 -DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0 -O3 -mtune=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
