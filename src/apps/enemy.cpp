#include "enemy.h"

Enemy::Enemy(int position_x, int position_y, EnemyDirection direction)
{
  boost::uuids::random_generator generator;

  this->id = generator();

  this->shape.x = position_x;
  this->shape.y = position_y;

  this->direction = direction;
}

Enemy::~Enemy()
{
}

void Enemy::move()
{
  if (shape.x < 380 && direction == RIGHT)
  {
    shape.x += 1;
  }
  else
  {
    direction = LEFT;
  }

  if (shape.x > 0 && direction == LEFT)
  {
    shape.x -= 1;
  }
  else
  {
    direction = RIGHT;
  }
}

void Enemy::move_step()
{
  if (shape.x <= 0 or shape.x >= 380)
  {
    shape.y += 10;
  }

  if (shape.x < 380 && direction == RIGHT)
  {
    shape.x += 10;
  }
  else
  {
    direction = LEFT;
  }

  if (shape.x > 0 && direction == LEFT)
  {
    shape.x -= 10;
  }
  else
  {
    direction = RIGHT;
  }
}

void Enemy::draw()
{
  DrawRectangleRec(shape, YELLOW);
}

std::tuple<int, int> Enemy::get_position()
{
  return {shape.x, shape.y};
}

bool Enemy::are_equal(const Enemy &rhs, const Enemy &lhs)
{
  return rhs.id == lhs.id;
}

bool operator==(const Enemy &rhs, const Enemy &lhs)
{
  return Enemy::are_equal(rhs, lhs);
}
