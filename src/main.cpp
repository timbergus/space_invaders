#include <vector>
#include <raylib.h>
#include <fmt/core.h>

#include "spaceship.h"
#include "projectile.h"
#include "enemy.h"

int main(int, char **)
{
  const int screenWidth = 400;
  const int screenHeight = 400;

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "Space Invaders");

  SetTargetFPS(120);

  std::vector<Projectile> projectiles;
  std::vector<Enemy> enemies;
  std::vector<Spaceship> spaceships;

  bool projectile_added{false};

  Spaceship spaceship(screenWidth / 2 - 10);

  spaceships.push_back(spaceship);

  for (auto i = 0; i < 3; i++)
  {
    Enemy enemy(screenWidth / 2 - 10, 20 + 12 * i);

    enemies.push_back(enemy);
  }

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(DARKBLUE);

    for (Spaceship &spaceship : spaceships)
    {
      if (IsKeyDown(KEY_RIGHT) && spaceship.get_position() <= screenWidth - 20)
      {
        spaceship.move_right();
      }

      if (IsKeyDown(KEY_LEFT) && spaceship.get_position() >= 0)
      {
        spaceship.move_left();
      }

      if (IsKeyDown(KEY_SPACE))
      {
        if (!projectile_added)
        {
          Projectile projectile(spaceship.get_position(), screenHeight - 10);
          projectiles.push_back(projectile);
        }

        projectile_added = true;
      }
      else
      {
        projectile_added = false;
      }

      spaceship.draw();
    }

    for (Enemy &enemy : enemies)
    {
      enemy.draw();
    }

    for (Projectile &projectile : projectiles)
    {
      for (Enemy &enemy : enemies)
      {
        if (CheckCollisionRecs(projectile.shape, enemy.shape))
        {
          // auto enemy_position = std::find(enemies.begin(), enemies.end(), enemy);

          enemies.erase(enemies.begin());
          projectiles.erase(projectiles.begin());
        }
      }

      if (projectile.is_alive())
      {
        projectile.move();
      }
      else
      {
        projectiles.erase(projectiles.begin());
      }
    }

    EndDrawing();
  }

  CloseWindow();

  return EXIT_SUCCESS;
}
