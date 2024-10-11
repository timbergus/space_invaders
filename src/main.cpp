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
  Sound explosion_sound = LoadSound("src/resources/explosion_02.mp3");

  std::vector<Projectile> projectiles;
  std::vector<Projectile> enemy_projectiles;
  std::vector<Enemy> enemies;
  std::vector<Spaceship> spaceships;

  bool projectile_added{false};

  Spaceship spaceship(screenWidth / 2 - 10);

  spaceships.push_back(spaceship);

  for (auto i : std::ranges::views::iota(0, 10))
  {
    Enemy enemy(40 + 30 * i, 20, LEFT);

    enemies.push_back(enemy);
  }

  PlaySound(game_start_sound);

  int time = 0;

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

      // Let's allow one single projectile on screen.

      if (IsKeyDown(KEY_SPACE) and projectiles.size() < 1)
      {
        if (!projectile_added)
        {
          Projectile projectile(spaceship.get_position(), screenHeight - 10, RED);
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

    auto local_time = static_cast<int>(GetTime());

    for (Enemy &enemy : enemies)
    {
      enemy.draw();
    }

    // Let's move the enemies once every second.

    if (time != local_time)
    {
      for (Enemy &enemy : enemies)
      {
        enemy.move_step();

        // Enemy shoot.

        auto enemy_position = enemy.get_position();

        Projectile projectile(std::get<0>(enemy_position), std::get<1>(enemy_position), YELLOW);
        enemy_projectiles.push_back(projectile);

        time = local_time;
      }
    }

    for (auto &projectile : projectiles)
    {
      for (auto &enemy : enemies)
      {
        if (CheckCollisionRecs(projectile.shape, enemy.shape))
        {
          enemies.erase(std::remove(enemies.begin(), enemies.end(), enemy), enemies.end());
          projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
          PlaySound(explosion_sound);
        }
      }

      if (projectile.is_alive())
      {
        projectile.move(UP);
      }
      else
      {
        projectiles.erase(std::remove(projectiles.begin(), projectiles.end(), projectile), projectiles.end());
      }
    }

    for (auto &projectile : enemy_projectiles)
    {
      for (auto &spaceship : spaceships)
      {
        if (CheckCollisionRecs(projectile.shape, spaceship.shape))
        {
          spaceships.erase(std::remove(spaceships.begin(), spaceships.end(), spaceship), spaceships.end());
          enemy_projectiles.erase(std::remove(enemy_projectiles.begin(), enemy_projectiles.end(), projectile), enemy_projectiles.end());
          PlaySound(explosion_sound);
        }
      }

      if (projectile.is_alive())
      {
        projectile.move(DOWN);
      }
      else
      {
        enemy_projectiles.erase(std::remove(enemy_projectiles.begin(), enemy_projectiles.end(), projectile), enemy_projectiles.end());
      }
    }

    EndDrawing();
  }

  UnloadSound(game_start_sound);
  UnloadSound(shoot_sound);
  UnloadSound(explosion_sound);

  CloseAudioDevice();

  CloseWindow();

  return EXIT_SUCCESS;
}
