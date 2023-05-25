#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include "Hardware/MatrixStage.h"
#include <vector>

using namespace std;

/*
g++ -Wall -o test test.cpp Hardware/MatrixStage.cpp Hardware/Matrix.cpp Hardware/MCP3008.cpp Hardware/Joystick.cpp -lpigpio
*/


int frame1[16][16] = {
    {1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0},
    {1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0},
    {1,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0},
    {1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1},
    {1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
    {1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0},
    {1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}
};

int main()
{
    system("clear");

	cout << "Starting testing" << endl << endl;

	vector<vector<int>> vec(12, vector<int>(6, 1));

	MatrixStage mstage(vec, 8, 4);

    cout << "printing with inbuilt" << endl;
	mstage.print();

    cout << "new stage:" << endl;
    mstage.newStage();
    mstage.print();

    vector<vector<int>> stageCopy = mstage.getStage();


	cout << endl << "Finished testing" << endl;

	return 0;
}