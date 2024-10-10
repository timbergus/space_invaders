#include <vector>
#include <raylib.h>
#include <fmt/core.h>
#include <algorithm>
#include <ranges>

#include "spaceship.h"
#include "projectile.h"
#include "enemy.h"

int main(int, char **)
{
  const int screenWidth{400};
  const int screenHeight{400};

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  InitWindow(screenWidth, screenHeight, "Space Invaders");

  InitAudioDevice();

  SetTargetFPS(120);

  Sound game_start_sound = LoadSound("src/resources/target.ogg");
  Sound shoot_sound = LoadSound("src/resources/shoot.mp3");
  Sound explosion = LoadSound("src/resources/explosion_02.mp3");

  std::vector<Projectile> projectiles;
  std::vector<Enemy> enemies;
  std::vector<Spaceship> spaceships;

  bool projectile_added{false};

  Spaceship spaceship(screenWidth / 2 - 10);

  spaceships.push_back(spaceship);

  for (auto i : std::ranges::views::iota(0, 6))
  {
    Enemy enemy(screenWidth / 2 - 10, 20 + 12 * i, i % 2 == 0 ? LEFT : RIGHT);

    enemies.push_back(enemy);
  }

  PlaySound(game_start_sound);

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(DARKBLUE);

    for (auto &spaceship : spaceships)
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
          PlaySound(shoot_sound);
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

    for (auto &projectile : projectiles)
    {
      for (auto &enemy : enemies)
      {
        if (CheckCollisionRecs(projectile.shape, enemy.shape))
        {
          enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
          projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
          PlaySound(explosion);
        }
      }

      if (projectile.is_alive())
      {
        projectile.move();
      }
      else
      {
        projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
      }
    }

    EndDrawing();
  }

  UnloadSound(game_start_sound);
  UnloadSound(shoot_sound);

  CloseAudioDevice();

  CloseWindow();

  return EXIT_SUCCESS;
}
