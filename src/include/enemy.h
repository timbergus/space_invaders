#pragma once

#include <raylib.h>
#include <boost/uuid/uuid_generators.hpp>
#include <vector>

#include "projectile.h"

enum EnemyDirection
{
  LEFT,
  RIGHT,
};

class Enemy
{
private:
  boost::uuids::uuid id;

  EnemyDirection direction = LEFT;

public:
  Rectangle shape{0, 0, 20, 10};
  std::vector<Projectile> projectiles;

  Enemy(int postion_x, int position_y, EnemyDirection direction);
  ~Enemy();

  void move();
  void move_step();
  void shoot();
  void draw();

  static bool are_equal(const Enemy &rhs, const Enemy &lhs);
};

bool operator==(const Enemy &rhs, const Enemy &lhs);
