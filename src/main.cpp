/*
*
*
*/


#include <iostream>
#include <raylib.h>
#include "../header/ball.hpp"
#include "../header/paddle.hpp"
#include "../header/cpu_paddle.hpp"

typedef enum GameScreen {title, gameplay, ending} GameScreen;

int main()
{
  std::cout << "Starting the game...\n";

  // Initialize the window & game screen
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 800;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
  SetTargetFPS(60);  // Determine how fast game will run (# of frames per second)
  GameScreen current_screen = title;  // Start the game on the title screen

  // Initialize the game objects
  Ball ball(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 7, 7, 20);
  Paddle player(SCREEN_WIDTH - player.get_width() - 10, SCREEN_HEIGHT/2 - player.get_height()/2, 25, 120, 6);
  CpuPaddle cpu(10, SCREEN_HEIGHT/2 - cpu.get_height()/2, 25, 120, 6);

  // Initialize the audio & adjust the volumes
  InitAudioDevice();
  Sound quack_sound = LoadSound("C:/Users/josep/Documents/GitHub/pong/resources/quack.wav");
  SetSoundVolume(quack_sound, 0.75);
  Music music = LoadMusicStream("C:/Users/josep/Documents/GitHub/pong/resources/background_music.mp3");
  PlayMusicStream(music);  // Play the background music
  SetMusicVolume(music, 0.5);
  
  // Game Loop
  // If the esc key or close window icon is clicked, then the window will close
  while(WindowShouldClose() == false) {
    // Update
    switch (current_screen) {
      case title: {
        if (IsKeyPressed(KEY_SPACE)) {
          // User pressed spacebar, so proceed to gameplay on the next loop
          current_screen = gameplay;
        }
      } break;

      case gameplay: {
        ball.update();
        player.update();
        cpu.update(ball.get_y());
        UpdateMusicStream(music);

        // Check for collisions between ball and paddles
        if (CheckCollisionCircleRec(Vector2{ball.get_x(), ball.get_y()}, ball.get_radius(), Rectangle{player.get_x(), player.get_y(), player.get_width(), player.get_height()})) {
          ball.change_x_direction();
          PlaySound(quack_sound);
        }

        if (CheckCollisionCircleRec(Vector2{ball.get_x(), ball.get_y()}, ball.get_radius(), Rectangle{cpu.get_x(), cpu.get_y(), cpu.get_width(), cpu.get_height()})) {
          ball.change_x_direction();
          PlaySound(quack_sound);
        }

        // If the cpu or player score passes the maximum score, then end the game
        if (ball.get_cpu_score() >= 3 || ball.get_player_score() >= 3) {
          current_screen = ending;
        }
      } break;

      case ending: {
        if (IsKeyPressed(KEY_SPACE)) {
          // User pressed spacebar, so proceed to title on the next loop
          current_screen = title;
          ball.reset_scores();
        }
      } break;

      default:
        break;
    }
    
    // Draw game objects
    BeginDrawing();  // Create a blank canvas to begin drawing game objects
    ClearBackground(BLACK);  // Begin with a black screen

    switch (current_screen) {
      case title: {
        DrawText("Pong", 120, 120, 20, WHITE);
        DrawText("First to 3 wins!", 120, 220, 20, WHITE);
        DrawText("Press the spacebar to begin...", 120, 270, 20, WHITE);
      } break;

      case gameplay: {
        DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, WHITE);  // Draw the center line dividing the two sides
        ball.draw();  // Call draw method for ball
        cpu.draw();
        player.draw();  // Call draw method for player

        DrawText(TextFormat("%i", ball.get_cpu_score()), SCREEN_WIDTH/4 - 20, 20, 80, WHITE);  // Display CPU Score
        DrawText(TextFormat("%i", ball.get_player_score()), 3*SCREEN_WIDTH/4 - 20, 20, 80, WHITE);  // Display player Score
      } break;

      case ending: {
        DrawText("Game Over", 120, 120, 20, RED);
        DrawText("Press the spacebar to return to the title screen", 120, 220, 20, WHITE);
        DrawText("Press the escape key to close the game", 120, 270, 20, WHITE);
      } break;

      default:
        break;
    }
    EndDrawing();  // Ends the canvas drawing
  }

  //  Unload & close audio
  UnloadSound(quack_sound);
  StopMusicStream(music);
  CloseAudioDevice();
 
  // Close the window & end the game
  CloseWindow();

  return 0;
}