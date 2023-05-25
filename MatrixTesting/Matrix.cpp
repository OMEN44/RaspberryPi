#include "Matrix.h"
#include <pigpio.h>


#define LAT 18
#define CLK 17
#define DI 16
#define G 13
#define A 12
#define B 6
#define C 5
#define D 4

void matrix::update(int matrix[16][16]) {
    for (int y = 0; y < 16; y++) {
        gpioWrite(G, 1);
        selectRow(y);
        for (int x = 0; x < 16; x++) {
            int bit = matrix[y][x];
            gpioWrite(DI, bit);
            gpioWrite(CLK, 1);
            gpioWrite(CLK, 0);
        }
        gpioWrite(LAT, 1);
        gpioWrite(LAT, 0);
        gpioWrite(G, 0);
    }
}

void matrix::selectRow(int row) {
    int num = 15 - row;
    int rowBin[4];
    decimalToBinary(num, rowBin);
    gpioWrite(D, rowBin[0]);
    gpioWrite(C, rowBin[1]);
    gpioWrite(B, rowBin[2]);
    gpioWrite(A, rowBin[3]);
}

void matrix::decimalToBinary(int decimal, int* output) {
    int binaryNumber = 0;
    binaryNumber |= ((decimal >> 3) & 1) << 3;
    binaryNumber |= ((decimal >> 2) & 1) << 2;
    binaryNumber |= ((decimal >> 1) & 1) << 1;
    binaryNumber |= (decimal & 1) << 0;

    // Convert binary number to array of integers
    for (int i = 0; i < 4; i++) {
        output[i] = (binaryNumber >> (3 - i)) & 1;
    }
}