#include <iostream>
#include <vector>
#include "MatrixStage.h"

using namespace std;

//constructors and destructors
MatrixStage::MatrixStage(vector<vector<int>> stage)
    : stage(stage) {}

MatrixStage::MatrixStage(int width, int height) 
    : stage(vector<vector<int>>(height, vector<int>(width, 0))) {}

MatrixStage::MatrixStage(vector<vector<int>> stage, int width, int height) {
    this->stage = vector<vector<int>>(height, vector<int>(width, 0));
    for (int y = 0; y < height; y++) for (int x = 0; x < width; x++)
        if (y < stage.size() && x < stage[0].size())
            this->stage[y][x] = stage[y][x];
}

//Setting up and editing the stage
void MatrixStage::newStage(int width, int height) {
    this->stage = vector<vector<int>>(height, vector<int>(width, 0));
}

void MatrixStage::newStage() {
    newStage(getLengthX(), getLengthY());
}

vector<vector<int>> MatrixStage::getStage() {
    return this->stage;
}

//utilities
void MatrixStage::invert() {
    for (int y = 0; y < getLengthY(); y++) 
        for (int x = 0; x < getLengthX(); x++)
            this->stage[y][x] = (this->stage[y][x] == 0) ? 1 : 0;
}

void MatrixStage::print() {
    for (int y = 0; y < getLengthY(); y++) {
		for (int x = 0; x < getLengthX(); x++) 
            cout << this->stage[y][x] << " ";
		cout << endl;
	}
}

inline int MatrixStage::getLengthX() {
    return this->stage[0].size();
}

inline int MatrixStage::getLengthY() {
    return this->stage.size();
}