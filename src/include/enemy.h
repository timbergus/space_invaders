#pragma once

#include <raylib.h>

enum Direction
{
  LEFT,
  RIGHT,
};

class Enemy
{
private:
  Direction direction = LEFT;

  int position_x = 0;
  int position_y = 0;

public:
  Rectangle shape{0, 0, 20, 10};

  Enemy(int postion_x, int position_y, Direction direction);
  ~Enemy();

  void draw();
};
