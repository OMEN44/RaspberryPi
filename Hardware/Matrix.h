#ifndef MATRIX_H
#define MATRIX_H
#include "MatrixStage.h"

class Matrix {
    public:
    //initialisation functions
    Matrix(MatrixStage stage, int LAT, int CLK, int DI, int G, int A, int B, int C, int D);
    Matrix(int LAT, int CLK, int DI, int G, int A, int B, int C, int D);
    //setting up the stage if it wasn't done in the constructor
    void setStage(MatrixStage stage);
    MatrixStage& getStage();
    void setSize(int width, int height);

    void run(bool* running);

    // private:
    bool stageInitialised = false;
    MatrixStage stage = MatrixStage(0, 0);
    int width = 16;
    int height = 16;
    int LAT;
    int CLK;
    int DI;
    int G;
    int A;
    int B;
    int C;
    int D;


    void update();
    void selectRow(int row);
    void decimalToBinary(int decimal, int* output);
};

#endif