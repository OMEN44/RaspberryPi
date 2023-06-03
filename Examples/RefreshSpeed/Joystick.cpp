#include <pigpio.h>
#include "Joystick.h"
#include "MCP3008.h"

#include <iostream>
using namespace std;

#define READING_DELAY 1

Joystick::Joystick(MCP3008 adc, int yChannel, int xChannel, int SW) {
    this->adc = adc;
    this->Y = yChannel;
    this->X = xChannel;
    this->SW = SW;
}

Joystick::Joystick(int yChannel, int xChannel, int SW) {
    this->Y = yChannel;
    this->X = xChannel;
    this->SW = SW;
}

double Joystick::getX() {
    gpioDelay(READING_DELAY);
    return static_cast<int>(
        (static_cast<double>(
            (adc.gpioAnalogRead(X) == 0) ? 1 : adc.gpioAnalogRead(X)
        ) / 512.0 * 100.0) + 0.5
    );
}

double Joystick::getY() {
    gpioDelay(READING_DELAY);
    return static_cast<int>(
        (static_cast<double>(
            (adc.gpioAnalogRead(Y) == 0) ? 1 : adc.gpioAnalogRead(Y)
        ) / 512.0 * 100.0) + 0.5
    );
}

int Joystick::getSW() {
    gpioDelay(READING_DELAY);
    return gpioRead(SW);
}

int Joystick::getRawX() {
    gpioDelay(READING_DELAY);
    return adc.gpioAnalogRead(X);
}

int Joystick::getRawY() {
    gpioDelay(READING_DELAY);
    return adc.gpioAnalogRead(Y);
}