################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MQTTTest.cpp \
../src/callbackExample.cpp \
../src/mqttClient2.cpp 

OBJS += \
./src/MQTTTest.o \
./src/callbackExample.o \
./src/mqttClient2.o 

CPP_DEPS += \
./src/MQTTTest.d \
./src/callbackExample.d \
./src/mqttClient2.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


