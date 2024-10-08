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

  InitAudioDevice();

  SetTargetFPS(120);

  Sound game_start_sound = LoadSound("src/resources/target.ogg");
  Sound shoot_sound = LoadSound("src/resources/shoot.mp3");
  Sound explosion = LoadSound("src/resources/explosion.mp3");

  std::vector<Projectile> projectiles;
  std::vector<Enemy> enemies;
  std::vector<Spaceship> spaceships;

  bool projectile_added{false};

  Spaceship spaceship(screenWidth / 2 - 10);

  spaceships.push_back(spaceship);

  for (auto i = 0; i < 8; i++)
  {
    Enemy enemy(screenWidth / 2 - 10, 20 + 12 * i, i % 2 == 0 ? LEFT : RIGHT);

    enemies.push_back(enemy);
  }

  PlaySound(game_start_sound);

  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    BeginDrawing();

    ClearBackground(DARKBLUE);

    for (int i = 0; i < static_cast<int>(spaceships.size()); i++)
    {
      if (IsKeyDown(KEY_RIGHT) && spaceships[i].get_position() <= screenWidth - 20)
      {
        spaceships[i].move_right();
      }

      if (IsKeyDown(KEY_LEFT) && spaceships[i].get_position() >= 0)
      {
        spaceships[i].move_left();
      }

      if (IsKeyDown(KEY_SPACE))
      {
        if (!projectile_added)
        {
          Projectile projectile(spaceships[i].get_position(), screenHeight - 10);
          projectiles.push_back(projectile);
          PlaySound(shoot_sound);
        }

        projectile_added = true;
      }
      else
      {
        projectile_added = false;
      }

      spaceships[i].draw();
    }

    for (Enemy &enemy : enemies)
    {
      enemy.draw();
    }

    for (int i = 0; i < static_cast<int>(projectiles.size()); i++)
    {
      for (int j = 0; j < static_cast<int>(enemies.size()); j++)
      {
        if (CheckCollisionRecs(projectiles[i].shape, enemies[j].shape))
        {
          enemies.erase(enemies.begin() + j);
          projectiles.erase(projectiles.begin() + i);
          PlaySound(explosion);
        }
      }

      if (projectiles[i].is_alive())
      {
        projectiles[i].move();
      }
      else
      {
        projectiles.erase(projectiles.begin() + i);
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
