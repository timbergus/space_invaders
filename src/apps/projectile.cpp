#include "projectile.h"

Projectile::Projectile(int position_x, int position_y)
{
  boost::uuids::random_generator generator;

  this->id = generator();
  this->position_x = position_x;
  this->position_y = position_y;
}

Projectile::~Projectile()
{
}

void Projectile::draw()
{
  shape.x = position_x + 9;
  shape.y = position_y;

  DrawRectangleRec(shape, RED);
}

void Projectile::move()
{
  position_y -= 2;
  draw();
}

bool Projectile::is_alive()
{
  return position_y > -20;
}

bool Projectile::are_equal(const Projectile &rhs, const Projectile &lhs)
{
  return rhs.id == lhs.id;
}

bool operator==(const Projectile &rhs, const Projectile &lhs)
{
  return Projectile::are_equal(rhs, lhs);
}
