#include "projectile.h"

Projectile::Projectile(int position_x, int position_y, Color color)
{
  boost::uuids::random_generator generator;

  this->id = generator();

  shape.x = position_x + 9;
  shape.y = position_y;

  this->color = color;
}

Projectile::~Projectile()
{
}

void Projectile::draw()
{
  DrawRectangleRec(shape, color);
}

void Projectile::move(ProjectileDirection direction)
{
  switch (direction)
  {
  case UP:
    shape.y -= 2;
    break;
  case DOWN:
    shape.y += 2;
    break;
  default:
    break;
  }

  draw();
}

bool Projectile::is_alive()
{
  return shape.y > -20 and shape.y < 420;
}

bool Projectile::are_equal(const Projectile &rhs, const Projectile &lhs)
{
  return rhs.id == lhs.id;
}

bool operator==(const Projectile &rhs, const Projectile &lhs)
{
  return Projectile::are_equal(rhs, lhs);
}
