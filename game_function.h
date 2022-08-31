#ifndef _GAME_FUNCTION_H_
#define _GAME_FUNCTION_H_


#include "snake.h"

#define UPDATETIME 500
#define WIDTH 1
#define HEIGHT 2

class SnakeGame {
    unsigned long perviousTime = millis();
    SPIDMD mainBuffer; // DMD controls the entire display
    SPIDMD secondBuffer;
    Snake snake;
    Point food;
    bool isPaused {false};
    byte score {0};
    bool gameOver{false};
    void serialInput();
    void IRInput();
    void swapBuffers();
    void getFood();
    void input();
  public:
    SnakeGame(byte width, byte height );
    void init ();
    byte width;
    byte height;
    void update(unsigned int elaspedTime);
    void render();
    void mainLoop();
    void pauseGame();
    void resumeGame();

    void restart();
};


#endif //_GAME_FUNCTION_H_
