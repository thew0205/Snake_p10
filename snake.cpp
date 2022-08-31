#include "snake.h"

Snake::Snake(int width , int height): boundaryWidth(width), boundaryHeight(height)  {
  reset();
}
void Snake::update( unsigned int elaspedTime) {
  switch  (direction) {
    case Direction::left:
      head.x--;
      break;
    case Direction::right:
      head.x++;
      break;
    case Direction::up:
      head.y--;
      break;
    case Direction::down:
      head.y++;
      break;
  }
  move();
}

void Snake::move() {
  for (byte i = 1; i < _bodyLenght ; i++) {
    body[_bodyLenght - i] =  body[_bodyLenght - i - 1];
  }
  body[0] = head;
}

void Snake::render(DMDFrame& screen) const {
  for (byte i = 0; i < _bodyLenght; i++) {
    body[i].render(screen);
  }
}


bool Snake::pointExist(const Point& point) const {
  for (byte i = 0; i < _bodyLenght ; i++) {
    if ( body[i] ==  point) {
      return true;
    }
  }
  return false;
}

void Snake::setDirection(Direction newDirection) {
  if ((direction == Direction::left && newDirection == Direction::right) || (direction == Direction::right && newDirection == Direction::left))return;
  if ((direction == Direction::up && newDirection == Direction::down) || (direction == Direction::down && newDirection == Direction::up))return;
  direction = newDirection;
}
void  Snake::reset () {
  _bodyLenght = 4;
  head = Point (boundaryWidth / 2 , boundaryHeight / 2);
  direction = Direction::right;
  speed = 1;
  isAlive = true;
  for (byte i = 0; i < 32 ; i++) {
    body[i ].x = -1;
    body[i].y = -1;
  }
  body[0] = head;
  for (byte i = 0; i < _bodyLenght ; i++) {
    body[i + 1].x = body[i].x - 1;
    body[i + 1].y = body[i].y ;
  }
}
bool Snake::checkIfStillAlive()const {
  if (( head.x > boundaryWidth - 2 || head.x <  1 ) || ( head.y > boundaryHeight - 2 || head.y <  1)) {
    return false;
  }
  if (headEatsBody()) {
    return false;
  }
  return true;
}

bool Snake::headEatsBody() const {

  for (byte i = 3 ; i < _bodyLenght; i++) {
    if (head == body[i]) {
      return true;
    }
  }
  return false;
}

void  Snake::grow() {
  _bodyLenght++;
}

Point::Point(byte x , byte y ): x(x), y(y) {}

bool Point::operator==(const Point & other)const {
  return x == other.x && y == other.y;
}

void Point::render(DMDFrame& screen) const {
  screen.setPixel(x, y);
}
