#pragma once

#include <raylib.h>
#include <boost/uuid/uuid_generators.hpp>

class Projectile
{
private:
  boost::uuids::uuid id;

  int position_x = 0;
  int position_y = 0;

  void draw();

public:
  Rectangle shape{0, 0, 2, 10};

  Projectile(int position_x, int position_y);
  ~Projectile();

  void move();
  bool is_alive();

  static bool are_equal(const Projectile &rhs, const Projectile &lhs);
};

bool operator==(const Projectile &rhs, const Projectile &lhs);
