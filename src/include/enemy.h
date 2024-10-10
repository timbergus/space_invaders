#pragma once

#include <raylib.h>
#include <boost/uuid/uuid_generators.hpp>

enum Direction
{
  LEFT,
  RIGHT,
};

class Enemy
{
private:
  boost::uuids::uuid id;

  Direction direction = LEFT;

  int position_x = 0;
  int position_y = 0;

public:
  Rectangle shape{0, 0, 20, 10};

  Enemy(int postion_x, int position_y, Direction direction);
  ~Enemy();

  void draw();

  static bool are_equal(const Enemy &rhs, const Enemy &lhs);
};

bool operator==(const Enemy &rhs, const Enemy &lhs);
