#include "main.h"

#ifndef MAP_H
#define MAP_H


class Map {
public:
    Map() {}
    Map(float x, float y, float z,float r, color_t color);
    glm::vec3 position;
    float rotation;
    double speed_y,acc_y,speed_x,speed_z;
    void draw(glm::mat4 VP,int cn);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object[5];
};


class Movedir {
public:
    Movedir() {}
    Movedir(float x, float y, float z,float r, color_t color);
    glm::vec3 position;
    float rotation;
    float rx;
    double speed_y,acc_y,speed_x,speed_z;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    void change_speed();
    double speed;
    bounding_box_t bounding_box();
private:
    VAO *object[5];
};

#endif // BALL_H
