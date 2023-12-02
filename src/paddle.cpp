// Source (Implementation) file
#include <iostream>
#include <raylib.h>
#include "../header/paddle.hpp"

Paddle::Paddle(float input_x, float input_y, float input_width, float input_height, int input_speed) :
x(input_x), y(input_y), WIDTH(input_width), HEIGHT(input_height), speed(input_speed) {}
   
void Paddle::limit_movement() {
  // Prevent paddle from leaving the screen 
  if (y <= 0) {
    y = 0;
  }

  if (y + HEIGHT >= GetScreenHeight()) {
    y = GetScreenHeight() - HEIGHT;
  }
}  

// Getters for each attribute
float Paddle::get_x() const {
  return x;
}

float Paddle::get_y() const {
  return y;
}

float Paddle::get_width() const {
  return WIDTH;
}

float Paddle::get_height() const {
  return HEIGHT;
}

void Paddle::draw() {
  DrawRectangle(x, y, WIDTH, HEIGHT, WHITE);  // Draw right paddle
}

void Paddle::update() {
  // From Raylib library, use IsKeyDown to detect if a key is pressed
  // Check if the up key (KEY_UP) is pressed 
  if (IsKeyDown(KEY_UP)) {
    y = y - speed;
  }
  if (IsKeyDown(KEY_DOWN)) {
    y = y + speed;
  }
  limit_movement();
}

Paddle::~Paddle() {
  std::cout << "Paddle destructor\n";
}