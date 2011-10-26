################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Output/Output.cpp \
../src/Output/OutputFactory.cpp 

OBJS += \
./src/Output/Output.o \
./src/Output/OutputFactory.o 

CPP_DEPS += \
./src/Output/Output.d \
./src/Output/OutputFactory.d 


# Each subdirectory must supply rules for building sources it contributes
src/Output/%.o: ../src/Output/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/ImageMagick -O3 -mtune=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


