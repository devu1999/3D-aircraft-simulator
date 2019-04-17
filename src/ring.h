#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(glm::vec3 po);
    void draw(glm::mat4 VP);
    void tick(glm::vec3 pos);

    glm::vec3 position;
    glm::vec3 direction;

    float rotation;
    float r, h;
    bool taken;
    float health;
private:
    VAO *object;
    VAO *healthObject;
};

#endif // BOSS_H
