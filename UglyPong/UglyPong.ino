#include <Gamer.h>

Gamer gamer;

int batSiz = 4;
int batPos = 0;

int ballX = 3;
int ballY = -1;
int ballVX = -1;
int ballVY = 1;

int displayWidth, displayHeight;
int gameSpeed = 150;

void setup() {
    gamer.begin();
    displayWidth =  displayHeight = 8;
}

void loop() {
    gamer.clear();

    if(gamer.isHeld(RIGHT) && (batPos + batSiz) < displayWidth) {
       batPos++;
    }
    else if(gamer.isHeld(LEFT) && batPos > 0) {
       batPos--;
    }

    for(int i = batPos; i < (batPos + batSiz); i++) {
       gamer.display[i][7] = 1;
    }

    if((ballX + ballVX) < 0 || ((ballX + ballVX) > displayWidth - 1)) {
        ballVX = -(ballVX);
    }

    if((ballY + ballVY) < 0) {
        ballVY = -(ballVY);
    }
    else if(ballY == (displayHeight - 2)
        && (ballX + ballVX) >= batPos
        && (ballX + ballVX) < (batPos + batSiz)
    ) {
        ballVY = -(ballVY);
    }
    else if((ballY + ballVY) > displayHeight - 1) {
        int startingPos = (int) random(0, displayWidth - 1);
        ballX = startingPos;
        ballY = -1;
        ballVX = -1;
        ballVY = 1;
    }

    ballX += ballVX;
    ballY += ballVY;
    
    gamer.display[ballX][ballY] = 1;
    gamer.updateDisplay();
    delay(gameSpeed);
}

