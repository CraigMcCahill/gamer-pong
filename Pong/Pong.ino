#include <Gamer.h>

struct Bat {
    int siz;
    int pos;
};

struct Ball {
    int x;
    int y;
    int vx;
    int vy;
};

Gamer gamer;
Bat bat = { 4, 0 };
Ball ball = { 3, -1, -1, 1 };
int displayWidth, displayHeight;
int gameSpeed = 150;

void setup() {
    gamer.begin();
    displayWidth =  displayHeight = 8;
}

void loop() {
    gamer.clear();
    updateBat();
    drawBat();
    updateBall();
    drawBall();
    gamer.updateDisplay();
    delay(gameSpeed);
}

void updateBat() {
    if(gamer.isHeld(RIGHT) && (bat.pos + bat.siz) < displayWidth) {
       bat.pos++;
    }
    else if(gamer.isHeld(LEFT) && bat.pos > 0) {
       bat.pos--;   
    }
}

void drawBat() {
    for(int i = bat.pos; i < (bat.pos + bat.siz); i++) {
       gamer.display[i][7] = 1;
    }
}

bool detectCollision() {
  return (ball.y == (displayHeight - 2) 
      && (ball.x + ball.vx) >= bat.pos
      && (ball.x + ball.vx) < (bat.pos + bat.siz) 
  );
}

void updateBall() {
   if((ball.x + ball.vx) < 0 || ((ball.x + ball.vx) > displayWidth - 1)) {
       ball.vx = -(ball.vx);
   }  
   
   if((ball.y + ball.vy) < 0 || detectCollision()) {
       ball.vy = -(ball.vy);
   } 
   else if((ball.y + ball.vy) > displayHeight - 1) {
       gameOver(); 
   }  
  
   ball.x += ball.vx;
   ball.y += ball.vy;
   
}

void drawBall() {
  gamer.display[ball.x][ball.y] = 1;
}

void gameOver() { 
    ball = { 3, -1, 1, 1 };   
}

