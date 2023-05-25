#include <pigpio.h>
#include "MCP3008.h"

MCP3008::MCP3008(int CS) {
    this->CS = CS;

    gpioSetMode(CS, PI_OUTPUT);
    gpioSetMode(MISO, PI_INPUT);
    gpioSetMode(MOSI, PI_OUTPUT);
    gpioSetMode(SCLK, PI_OUTPUT);
}

MCP3008::MCP3008(int CS, int MISO, int MOSI, int SCLK) {
    this->CS = CS;
    this->MISO = MISO;
    this->MOSI = MOSI;
    this->SCLK = SCLK;

    gpioSetMode(CS, PI_OUTPUT);
    gpioSetMode(MISO, PI_INPUT);
    gpioSetMode(MOSI, PI_OUTPUT);
    gpioSetMode(SCLK, PI_OUTPUT);
}

void MCP3008::clockBit(unsigned short int value) {
    gpioWrite(SCLK, 0);
    gpioWrite(MOSI, value);
    gpioDelay(2);
    gpioWrite(SCLK, 1);
    gpioDelay(2);
}

int MCP3008::gpioAnalogRead(int address) {
    
    gpioWrite(CS, 0);

    //start bit
    clockBit(1);
    //wite single ended bit
    clockBit(1);
    //write address
    for(int i = 0; i < 3; i++) clockBit((address >> (2 - i)) & 1);

    //send buffer before read
    gpioDelay(2);
    gpioWrite(SCLK, 0);
    gpioDelay(2);

    //read data
    unsigned int data = 0;
    for (int i = 0; i < 10; i++) {
        gpioWrite(SCLK, 1);
        gpioDelay(2);
        gpioWrite(SCLK, 0);
        gpioDelay(2);
        data = (data << 1) | gpioRead(MISO);
    }

    gpioWrite(CS, 1);
    gpioDelay(2);
    
    return data;
}