#include "main.h"
#ifndef BALL_H
#define BALL_H




class Ball {
public:
    Ball() {}
    Ball(float x, float y, color_t color);
    glm::vec3 position,direction;
    float rotation;
    float rzrotation;
    float rxrotation;
    bool detached;
    int fan_rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(int t, float camera_rotation_angle);
    void move(bool up, bool down, bool left, bool right);
    double speed_y;
    bounding_box_t bounding_box();
    void rotate(int dir);
private:
    VAO *object[10];
};

#endif // BALL_H


