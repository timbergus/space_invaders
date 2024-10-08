#pragma once

#include <raylib.h>

class Enemy
{
private:
  int direction = 1;

  int position_x = 0;
  int position_y = 0;

public:
  Rectangle shape{0, 0, 20, 10};

  Enemy(int postion_x, int position_y);
  ~Enemy();

  void draw();
};
