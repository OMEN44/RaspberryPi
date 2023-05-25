#include <stdio.h>
#include <pigpio.h>
#include <iostream>
#include "MatrixDriver.h"
#include "MatrixStage.h"

using namespace std;

//constructors and destructors
MatrixDriver::MatrixDriver(int D, int C, int B, int A, int G, int DI, int CLK, int LAT) {
    this->D = D;
    this->C = C;
    this->B = B;
    this->A = A;
    this->G = G;
    this->DI = DI;
    this->CLK = CLK;
    this->LAT = LAT;

    gpioSetMode(D, PI_OUTPUT);
    gpioSetMode(C, PI_OUTPUT);
    gpioSetMode(B, PI_OUTPUT);
    gpioSetMode(A, PI_OUTPUT);
    gpioSetMode(G, PI_OUTPUT);
    gpioSetMode(DI, PI_OUTPUT);
    gpioSetMode(CLK, PI_OUTPUT);
    gpioSetMode(LAT, PI_OUTPUT);
    //TODO: Add init animation
}

//Whole screen functions

MatrixStage MatrixDriver::getStage() {
    if (!this->stageInitialised) {
        cout << "Stage not initialised" << endl;
        return MatrixStage(0, 0);
    }
    return this->stage;
}

void MatrixDriver::setStage(MatrixStage stage) {
    if (stage.getColCount() < 16 || stage.getRowCount() < 16) {
        cout << "Stage too small" << endl;
        return;
    }
    this->stage = stage;
    this->xsize = stage.getColCount();
    this->ysize = stage.getRowCount();
    stageInitialised = 1;
}

void MatrixDriver::setStage(int** stage, int stageWidth, int stageHeight) {
    if (stageWidth < 16 || stageHeight < 16) {
        cout << "Stage too small" << endl;
        return;
    }
    this->stage = MatrixStage(stage, stageWidth, stageHeight);
    this->xsize = stageWidth;
    this->ysize = stageHeight;
    stageInitialised = 1;
}

void MatrixDriver::update() {
    if (!this->stageInitialised) {
        cout << "Stage not initialised" << endl;
        return;
    }
    for (int y = 0; y < ysize; y++) {
        gpioWrite(G, 1);
        selectRow(y);
        for (int x = 0; x < xsize; x++) {
            int bit = this->getStage().getCameraView()[y][x];
            gpioWrite(DI, bit);
            gpioWrite(CLK, 1);
            gpioWrite(CLK, 0);
        }
        gpioWrite(LAT, 1);
        gpioWrite(LAT, 0);
        gpioWrite(G, 0);
    }
}

void MatrixDriver::selectRow(int row) {
    int num = 15 - row;
    int rowBin[4];
    decimalToBinary(num, rowBin);
    gpioWrite(D, rowBin[0]);
    gpioWrite(C, rowBin[1]);
    gpioWrite(B, rowBin[2]);
    gpioWrite(A, rowBin[3]);
}

void MatrixDriver::decimalToBinary(int decimal, int* output) {
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

