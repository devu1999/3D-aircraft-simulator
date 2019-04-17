#include "main.h"

#ifndef HEALTH_H
#define HEALTH_H


class Health {
public:
    Health() {}
    Health(glm::vec3 pos);
    void draw(glm::mat4 VP);
    void tick();

    glm::vec3 position;
    glm::vec3 direction;

    float rotation;
    float r, h;
    bool taken;
private:
    VAO *object;
    VAO *healthObject;
};

#endif // HEALTH_H
