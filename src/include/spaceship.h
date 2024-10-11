#pragma once

#include <raylib.h>
#include <boost/uuid/uuid_generators.hpp>

class Spaceship
{
private:
  boost::uuids::uuid id;

public:
  Rectangle shape{0, 390, 20, 10};

  Spaceship(int positionX);
  ~Spaceship();

  void move_left();
  void move_right();
  int get_position();
  void draw();

  static bool are_equal(const Spaceship &rhs, const Spaceship &lhs);
};

bool operator==(const Spaceship &rhs, const Spaceship &lhs);
