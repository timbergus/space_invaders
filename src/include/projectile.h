#pragma once

#include <raylib.h>

class Projectile
{
private:
  int position_x = 0;
  int position_y = 0;

  void draw();

public:
  Rectangle shape{0, 0, 2, 10};

  Projectile(int position_x, int position_y);
  ~Projectile();

  void move();
  bool is_alive();
};
