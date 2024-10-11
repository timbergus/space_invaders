#pragma once

#include <raylib.h>
#include <boost/uuid/uuid_generators.hpp>

enum ProjectileDirection
{
  UP,
  DOWN,
};

class Projectile
{
private:
  boost::uuids::uuid id;
  Color color;

  void draw();

public:
  Rectangle shape{0, 0, 2, 10};

  Projectile(int position_x, int position_y, Color color);
  ~Projectile();

  void move(ProjectileDirection direction);
  bool is_alive();

  static bool are_equal(const Projectile &rhs, const Projectile &lhs);
};

bool operator==(const Projectile &rhs, const Projectile &lhs);
