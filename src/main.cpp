#include <iostream>
#include <raylib.h>
#include "../header/ball.hpp"
#include "../header/paddle.hpp"
#include "../header/cpu_paddle.hpp"

int main()
{
  std::cout << "Starting the game...\n";

  // Initialize the window
  const int SCREEN_WIDTH = 1280;
  const int SCREEN_HEIGHT = 800;
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pong");
  SetTargetFPS(60);  // Determine how fast game will run (# of frames per second)

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
    BeginDrawing();  // Create a blank canvas to begin drawing game objects

    // Update
    ball.update();
    player.update();
    cpu.update(ball.get_y());
    UpdateMusicStream(music);

    // Check for collisions between ball and paddles
    if (CheckCollisionCircleRec(Vector2{ball.get_x(), ball.get_y()}, ball.get_radius(), Rectangle{player.get_x(), player.get_y(), player.get_width(), player.get_height()})) {
      ball.change_x_direction();
      PlaySound(quack_sound);
    }
    // TODO: Try renaming audio to SoundEffect

    if (CheckCollisionCircleRec(Vector2{ball.get_x(), ball.get_y()}, ball.get_radius(), Rectangle{cpu.get_x(), cpu.get_y(), cpu.get_width(), cpu.get_height()})) {
      ball.change_x_direction();
      PlaySound(quack_sound);
    }

    // Draw game objects
    ClearBackground(BLACK);
    DrawLine(SCREEN_WIDTH/2, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT, WHITE);  // Draw the center line dividing the two sides
    ball.draw();  // Call draw method for ball
    cpu.draw();
    player.draw();  // Call draw method for player

    DrawText(TextFormat("%i", ball.get_cpu_score()), SCREEN_WIDTH/4 - 20, 20, 80, WHITE);  // Display CPU Score
    DrawText(TextFormat("%i", ball.get_player_score()), 3*SCREEN_WIDTH/4 - 20, 20, 80, WHITE);  // Display player Score

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