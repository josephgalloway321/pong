// Source (Implementation) file
#include <iostream>
#include <raylib.h>
#include "../header/cpu_paddle.hpp"

// Inherit attributes & methods from Paddle class
// Call the Paddle constructor and pass in values from CpuPaddle constructor 
CpuPaddle::CpuPaddle(float input_x, float input_y, float input_width, float input_height, int input_speed) : Paddle(input_x, input_y, input_width, input_height, input_speed) {}
void CpuPaddle::update(int ball_y) {
  if (y + HEIGHT/2 > ball_y) {
    y = y - speed;
  }
  
  if (y + HEIGHT/2 <= ball_y) {
    y = y + speed;
  
  limit_movement();
  }
}