################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Utils/FileUtils.cpp \
../src/Utils/MyLogger.cpp 

OBJS += \
./src/Utils/FileUtils.o \
./src/Utils/MyLogger.o 

CPP_DEPS += \
./src/Utils/FileUtils.d \
./src/Utils/MyLogger.d 


# Each subdirectory must supply rules for building sources it contributes
src/Utils/%.o: ../src/Utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -mtune=native -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


