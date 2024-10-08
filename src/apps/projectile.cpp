#include "projectile.h"

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

Projectile::Projectile(int position_x, int position_y)
{
  this->position_x = position_x;
  this->position_y = position_y;
}

Projectile::~Projectile()
{
}
