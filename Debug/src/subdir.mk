################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Calculus.cpp \
../src/DenseMatrix.cpp \
../src/FEM3.cpp \
../src/FEMelement.cpp \
../src/FEMelementcontainer.cpp \
../src/FEMobject.cpp \
../src/GeoData.cpp \
../src/Interpolator.cpp \
../src/ReadFromOBJ.cpp \
../src/ScalarData.cpp \
../src/SparseMatrix.cpp \
../src/TriangleInterpolation.cpp \
../src/VectorData.cpp 

OBJS += \
./src/Calculus.o \
./src/DenseMatrix.o \
./src/FEM3.o \
./src/FEMelement.o \
./src/FEMelementcontainer.o \
./src/FEMobject.o \
./src/GeoData.o \
./src/Interpolator.o \
./src/ReadFromOBJ.o \
./src/ScalarData.o \
./src/SparseMatrix.o \
./src/TriangleInterpolation.o \
./src/VectorData.o 

CPP_DEPS += \
./src/Calculus.d \
./src/DenseMatrix.d \
./src/FEM3.d \
./src/FEMelement.d \
./src/FEMelementcontainer.d \
./src/FEMobject.d \
./src/GeoData.d \
./src/Interpolator.d \
./src/ReadFromOBJ.d \
./src/ScalarData.d \
./src/SparseMatrix.d \
./src/TriangleInterpolation.d \
./src/VectorData.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++0x -I/home/majernik/Programming/C++/FEM3/include/Eigen -I/usr/include/python2.7 -I/home/majernik/Programming/C++/FEM3/include -I"/home/majernik/Programming/C++/FEM3/examples" -O0 -g3 -Wall -c -fmessage-length=0 -fopenmp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


