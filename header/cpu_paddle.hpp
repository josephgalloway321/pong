// Header (Declaration) file
#pragma once
#include <iostream>
#include "paddle.hpp"

class CpuPaddle: public Paddle {
  public:
    CpuPaddle(float input_x, float input_y, float input_width, float input_height, int input_speed);
    void update(int ball_y);
};