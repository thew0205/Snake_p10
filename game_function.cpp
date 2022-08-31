
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <IRremote.h>  //including infrared remote header file   
#include "game_function.h"

#define BUTTON_ON 0xBA45FF00
#define BUTTON_0 0xE916FF00
#define BUTTON_1 0xF30CFF00
#define BUTTON_2 0xE718FF00
#define BUTTON_3 0xA15EFF00
#define BUTTON_4 0xF708FF00
#define BUTTON_5 0xE31CFF00
#define BUTTON_6 0xA55AFF00
#define BUTTON_7 0xBD42FF00
#define BUTTON_8 0xAD52FF00
#define BUTTON_9 0xB54AFF00
#define BUTTON_VOL_MINUS 0xEA15FF00
#define BUTTON_VOL_PLUS 0xF609FF00
#define BUTTON_PLAY_PAUSE 0xBB44FF00


constexpr int RECV_PIN = 2;

void drawStartNewGame(DMDFrame& screen, int score) {
  screen.drawString(2, 1,  "Start");
  screen.drawString(2, 8,  "Game");

  char stringScore[10]  = "Score";
  char charScore [3];
  itoa(score, charScore, 10);
  screen.drawString(2, 15, stringScore);
  screen.drawString(2, 22, charScore);
}
void drawGameOver(DMDFrame& screen, int score) {
  screen.drawString(2, 1,  "Game");
  screen.drawString(2, 8,  "Over");

  char stringScore[10]  = "Score";
  char charScore [3];
  itoa(score, charScore, 10);
  screen.drawString(2, 15, stringScore);
  screen.drawString(2, 22, charScore);
}

void drawGamePause(DMDFrame& screen, int score) {
  screen.drawString(2, 1,  "Resume");
  screen.drawString(2, 8,  "game");
  char stringScore[10]  = "Score";
  char charScore [3];
  itoa(score, charScore, 10);

  screen.drawString(2, 15, stringScore);
  screen.drawString(2, 22, charScore);
}

SnakeGame::SnakeGame(byte newWidth, byte newHeight): mainBuffer{newWidth, newHeight} , secondBuffer(newWidth, newHeight) , snake( mainBuffer.width, mainBuffer.height ) {

  width = mainBuffer.width;
  height = mainBuffer.height;
}

void SnakeGame::init() {
  //  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
  secondBuffer.clearScreen();
  mainBuffer.setBrightness(255);
  mainBuffer.selectFont(SystemFont5x7);
  mainBuffer.begin();
  secondBuffer.selectFont(SystemFont5x7);
  pauseGame();
  gameOver = true;
  randomSeed(analogRead(0));
  getFood();
  //  Serial.println("game started");
}


void SnakeGame::mainLoop() {
  while (true) {
    input();
    unsigned int elaspedTime = millis() - perviousTime;
    if (!gameOver && !isPaused && elaspedTime > UPDATETIME) {
      update(elaspedTime);
      perviousTime = millis();
    }
    render();
    swapBuffers();
  }
}

void  SnakeGame::update(unsigned int elaspedTime) {
  gameOver = !snake.checkIfStillAlive();
  if (snake.pointExist(food)) {
    getFood();
    score ++;
    snake.grow();
  }
  snake.update(elaspedTime);
}

void SnakeGame::render() {
  secondBuffer.clearScreen();
  secondBuffer.drawBox(0, 0, width - 1 , height - 1);
  if (gameOver) {
    drawStartNewGame(secondBuffer, score);
    return;
  }
  if (isPaused) {
    drawGamePause(secondBuffer, score);
    return;
  }
  food.render(secondBuffer);
  snake.render(secondBuffer);
}

void SnakeGame::getFood() {

  do  {
    food.x = random(1, width - 2);
    food.y = random(1, height - 2);
  } while (snake.pointExist(food));
  //  Serial.print("x :");
  //  Serial.print(food.x);
  //  Serial.print("y :");
  //  Serial.println(food.y);
}



void SnakeGame::restart() {
  gameOver = false;
  score = 0;
  snake.reset();
  getFood();
  resumeGame();
}

void SnakeGame::input() {
  //  serialInput();
  IRInput();
}

void SnakeGame::serialInput() {
  if (Serial.available()) {
    byte direction = Serial.read();
    if ( direction == 'w' || direction == 'W') {
      Serial.println("w");
      snake.setDirection ( Direction::up);
    }
    else if ( direction == 'a' || direction == 'A') {
      snake.setDirection (  Direction::left);
      Serial.println("a");
    }

    else if ( direction == 's' || direction == 'S') {
      snake.setDirection (  Direction::down);
      Serial.println("s");
    }

    else if ( direction == 'd' || direction == 'D') {
      Serial.println("d");
      snake.setDirection ( Direction::right);
    }
    else if ( direction == 'p' || direction == 'P') {
      Serial.println("p");
      restart();
    }
    else if ( direction == 'b' || direction == 'B' ) {
      Serial.println("b");
      isPaused = !isPaused;
    }
  }
}

void SnakeGame::IRInput() {
  if (IrReceiver.decode()) {

    switch (IrReceiver.decodedIRData.decodedRawData) {
      case BUTTON_ON:
        //        Serial.println("button on pressed");
        restart();
        break;
      case BUTTON_0:
        //        Serial.println("button 0 pressed");
        break;
      case BUTTON_1:
        //        Serial.println("button 1 pressed");
        snake.setDirection (  Direction::left);
        break;
      case BUTTON_2:
        //        Serial.println("button 2 pressed");
        snake.setDirection ( Direction::up);
        break;
      case BUTTON_3:
        //        Serial.println("button 3 pressed");
        snake.setDirection ( Direction::right);
        break;
      case BUTTON_4:
        //        Serial.println("button 4 pressed");
        snake.setDirection (  Direction::left);
        break;
      case BUTTON_5:
        //        Serial.println("button 5 pressed");
        snake.setDirection (  Direction::down);
        break;
      case BUTTON_6:
        //        Serial.println("button 6 pressed");
        snake.setDirection ( Direction::right);
        break;
      case BUTTON_7:
        //        Serial.println("button 7 pressed");
        break;
      case BUTTON_8:
        //        Serial.println("button 8 pressed");
        snake.setDirection (  Direction::down);
        break;
      case BUTTON_9:
        //        Serial.println("button 9 pressed");
        break;
      case BUTTON_VOL_PLUS:
        //        Serial.println("button vol + pressed");
        break;
      case BUTTON_VOL_MINUS:
        //        Serial.println("button vol - pressed");
        break;
      case BUTTON_PLAY_PAUSE:
        //        Serial.println("button vol - pressed");
        isPaused = !isPaused;
        break;
      case 0x0:

        //        Serial.println("button pressed double");
        break;
      default:
        break;
    }
    IrReceiver.resume();
  }
}


void SnakeGame::pauseGame() {
  isPaused = true;
}
void SnakeGame::resumeGame() {
  isPaused = false;
}

void SnakeGame::swapBuffers() {
  mainBuffer.swapBuffers(secondBuffer);
}
