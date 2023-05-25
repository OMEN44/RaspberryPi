#include <iostream>
#include <pigpio.h>
#include "Matrix.h"

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

    while (true) {
        m.update(frame1);
    }


    return 0;
}