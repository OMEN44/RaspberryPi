#ifndef MATRIX_H
#define MATRIX_H
#include "MatrixStage.h"

class Matrix {
    public:
    int stageInitialised = 0;
    //initialisation functions
    Matrix(MatrixStage stage, int LAT, int CLK, int DI, int G, int A, int B, int C, int D);
    Matrix(int LAT, int CLK, int DI, int G, int A, int B, int C, int D);
    //setting up the stage if it wasn't done in the constructor
    void setStage(MatrixStage stage);
    MatrixStage& getStage();


    private:
    MatrixStage stage = MatrixStage(0, 0);
    int LAT;
    int CLK;
    int DI;
    int G;
    int A;
    int B;
    int C;
    int D;

};

#endif