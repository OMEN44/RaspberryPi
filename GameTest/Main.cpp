#include "../Hardware/Joystick.h"
#include "../Hardware/Matrix.h"
#include <iostream>
#include <pigpio.h>
//random thingo:
// #include <functional>
// #include <random>
//exit on key press:
// #include <conio.h>

/*
g++ Main.cpp ../Hardware/* -o pong -lpigpio -Wall
clear ; g++ Main.cpp ../Hardware/* -o pong -lpigpio ; sudo ./pong
*/

#define START_BUTTON 22

using namespace std;

int main(int argc, char const *argv[])
{
    if (gpioInitialise() < 0) {
        std::cout << "Failed to initialize GPIOs" << std::endl;
        return 1;
    }
    gpioSetMode(START_BUTTON, PI_INPUT);

    Joystick p0(2, 3, 20);
    Joystick p1(0, 1, 26);
    MatrixStage m(16, 16);
    // m.setPixelValue(9, 0, 0);

    unsigned int players[2][4] = { { 6, 7, 8, 9 }, { 6, 7, 8, 9 } };
    unsigned int ball[4][2] = { {7, 7}, {7, 8}, {8, 7}, {8, 8} };

    Matrix matrix(m, 18, 17, 16, 13, 12, 6, 5, 4);

    /*
     5     0
      \   /
    4 - b - 1
      /   \
     3     2    
    */
    
    int inputBuffer = 0;
    int ballBuffer = 0;
    int ballDir = 1;

    cout << "Press button to start!" << endl;
    while (gpioRead(START_BUTTON) == 0) {}
    cout << "3" << endl;
    gpioDelay(1000000);
    cout << "2" << endl;
    gpioDelay(1000000);
    cout << "1" << endl;
    gpioDelay(1000000);
    cout << "Play!" << endl;
    gpioDelay(10000);
    
    do {
        //INPUT
        if (inputBuffer == 10) {
            //player 0
            if (p0.getY() < 45 && players[0][3] < 15) {
                for (int i = 0; i < 4; i++) {
                    matrix.getStage().setPixelValue(players[0][i], 1, 1);
                    players[0][i] += 1;
                }
            } else if (p0.getY() > 55 && players[0][0] > 0) {
                for (int i = 0; i < 4; i++) {
                    matrix.getStage().setPixelValue(players[0][i], 1, 1);
                    players[0][i] -= 1;
                }
            }
            //player 1
            if (p1.getY() < 45 && players[1][3] < 15) {
                for (int i = 0; i < 4; i++) {
                    matrix.getStage().setPixelValue(players[1][i], 14, 1);
                    players[1][i] += 1;
                }
            } else if (p1.getY() > 55 && players[1][0] > 0) {
                for (int i = 0; i < 4; i++) {
                    matrix.getStage().setPixelValue(players[1][i], 14, 1);
                    players[1][i] -= 1;
                }
            }
            inputBuffer = 0;
        } else inputBuffer++;

        //(0) 7, 7 bottom left
        //(1) 7, 8 bottom right
        //(2) 8, 7 top left
        //(3) 8, 8 top right

        // LOGIC
        if (ballBuffer == 20) {
            cout << "ballDir: " << ballDir << endl;
            cout << "tl (" << ball[0][1] << ", " << ball[0][0] << ")" << endl;
            cout << "tr (" << ball[3][1] << ", " << ball[3][0] << ")" << endl;
            cout << "br (" << ball[2][1] << ", " << ball[2][0] << ")" << endl;
            cout << "bl (" << ball[1][1] << ", " << ball[1][0] << ")" << endl << endl;
            // BALL MOVEMENT
            switch (ballDir) {
                case 0:
                    if (ball[3][0] < 15 && ball[3][1] < 15) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][0] += 1;
                            ball[i][1] += 1;
                        }
                    } else {
                        ballDir = 3;
                    }
                    break;
                case 1:
                    if (ball[1][1] == players[1][0] && ball[3][1] == players[1][1]) {
                        ballDir = 4;
                        break;
                    }
                    if (ball[1][1] < 15) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][1] += 1;
                        }
                    } else {
                        ballDir = 4;
                    }
                    break;
                case 2:
                    if (ball[1][0] > 0 && ball[1][1] < 15) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][0] -= 1;
                            ball[i][1] += 1;
                        }
                    } else {
                        ballDir = 5;
                    }
                    break;
                case 3:
                    if (ball[0][0] > 0 && ball[0][1] > 0) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][0] -= 1;
                            ball[i][1] -= 1;
                        }
                    } else {
                        ballDir = 0;
                    }
                    break;
                case 4:
                    if (ball[0][1] > 0) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][1] -= 1;
                        }
                    } else {
                        ballDir = 1;
                    }
                    break;
                case 5:
                    if (ball[2][0] < 15 && ball[2][1] > 0) {
                        for (int i = 0; i < 4; i++) {
                            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 1);
                            ball[i][0] += 1;
                            ball[i][1] -= 1;
                        }
                    } else {
                        ballDir = 2;
                    }
                    break;
            }
            ballBuffer = 0;
        } else ballBuffer++;

        //RENDER
        for (int i = 0; i < 4; i++) {
            matrix.getStage().setPixelValue(players[0][i], 1, 0);
            matrix.getStage().setPixelValue(players[1][i], 14, 0);
            matrix.getStage().setPixelValue(ball[i][0], ball[i][1], 0);
        }
        matrix.update();
    } while (gpioRead(START_BUTTON) == 0);

    gpioTerminate();

    cout << "GAME OVER MAN!" << endl;
    return 0;
}
