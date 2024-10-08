#pragma once

#include <raylib.h>

class Spaceship
{
private:
  int positionX = 0;

public:
  Spaceship(int positionX);
  ~Spaceship();

  void move_left();
  void move_right();
  int get_position();
  void draw();
};
