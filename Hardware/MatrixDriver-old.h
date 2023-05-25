#ifndef MATRIXDRIVER_H
#define MATRIXDRIVER_H
#include "MatrixStage.h"

class MatrixDriver {
    public:
    //constructors/destructors
    MatrixDriver(int D, int C, int B, int A, int G, int DI, int CLK, int LAT);
    
    //Whole screen functions
    MatrixStage getStage();
    void setStage(MatrixStage stage);
    void setStage(int** stage, int stageWidth, int stageHeight);
    void update();

    //animation functions
    void scrollText(char* text);
    void playAnimation(int*** animation, int delay);
    void playAnimation(MatrixStage* animation, int delay);

    private:
    int stageInitialised = 0;
    int D;
    int C;
    int B;
    int A;
    int G;
    int DI;
    int CLK;
    int LAT;
    //actual size of stage
    int xsize;
    int ysize;
    MatrixStage stage = MatrixStage(0, 0);

    void selectRow(int row);
    void decimalToBinary(int decimal, int* output);

};

#endif