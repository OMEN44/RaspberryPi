#include <iostream>
#include <pigpio.h>
#include "Matrix.h"
#include "MCP3008.h"
#include "Joystick.h"

using namespace std;

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


#define LAT 18
#define CLK 17
#define DI 16
#define G 13
#define A 12
#define B 6
#define C 5
#define D 4

int main() {

    cout << "This example uses a joystick to controll the speed of the matrix." << endl;
    cout << "The matrix is wired as follows:" << endl;
    cout << "    LAT: 18" << endl;
    cout << "    CLK: 17" << endl;
    cout << "    DI:  16" << endl;
    cout << "    G:   13" << endl;
    cout << "    A:   12" << endl;
    cout << "    B:   6" << endl;
    cout << "    C:   5" << endl;
    cout << "    D:   4" << endl;
    cout << "The MCP3008 ADC is wired to the default RaspberryPi SPI communication ports in CE0" << endl;
    cout << "The joy stick is connected to channel 2 and 3 of the MCP3008" << endl << endl;
    cout << "To recompile the example use the following command:" << endl;
    cout << "    g++ main.cpp Joystick.cpp Matrix.cpp MCP3008.cpp -o RefreshSpeedExample -lpigpio" << endl << endl;
    cout << "Press enter to continue" << endl;
    cin.get();


    if (gpioInitialise() < 0) {
        cout << "GPIO initialisation failed" << endl;
        return 1;
    }

    gpioSetMode(LAT, PI_OUTPUT);
    gpioSetMode(CLK, PI_OUTPUT);
    gpioSetMode(DI, PI_OUTPUT);
    gpioSetMode(G, PI_OUTPUT);
    gpioSetMode(A, PI_OUTPUT);
    gpioSetMode(B, PI_OUTPUT);
    gpioSetMode(C, PI_OUTPUT);
    gpioSetMode(D, PI_OUTPUT);

    matrix m;
    Joystick j(3, 2, 26);

    while (true) {
        cout << "(" << j.getX() << ", " << j.getY() << ")";
        int delay = 0;
        if (j.getY() > 0) {
            delay = j.getY() * 1000;
        } else {
            delay = 200;
        }
        cout << " delay: " << delay << "μs" << endl;
        m.update(frame1, delay);
        system("clear");
    }

    while (false) {
    
        //init transaction
        gpioWrite(G, 1);
        //select first row
        gpioWrite(A, 0);
        gpioWrite(B, 0);
        gpioWrite(C, 0);
        gpioWrite(D, 0);

        for (int x = 0; x < 16; x++) {
            int bit = frame1[0][x];
            gpioWrite(DI, bit);
            gpioWrite(CLK, 1);
            gpioWrite(CLK, 0);
        }
        gpioWrite(LAT, 1);
        gpioWrite(LAT, 0);
        gpioWrite(G, 0);

        //init transaction
        gpioWrite(G, 1);
        //select first row
        gpioWrite(A, 1);
        gpioWrite(B, 0);
        gpioWrite(C, 0);
        gpioWrite(D, 0);

        for (int x = 0; x < 16; x++) {
            int bit = frame1[1][x];
            gpioWrite(DI, bit);
            gpioWrite(CLK, 1);
            gpioWrite(CLK, 0);
        }
        gpioWrite(LAT, 1);
        gpioWrite(LAT, 0);
        gpioWrite(G, 0);
    }




    return 0;
}