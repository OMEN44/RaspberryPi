#include <iostream>
#include <unistd.h>
#include <pigpio.h>
#include "Hardware/MatrixStage.h"
#include "Hardware/Matrix.h"
#include "Hardware/MCP3008.h"
#include "Hardware/Joystick.h"
#include <vector>

using namespace std;

/*
g++ -Wall -o test test.cpp Hardware/MatrixStage.cpp Hardware/Matrix.cpp Hardware/MCP3008.cpp Hardware/Joystick.cpp -lpigpio
*/


vector<vector<int>> frame = {
    {1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,0,1},
    {1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0},
    {1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0},
    {1,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,1,0,1,0,0,1,0},
    {1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
    {1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1},
    {1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,1,0,1,0,1,0,1,0,1,1,1,0},
    {1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,1,1,0},
    {1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,1,1,0,0,1},
    {1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0},
    {1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}
};

int main()
{
    system("clear");

	cout << "Starting testing" << endl << endl;

    if (gpioInitialise() < 0) {
        cerr << "Failed to initialise GPIO" << endl;
        return 1;
    }

	vector<vector<int>> vec(24, vector<int>(6, 1));

	MatrixStage mstage(16, 16);
    mstage.setPixelValue(0, 0, 0);
    int coords[2] = {0, 0};
    
    Matrix m(mstage, 18, 17, 16, 13, 12, 6, 5, 4);

    int inputBuffer = 0;

    while (true) {
        if (inputBuffer == 10) {
            cout << "(" << coords[1] << ", " << coords[0] << ")" << endl;
            m.getStage().setPixelValue(coords[1], coords[0], 1);
            if (coords[0] == 15 && coords[1] == 15) {
                coords[0] = 0;
                coords[1] = 0;
            } else if (coords[0] == 15) {
                coords[0] = 0;
                coords[1]++;
            } else {
                coords[0]++;
            }
            m.getStage().setPixelValue(coords[1], coords[0], 0);
            inputBuffer = 0;
        } else inputBuffer++;
        m.update();
    }

    // for (int y = 0; y < 16; y++) {
    //     for (int x = 0; x < 16; x++) {
    //         mstage.setPixelValue(coords[0], coords[1], 1);
    //         if (coords[0] == 15) {
    //             coords[0] = 0;
    //             coords[1]++;
    //         } else {
    //             coords[0]++;
    //         }
    //         gpioDelay(100000);
    //         m.update();
    //     }
    // }
    gpioTerminate();

	cout << endl << "Finished testing" << endl;

	return 0;
}