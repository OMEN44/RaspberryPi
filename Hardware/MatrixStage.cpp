#include <iostream>
#include <vector>
#include "MatrixStage.h"

using namespace std;

//constructors and destructors
MatrixStage::MatrixStage(vector<vector<int>> stage)
    : stage(stage) {}

MatrixStage::MatrixStage(int width, int height) 
    : stage(vector<vector<int>>(height, vector<int>(width, 1))) {}

MatrixStage::MatrixStage(vector<vector<int>> stage, int width, int height) {
    this->stage = vector<vector<int>>(height, vector<int>(width, 1));
    for (int y = 0; y < height; y++) for (int x = 0; x < width; x++)
        if ((unsigned)y < stage.size() && (unsigned)x < stage[0].size())
            this->stage[y][x] = stage[y][x];
}

//Setting up and editing the stage
void MatrixStage::newStage(int width, int height) {
    this->stage = vector<vector<int>>(height, vector<int>(width, 1));
}

void MatrixStage::newStage() {
    newStage(getLengthX(), getLengthY());
}

void MatrixStage::setStage(vector<vector<int>> stage) {
    this->stage = stage;
}

void MatrixStage::setStage(vector<vector<int>> stage, int width, int height) {
    this->stage = vector<vector<int>>(height, vector<int>(width, 1));
    for (int y = 0; y < height; y++) for (int x = 0; x < width; x++)
        if ((unsigned)y < stage.size() && (unsigned)x < stage[0].size())
            this->stage[y][x] = stage[y][x];
}

inline vector<vector<int>>& MatrixStage::getStage() {
    return this->stage;
}

//working with individual pixels
int MatrixStage::getPixelValue(int x, int y) {
    if (x >= getLengthX() || y >= getLengthY() || x < 0 || y < 0) {
        cout << "Position out of bounds for stage. Retuning 0..." << endl;
        return 0;
    }
    return this->stage[y][x];
}

void MatrixStage::setPixelValue(int x, int y, int value) {
    if (x >= getLengthX() || y >= getLengthY() || x < 0 || y < 0) {
        cout << "Position out of bounds for stage. No value set" << endl;
        return;
    }
    this->stage[y][x] = value;
}

//camera controll
int MatrixStage::getViewX() {
    return this->viewX;
}

int MatrixStage::getViewY() {
    return this->viewY;
}

void MatrixStage::setCameraSize(int width, int height) {
    if (width < 0 || height < 0 || width > getLengthX() || height > getLengthY()) {
        cout << "Invalid size. Size unchanged." << endl;
        return;
    }
    this->cameraHeight = height;
    this->cameraWidth = width;
}

void MatrixStage::goTo(int x, int y) {
    if (x >= getLengthX() || y >= getLengthY() || x < 0 || y < 0) {
        cout << "Position out of bounds for stage. Camera not moved." << endl;
        return;
    }
    this->viewX = x;
    this->viewY = y;
}

bool MatrixStage::shift(int pixels, int direction) {
    if (direction < 0 || direction > 3) {
        cout << "Invalid direction" << endl;
        return false;
    }
    switch (direction) {
        case 0:
            if (viewY == 0) return false;
            if (viewY - pixels < 0) viewY = 0;
            else viewY -= pixels;
            break;
        case 1:
            if (viewX == getLengthX() - cameraWidth) return false;
            if (viewX + pixels > getLengthX() - cameraWidth) viewX = getLengthX() - cameraWidth;
            else viewX += pixels;
            break;            
        case 2:
            if (viewY == getLengthY() - cameraHeight) return false;
            if (viewY + pixels > getLengthY() - cameraHeight) viewY = getLengthY() - cameraHeight;
            else viewY += pixels;
            break;
        case 3:
            if (viewX == 0) return false;
            if (viewX - pixels < 0) viewX = 0;
            else viewX -= pixels;
            break;
    }
    return true;
}

bool MatrixStage::shift(int direction) {
    return shift(1, direction);
}

vector<vector<int>> MatrixStage::getCameraView() {
    vector<vector<int>> view(cameraHeight, vector<int>(cameraWidth, 1));
    for (int y = 0; y < cameraHeight; y++) for (int x = 0; x < cameraWidth; x++)
        view[y][x] = stage[y + viewY][x + viewX];
    return view;
}

void MatrixStage::printCameraView() {
    for (int y = 0; y < cameraHeight; y++) {
        for (int x = 0; x < cameraWidth; x++) 
            cout << stage[y + viewY][x + viewX] << " ";
        cout << endl;
    }
}

//utilities
void MatrixStage::invert() {
    for (int y = 0; y < getLengthY(); y++) 
        for (int x = 0; x < getLengthX(); x++)
            this->stage[y][x] = (this->stage[y][x] == 0) ? 1 : 0;
}

inline int MatrixStage::getLengthX() {
    return this->stage[0].size();
}

inline int MatrixStage::getLengthY() {
    return this->stage.size();
}

void MatrixStage::print() {
    for (int y = 0; y < getLengthY(); y++) {
		for (int x = 0; x < getLengthX(); x++) {
            if (x == viewX && y == viewY) {
                cout << "┌─";
                continue;
            }
            if (x == (viewX + cameraWidth - 1) && y == viewY) {
                cout << "┐ ";
                continue;
            }
            if (x == viewX && y == (viewY + cameraHeight - 1)) {
                cout << "└─";
                continue;
            }
            if (x == (viewX + cameraWidth - 1) && y == (viewY + cameraHeight - 1)) {
                cout << "┘ ";
                continue;
            }
            if ((x > viewX && x < (viewX + cameraWidth - 1)) && 
               (y == viewY || y == (viewY + cameraHeight - 1))) {
                cout << "──";
                continue;
            }
            if ((y > viewY && y < (viewY + cameraHeight - 1)) && 
               (x == viewX || x == (viewX + cameraWidth - 1))) {
                cout << "│ ";
                continue;
            }
            cout << this->stage[y][x] << " ";
        }
		cout << endl;
	}
}