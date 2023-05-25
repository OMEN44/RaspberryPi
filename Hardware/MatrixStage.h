#ifndef MATRIXSTAGE_H
#define MATRIXSTAGE_H
#include <vector>

class MatrixStage {
    public:
    MatrixStage(std::vector<std::vector<int>> stage);
    MatrixStage(int width, int height);
    MatrixStage(std::vector<std::vector<int>> stage, int width, int height);

    //Setting up and editing the stage variable
    void newStage(int width, int height);
    void newStage();
    void setStage(std::vector<std::vector<int>> stage);
    void setStage(std::vector<std::vector<int>> stage, int rowCount, int colCount);
    std::vector<std::vector<int>> getStage();
    
    //working with individual pixels
    int getValue(int x, int y);
    void setValue(int x, int y, int value);

    //camera movement
    void shift(int pixels, int direction);
    void shift(int direction);
    void goTo(int x, int y);
    int getViewX();
    int getViewY();
    int** getCameraView();
    void printCameraView();

    //utilities
    void invert();
    void print();
    int getLengthX();
    int getLengthY();

    private:
    std::vector<std::vector<int>> stage;
    //Top left of the camera view
    int viewX = 0; //the x coordinate of the camera
    int viewY = 0; //the y coordinate of the camera
};

#endif