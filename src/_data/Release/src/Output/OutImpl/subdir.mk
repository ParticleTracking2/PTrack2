################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Output/OutImpl/BinaryOutput.cpp \
../src/Output/OutImpl/ConnectorOutput.cpp \
../src/Output/OutImpl/PlainOutput.cpp \
../src/Output/OutImpl/StandarOutput.cpp 

OBJS += \
./src/Output/OutImpl/BinaryOutput.o \
./src/Output/OutImpl/ConnectorOutput.o \
./src/Output/OutImpl/PlainOutput.o \
./src/Output/OutImpl/StandarOutput.o 

CPP_DEPS += \
./src/Output/OutImpl/BinaryOutput.d \
./src/Output/OutImpl/ConnectorOutput.d \
./src/Output/OutImpl/PlainOutput.d \
./src/Output/OutImpl/StandarOutput.d 


# Each subdirectory must supply rules for building sources it contributes
src/Output/OutImpl/%.o: ../src/Output/OutImpl/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/include/ImageMagick -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


