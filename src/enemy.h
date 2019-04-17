#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(glm::vec3 pos, color_t color,int type);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    int type;
    double speed_x,speed_y,speed_z,acc_y;
    bounding_box_t bounding_box();
private:
    VAO *object[15];
};

#endif // ENEMY_H
