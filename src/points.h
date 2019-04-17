#include "main.h"

#ifndef POINTS_H
#define POINTS_H


class Points {
public:
    Points() {}
    Points(glm::vec3 pos);
    void draw(glm::mat4 VP);
    void tick();

    glm::vec3 position;
    glm::vec3 direction;

    float rotation;
    float r, h;
    bool taken;
private:
    VAO *object;
    VAO *pointsObject;
};

#endif // POINTS_H
