/*
  Quick demo of major drawing operations on a single DMD
*/



#include "snake.h"
#include "game_function.h"




// the setup routine runs once when you press reset:
void setup() {

  SnakeGame snakeGame(1, 2);

  snakeGame.init();

  snakeGame.mainLoop();
}


// the loop routine runs over and over again forever:
void loop() {

}
