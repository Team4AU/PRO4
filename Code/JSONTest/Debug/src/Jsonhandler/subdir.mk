################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Jsonhandler/dataPoint.cpp \
../src/Jsonhandler/jsonHandler.cpp \
../src/Jsonhandler/jsonValidationException.cpp \
../src/Jsonhandler/mqttPayload.cpp \
../src/Jsonhandler/testConfig.cpp 

OBJS += \
./src/Jsonhandler/dataPoint.o \
./src/Jsonhandler/jsonHandler.o \
./src/Jsonhandler/jsonValidationException.o \
./src/Jsonhandler/mqttPayload.o \
./src/Jsonhandler/testConfig.o 

CPP_DEPS += \
./src/Jsonhandler/dataPoint.d \
./src/Jsonhandler/jsonHandler.d \
./src/Jsonhandler/jsonValidationException.d \
./src/Jsonhandler/mqttPayload.d \
./src/Jsonhandler/testConfig.d 


# Each subdirectory must supply rules for building sources it contributes
src/Jsonhandler/%.o: ../src/Jsonhandler/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


