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

	MatrixStage mstage(frame, 32, 16);
    
    Matrix m(mstage, 18, 17, 16, 13, 12, 6, 5, 4);

    Joystick j(3, 2, 26);

    while (true) {
        if (j.getY() > 75)
            m.getStage().shift(1);
        else if (j.getY() < 25)
            m.getStage().shift(3);
        m.update();
    }

    // bool running = true;
    // m.run(&running);


	cout << endl << "Finished testing" << endl;

	return 0;
}