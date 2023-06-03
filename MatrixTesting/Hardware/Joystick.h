#ifndef JOYSTICK_H
#define JOYSTICK_H
#include "MCP3008.h"

class Joystick {
    public:
    Joystick(MCP3008 adc, int yChannel, int xChannel, int SW);
    Joystick(int yChannel, int xChannel, int SW);
    double getX();
    double getY();
    int getSW();

    int getRawX();
    int getRawY();

    private:
    int X = 0;
    int Y = 1;
    int SW = 0;
    MCP3008 adc = MCP3008(8, 9, 10, 11);
};

#endif