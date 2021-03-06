#include "main.h"

#ifndef ARROW_H
#define ARROW_H


class Arrow {
public:
    Arrow() {}
    Arrow(float x, float y, float z,color_t color);
    glm::vec3 position;
    float rotation;
    bool achieved;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object[5];
};

#endif // LAND_H
