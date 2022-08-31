#pragma once
#include <Arduino.h>
#include <DMD2.h>



class Point {
  public:
    byte x ;
    byte y;
    Point (byte x = 0, byte y = 0);
    bool operator==(const Point & point)const ;
    void render(DMDFrame& screen)const;
};

enum class Direction : byte {
  left,
  right,
  up,
  down,
};

class Snake {
    Point head ;
    Point body[32];
    Direction direction{Direction::right};
    byte _bodyLenght{4};
    byte speed {1};
    bool isAlive {true};
    byte boundaryWidth;
    byte boundaryHeight;

  public:
    void setDirection(Direction direction);
    Snake(int width , int height );
    void update(unsigned int elaspedTime);
    void render(DMDFrame& screen)const ;
    void move();
    bool checkIfStillAlive()const;
    bool headEatsBody()const;
    bool pointExist(const Point& point) const;
    void  reset ();
    void grow();
    inline byte bodyLenght() const {
      return  _bodyLenght;
    }
    inline Point getBodyPoint(byte i) const {
      return body[i];
    }


};
