// Header (Declaration) file
#pragma once
#include <iostream>

class Paddle {
  // Same as private attributes & methods except these are accessible through inheritence
  protected:
    float x, y;
    const float WIDTH, HEIGHT;
    int speed;
    void limit_movement();
  
  public:
    Paddle(float input_x, float input_y, float input_width, float input_height, int input_speed);
    float get_x() const;
    float get_y() const;
    float get_width() const;
    float get_height() const;
    void draw();
    void update();
    ~Paddle();
};