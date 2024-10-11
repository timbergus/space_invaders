#include "spaceship.h"

Spaceship::Spaceship(int position_x)
{
  boost::uuids::random_generator generator;

  this->id = generator();

  shape.x = position_x;
}

Spaceship::~Spaceship()
{
}

void Spaceship::move_left()
{
  shape.x -= 1;
}

void Spaceship::move_right()
{
  shape.x += 1;
}

int Spaceship::get_position()
{
  return shape.x;
}

void Spaceship::draw()
{
  DrawRectangleRec(shape, RED);
}

bool Spaceship::are_equal(const Spaceship &rhs, const Spaceship &lhs)
{
  return rhs.id == lhs.id;
}

bool operator==(const Spaceship &rhs, const Spaceship &lhs)
{
  return Spaceship::are_equal(rhs, lhs);
}
