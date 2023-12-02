// Source (Implementation) file
#include <iostream>
#include <raylib.h>
#include "../header/ball.hpp"

Ball::Ball(float input_x, float input_y, int input_speed_x, int input_speed_y, int input_radius) : 
x(input_x), y(input_y), speed_x(input_speed_x), speed_y(input_speed_y), RADIUS(input_radius) {
  player_score = 0;
  cpu_score = 0;
}

// Getters/setters for each attribute
float Ball::get_x() const {
  return x;
}

float Ball::get_y() const {
  return y;
}

int Ball::get_speed_x() const {
  return speed_x;
}

int Ball::get_speed_y() const {
  return speed_y;
}

int Ball::get_radius() const {
  return RADIUS;
}

int Ball::get_player_score() const {
  return player_score;
}

int Ball::get_cpu_score() const {
  return cpu_score;
}

void Ball::change_x_direction() {
  speed_x *= -1;
}

void Ball::draw() {
  DrawCircle(x, y, RADIUS, WHITE);
}

void Ball::update() {
  x += speed_x;
  y += speed_y;
  // Logic for detecting top and bottom edges
  if (y + RADIUS >= GetScreenHeight() || y - RADIUS <= 0) {
    speed_y *= -1;
  }
  
  // Logic for detecting left and right edges
  if (x + RADIUS >= GetScreenWidth()) {
    cpu_score++;
    reset_ball();
  }
  
  if (x - RADIUS <= 0) {
    player_score++;
    reset_ball();
  }
}

void Ball::reset_ball() {
  x = GetScreenWidth()/2;
  y = GetScreenHeight()/2;
  int speed_choices[2] = {-1, 1};
  speed_x *= speed_choices[GetRandomValue(0, 1)];
  speed_y *= speed_choices[GetRandomValue(0, 1)];
}

// Destructor
Ball::~Ball() {
  std::cout << "Ball destructor\n";
}