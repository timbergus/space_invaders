#include "enemy.h"

Enemy::Enemy(int position_x, int position_y, Direction direction)
{
  boost::uuids::random_generator generator;

  this->id = generator();
  this->position_x = position_x;
  this->position_y = position_y;
  this->direction = direction;
}

Enemy::~Enemy()
{
}

void Enemy::draw()
{
  if (position_x < 380 && direction == RIGHT)
  {
    position_x += 1;
  }
  else
  {
    direction = LEFT;
  }

  if (position_x > 0 && direction == LEFT)
  {
    position_x -= 1;
  }
  else
  {
    direction = RIGHT;
  }

  shape.x = position_x;
  shape.y = position_y;

  DrawRectangleRec(shape, YELLOW);
}

bool Enemy::are_equal(const Enemy &rhs, const Enemy &lhs)
{
  return rhs.id == lhs.id;
}

bool operator==(const Enemy &rhs, const Enemy &lhs)
{
  return Enemy::are_equal(rhs, lhs);
}
