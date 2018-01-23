################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../examples/FEMmetal.cpp 

OBJS += \
./examples/FEMmetal.o 

CPP_DEPS += \
./examples/FEMmetal.d 


# Each subdirectory must supply rules for building sources it contributes
examples/%.o: ../examples/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/home/majernik/Programming/C++/FEM3/include/Eigen -I/home/majernik/Programming/C++/FEM3/include -I"/home/majernik/Programming/C++/FEM3/examples" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


