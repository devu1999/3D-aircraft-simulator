#include "main.h"

#ifndef BOSS_H
#define BOSS_H


class Boss {
public:
    Boss() {}
    Boss(glm::vec3 pos);
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
