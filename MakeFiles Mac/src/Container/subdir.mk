################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Container/Container.cpp \
../src/Container/ParameterContainer.cpp 

OBJS += \
./src/Container/Container.o \
./src/Container/ParameterContainer.o 

CPP_DEPS += \
./src/Container/Container.d \
./src/Container/ParameterContainer.d 


# Each subdirectory must supply rules for building sources it contributes
src/Container/%.o: ../src/Container/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/ImageMagick -I/usr/local/include/ImageMagick -O3 -mtune=native -mfpmath=sse -ftree-vectorize -funroll-loops -ffast-math -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


