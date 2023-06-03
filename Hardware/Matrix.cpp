#include <pigpio.h>
#include <iostream>
#include "Matrix.h"
#include "MatrixStage.h"

Matrix::Matrix(MatrixStage stage, int LAT, int CLK, int DI, int G, int A, int B, int C, int D) 
    : stage(stage), LAT(LAT), CLK(CLK), DI(DI), G(G), A(A), B(B), C(C), D(D)
{
    this->stageInitialised = true;
    this->stage.setCameraSize(width, height);
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
    this->stage.setCameraSize(width, height);
    this->stageInitialised = false;
}

//setting up the stage if it wasn't done in the constructor
void Matrix::setStage(MatrixStage stage) {
    this->stage = stage;
    this->stage.setCameraSize(width, height);
    this->stageInitialised = true;
}

MatrixStage& Matrix::getStage() {
    if (!this->stageInitialised) 
        std::cerr << "Stage not initialised" << std::endl;
    return this->stage;
}

void Matrix::setSize(int width, int height) {
    std::cerr << "setSize() not implemented" << std::endl;
}

void Matrix::run(bool* running) {
    while (*running) {
        update();
    }
}

// private functions
void Matrix::update() {
    update(200);
}

void Matrix::update(int delay) {
    if (!this->stageInitialised) {
        std::cerr << "Stage not initialised" << std::endl;
        return;
    }
    // stage.printCameraView();
    for (int y = 0; y < height; y++) {
        gpioWrite(G, 1);
        selectRow(y);
        for (int x = 0; x < width; x++) {
            int bit = this->getStage().getCameraView()[y][x];
            gpioWrite(DI, bit);
            gpioWrite(CLK, 1);
            gpioWrite(CLK, 0);
        }
        gpioWrite(LAT, 1);
        gpioWrite(LAT, 0);
        gpioWrite(G, 0);
        gpioDelay(delay);
    }
}

void Matrix::selectRow(int row) {
    int num = 15 - row;
    int rowBin[4];
    decimalToBinary(num, rowBin);
    gpioWrite(D, rowBin[0]);
    gpioWrite(C, rowBin[1]);
    gpioWrite(B, rowBin[2]);
    gpioWrite(A, rowBin[3]);
}

void Matrix::decimalToBinary(int decimal, int* output) {
    int binaryNumber = 0;
    binaryNumber |= ((decimal >> 3) & 1) << 3;
    binaryNumber |= ((decimal >> 2) & 1) << 2;
    binaryNumber |= ((decimal >> 1) & 1) << 1;
    binaryNumber |= (decimal & 1) << 0;

    // Convert binary number to array of integers
    for (int i = 0; i < 4; i++) {
        output[i] = (binaryNumber >> (3 - i)) & 1;
    }
}

