#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water {
public:
    Water() {}
    Water(float x, float y, float r, color_t color);
    glm::vec3 position;
    float speed;
    float r;
    glm::vec3 direction;
    float maxSpeed;
    float acceleration;
    float floatDir;
    float rotation;
    void draw(glm::mat4 VP);
    void setPosition(glm::vec3 newPosition);
    glm::vec3 getPosition();
private:
    VAO *object;
};

#endif // WATER_H
