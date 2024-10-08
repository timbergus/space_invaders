#include "enemy.h"

Enemy::Enemy(int position_x, int position_y)
{
  this->position_x = position_x;
  this->position_y = position_y;
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
  if (position_x < 380 && direction == 1)
  {
    position_x += 1;
  }
  else
  {
    direction = 0;
  }

  if (position_x > 0 && direction == 0)
  {
    position_x -= 1;
  }
  else
  {
    direction = 1;
  }

  shape.x = position_x;
  shape.y = position_y;

  DrawRectangleRec(shape, YELLOW);
}
