#ifndef MCP3008_H
#define MCP3008_H

class MCP3008 {
    public:
    MCP3008(int CS);
    MCP3008(int CS, int MISO, int MOSI, int SCLK);
    int gpioAnalogRead(int address);

    private:
    unsigned short int CS = 8;
    unsigned short int MISO = 9;
    unsigned short int MOSI = 10;
    unsigned short int SCLK = 11;

    void clockBit(unsigned short int value);

};

#endif