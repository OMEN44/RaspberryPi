#include <pigpio.h>
#include <iostream>
#include "Matrix.h"
#include "MatrixStage.h"

Matrix::Matrix(MatrixStage stage, int LAT, int CLK, int DI, int G, int A, int B, int C, int D) 
    : stage(stage), LAT(LAT), CLK(CLK), DI(DI), G(G), A(A), B(B), C(C), D(D)
{
    this->stageInitialised = 1;
    gpioSetMode(D, PI_OUTPUT);
    gpioSetMode(C, PI_OUTPUT);
    gpioSetMode(B, PI_OUTPUT);
    gpioSetMode(A, PI_OUTPUT);
    gpioSetMode(G, PI_OUTPUT);
    gpioSetMode(DI, PI_OUTPUT);
    gpioSetMode(CLK, PI_OUTPUT);
    gpioSetMode(LAT, PI_OUTPUT);
}

Matrix::Matrix(int LAT, int CLK, int DI, int G, int A, int B, int C, int D) 
    : Matrix(MatrixStage(0, 0), LAT, CLK, DI, G, A, B, C, D) 
{
    this->stageInitialised = 0;
}

//setting up the stage if it wasn't done in the constructor
void Matrix::setStage(MatrixStage stage) {
    this->stage = stage;
    this->stageInitialised = 1;
}

MatrixStage& Matrix::getStage() {
    if (!this->stageInitialised) 
        std::cout << "Stage not initialised" << std::endl;
    return this->stage;
}



