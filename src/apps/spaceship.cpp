#include "spaceship.h"

Spaceship::Spaceship(int positionX)
{
  this->positionX = positionX;
}

Spaceship::~Spaceship()
{
}

void Spaceship::move_left()
{
  positionX -= 1;
}

void Spaceship::move_right()
{
  positionX += 1;
}

int Spaceship::get_position()
{
  return positionX;
}

void Spaceship::draw()
{
  DrawRectangle(positionX, 390, 20, 10, RED);
}
