#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include "Hardware/MatrixStage.h"
#include <vector>

using namespace std;

/*
g++ -Wall -o test test.cpp Hardware/MatrixStage.cpp Hardware/Matrix.cpp Hardware/MCP3008.cpp Hardware/Joystick.cpp -lpigpio
*/


vector<vector<int>> frame = {
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

	vector<vector<int>> vec(24, vector<int>(6, 1));

	MatrixStage mstage(frame, 16, 16);
    mstage.setCameraSize(4, 4);

    mstage.print();

    if (!mstage.shift(2, 1))
        cout << "Failed to shift" << endl;
    cout << endl;
    mstage.print();

    int d = 1;
    while (true) {
        while (mstage.shift(d)) {
            system("clear");
            mstage.print();
            cout << endl;
            mstage.printCameraView();
            sleep(1);
        }
        if (d == 1) d = 3;
        else d = 1;
    }


	cout << endl << "Finished testing" << endl;

	return 0;
}