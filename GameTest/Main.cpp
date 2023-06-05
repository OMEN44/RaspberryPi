#include "../Hardware/Joystick.h"
#include "../Hardware/Matrix.h"
#include <iostream>
#include <pigpio.h>
//random thingo:
// #include <functional>
// #include <random>

using namespace std;

/*
g++ Main.cpp ../Hardware/* -o pong -lpigpio -Wall
clear ; g++ Main.cpp ../Hardware/* -o pong -lpigpio ; sudo ./pong
*/

#define START_BUTTON 22

int playerScore[2] = {0, 0};
unsigned int ball[4][2] = { {2, 12}, {3, 12}, {3, 11}, {2, 11} };
unsigned int players[2][4] = { { 6, 7, 8, 9 }, { 6, 7, 8, 9 } };
int ballDir = 2;

void score(bool isPlayer0) {
    if (!isPlayer0) playerScore[0]++;
    else playerScore[1]++;
    int ballStart[4][2] = { {7, 8}, {8, 8}, {8, 7}, {7, 7} };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            ball[i][j] = ballStart[i][j];
        }
    }
}

int main(int argc, char const *argv[])
{
    if (gpioInitialise() < 0) {
        cout << "Failed to initialize GPIOs" << endl;
        return 1;
    }
    gpioSetMode(START_BUTTON, PI_INPUT);

    Joystick p0(2, 3, 20);
    Joystick p1(0, 1, 26);
    MatrixStage m(16, 16);
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

        //0: tl (7, 8)
        //1: tr (8, 8)
        //2: br (8, 7)
        //3: bl (7, 7)

        // LOGIC
        if (ballBuffer == 20) {
            cout << "score: " << playerScore[0] << " - " << playerScore[1] << endl;
            // CLEAR BALL
            for (int i = 0; i < 4; i++)
                matrix.getStage().setPixelValue(ball[i][1], ball[i][0], 1);
            // CHECK COLLISIONS
            int topCollision = -1;
            int bottomCollision = -1;
            if (ball[0][0] == 2) {
                for (int i = 0; i < 4; i++) {
                    if (players[0][i] == ball[0][1]) topCollision = players[0][i];
                    else topCollision = -1;
                    if (players[0][i] == ball[3][1]) bottomCollision = players[0][i];
                    else bottomCollision = -1;
                }
            } else if (ball[1][0] == 13) {
                for (int i = 0; i < 4; i++) {
                    if (players[1][i] == ball[1][1]) topCollision = players[1][i];
                    else topCollision = -1;
                    if (players[1][i] == ball[2][1]) bottomCollision = players[1][i];
                    else bottomCollision = -1;
                }
            }
            if ((topCollision == -1 && bottomCollision == players[0][3])
                || (topCollision == players[0][3] && bottomCollision == players[0][2]))
                ballDir = 0;
            if ((topCollision == -1 && bottomCollision == players[1][3])
                || (topCollision == players[1][3] && bottomCollision == players[1][2]))
                ballDir = 5;
            if ((topCollision == players[0][0] && bottomCollision == -1)
                || (topCollision == players[0][1] && bottomCollision == players[0][0]))
                ballDir = 2;
            if ((topCollision == players[1][0] && bottomCollision == -1)
                || (topCollision == players[1][1] && bottomCollision == players[1][0]))
                ballDir = 3;
            if (topCollision == players[0][2] && bottomCollision == players[0][1])
                ballDir = 1;
            if (topCollision == players[1][2] && bottomCollision == players[1][1])
                ballDir = 4;
            //TODO: check if seperating movement and wall collisions is more efficient
            // BALL MOVEMENT
            switch (ballDir) {
                case 0:
                    if (ball[1][0] == 15 && ball[1][1] == 15) score(false);
                    else if (ball[1][0] == 15) ballDir = 5;
                    else if (ball[0][1] == 15) ballDir = 2;
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] += 1;
                            ball[i][1] += 1;
                        }
                    break;
                case 1:
                    if (ball[1][0] == 15) score(false);
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] += 1;
                        }
                    break;
                case 2:
                    if (ball[2][0] == 15 && ball[2][1] == 0) score(false);
                    else if (ball[1][0] == 15) ballDir = 3;
                    else if (ball[3][1] == 0) ballDir = 0;
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] += 1;
                            ball[i][1] -= 1;
                        }
                    break;
                case 3:
                    if (ball[3][0] == 0 && ball[3][1] == 0) score(true);
                    else if (ball[0][0] == 0) ballDir = 2;
                    else if (ball[3][1] == 0) ballDir = 5;
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] -= 1;
                            ball[i][1] -= 1;
                        }
                    break;
                case 4:
                    if (ball[0][0] == 0) score(true);
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] -= 1;
                        }
                    break;
                case 5:
                    if (ball[0][0] == 0 && ball[0][1] == 15) score(true);
                    else if (ball[0][0] == 0) ballDir = 0;
                    else if (ball[0][1] == 15) ballDir = 3;
                    else
                        for (int i = 0; i < 4; i++) {
                            ball[i][0] -= 1;
                            ball[i][1] += 1;
                        }
                    break;
            }
            ballBuffer = 0;
        } else ballBuffer++;

        //RENDER
        for (int i = 0; i < 4; i++) {
            matrix.getStage().setPixelValue(players[0][i], 1, 0);
            matrix.getStage().setPixelValue(players[1][i], 14, 0);
            matrix.getStage().setPixelValue(ball[i][1], ball[i][0], 0);
        }
        matrix.update();
    } while (gpioRead(START_BUTTON) == 0);

    gpioTerminate();

    cout << "GAME OVER MAN!" << endl;
    return 0;
}
