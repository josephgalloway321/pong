// Header (Declaration) file

// The following is a preprocessor directive (specifically a header guard in this case) 
// that prevents the file from being included mutliple times in a single compilation
#pragma once   
#include <iostream>

class Ball {
  private: 
    float x, y;
    int speed_x, speed_y;
    const int RADIUS;
    int player_score;
    int cpu_score;
  
  public:
    Ball(float input_x, float input_y, int input_speed_x, int input_speed_y, int input_radius);
    float get_x() const;
    float get_y() const;
    int get_speed_x() const;
    int get_speed_y() const;
    int get_radius() const;
    int get_player_score() const;
    int get_cpu_score() const;
    void change_x_direction();
    void draw();
    void update();
    void reset_ball();
    void reset_scores();
    ~Ball();
};