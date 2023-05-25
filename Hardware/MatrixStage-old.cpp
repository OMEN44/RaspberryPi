#include <iostream>
#include <vector>
#include "MatrixStage.h"

using namespace std;

//constructors and destructors
MatrixStage::MatrixStage(int Xlength, int Ylength)
{
    //Initialise the stage to be a 2D array of 0s
    this->stage = vector<vector<int>>(Ylength, vector<int>(Xlength, 0));
}

MatrixStage::MatrixStage(vector<vector<int>> stage, int Xlength, int Ylength) {
    this->stage = vector<vector<int>>(Ylength, vector<int>(Xlength, 0));
    //Squishes the stage vector to be the specified size
    for (int y = 0; y < Ylength; y++)
        for (int x = 0; x < Xlength; x++)
            if (y < stage.size() && x < stage[0].size())
                this->stage[y][x] = stage[y][x];
}

MatrixStage::MatrixStage(vector<vector<int>> stage) {
    //no changes are made to the stage variable
    this->stage = stage;
}

//Setting up and editing the stage variable
//Sets stage to a 2D array of 0's at the specified size
void MatrixStage::newStage(int rowCount, int colCount) {
    this->stage = vector<vector<int>>(rowCount, vector<int>(colCount, 0));
}

//Sets stage to the specified 2D array
void MatrixStage::setStage(vector<vector<int>> stage) {
    this->stage = stage;
}

//Sets stage to the specified 2D array, squished to the specified size
void MatrixStage::setStage(vector<vector<int>> stage, int rowCount, int colCount) {
    this->stage = stage;
    //Squishes the stage vector to be the specified size
    for (int y = 0; y < rowCount; y++)
        for (int x = 0; x < colCount; x++)
            if (y < stage.size() && x < stage[0].size())
                this->stage[y][x] = stage[y][x];
}

//returns the 2D array of the stage
vector<vector<int>> MatrixStage::getStage() {
    return this->stage;
}

//working with individual pixels
int MatrixStage::getValue(int x, int y) {
    if (x < 0 || x >= this->getLengthX() || y < 0 || y >= this->getLengthY()) {
        return -1;
    }
    return this->stage[x][y];
}

void MatrixStage::setValue(int x, int y, int value) {
    if (x < 0 || x >= this->getLengthX() || y < 0 || y >= this->getLengthY()) {
        return;
    }
    this->stage[x][y] = value;
}

//camera movement
void MatrixStage::shift(int pixels, int direction) {
    switch (direction) {
        case 0:
            if (this->viewY - pixels < 0)
                this->viewY = this->getLengthY() - 16;
            else
                this->viewY -= pixels;
            break;
        case 1:
            if (this->viewX + pixels + 16 > this->getLengthX())
                this->viewX = 0;
            else
                this->viewX += pixels;
            break;
        case 2:
            if (this->viewY + pixels + 16 > this->getLengthY())
                this->viewY = 0;
            else
                this->viewY += pixels;
            break;
        case 3:
            if (this->viewX - pixels < 0)
                this->viewX = this->getLengthX() - 16;
            else
                this->viewX -= pixels;
            break;
    }
}

void MatrixStage::shift(int direction) {
    this->shift(1, direction);
}

void MatrixStage::goTo(int x, int y) {
    this->viewX = x;
    this->viewY = y;
}

int MatrixStage::getViewX() {
    return this->viewX;
}

int MatrixStage::getViewY() {
    return this->viewY;
}

int** MatrixStage::getCameraView() {
    int** view = new int*[16];
    for (int i = 0; i < 16; i++) {
        view[i] = new int[16];
    }
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            view[y][x] = this->stage[y + this->viewY][x + this->viewX];
            //cout << view[y][x] << " ";
        }
        //cout << endl;
    }
    return view;
}

void MatrixStage::printCameraView() {
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            cout << this->stage[y + this->viewY][x + this->viewX] << " ";
        }
        cout << endl;
    }
}

//utilities
void MatrixStage::clear() {
    for (int i = 0; i < this->getLengthY(); i++) {
        for (int j = 0; j < this->getLengthX(); j++) {
            this->stage[i][j] = 0;
        }
    }
}

void MatrixStage::invert() {
    for (int i = 0; i < this->getLengthY(); i++) {
        for (int j = 0; j < this->getLengthX(); j++) {
            this->stage[i][j] = !this->stage[i][j];
        }
    }
}

void MatrixStage::copy(MatrixStage* stage) {
    for (int i = 0; i < this->getLengthY(); i++) {
        for (int j = 0; j < this->getLengthX(); j++) {
            this->stage[i][j] = stage->getValue(i, j);
        }
    }
}

int MatrixStage::getLengthX() {
    return this->stage.size();
}

int MatrixStage::getLengthY() {
    return this->stage[0].size();
}

void MatrixStage::print() {
    cout << getLengthX() << " " << getLengthY() << endl;

    for (int y = 0; y < getLengthY(); y++) {
		for (int x = 0; x < getLengthX(); x++) {
			cout << getStage()[x][y] << " ";
		}
		cout << "e" << endl;
	}
    // for (int y = 0; y < this->getLengthY(); y++) {
    //     for (int x = 0; x < this->getLengthX(); x++) {
    //         if ((y == this->viewY && x == this->viewX)
    //             || (y == this->viewY + 15 && x == this->viewX + 15)
    //             || (y == this->viewY && x == this->viewX + 15)
    //             || (y == this->viewY + 15 && x == this->viewX)) {
    //             cout << ". ";
    //             continue;
    //         } else if ((y == this->viewY || y == this->viewY + 15) 
    //             && (x > this->viewX && x < this->viewX + 15)) {
    //             cout << "_ ";
    //             continue;
    //         } else if ((x == this->viewX || x == this->viewX + 15)
    //             && (y > this->viewY && y < this->viewY + 15)) {
    //             cout << "| ";
    //             continue;
    //         }
    //         cout << this->stage[y][x] << " ";
    //     }
    //     cout << endl;
    // }
}