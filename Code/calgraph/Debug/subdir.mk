################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FichaJUNG.cpp \
../connection.cpp \
../graphviewer.cpp \
../main.cpp 

OBJS += \
./FichaJUNG.o \
./connection.o \
./graphviewer.o \
./main.o 

CPP_DEPS += \
./FichaJUNG.d \
./connection.d \
./graphviewer.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -Dstl=/usr/include/c++/4.9.2 -D__GXX_EXPERIMENTAL_CXX0X__ -D__cplusplus=201103L -I/usr/include/c++/4.9.2 -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


