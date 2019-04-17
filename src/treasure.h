#include "main.h"

#ifndef TREASURE_H
#define TREASURE_H


class Treasure {
public:
    Treasure() {}
    Treasure(glm::vec3 pos);
    void draw(glm::mat4 VP);
    void tick();

    glm::vec3 position;
    glm::vec3 direction;

    float rotation;
    float r, h;
    bool taken;
private:
    // VAO *object;
    VAO *treasureObject;
    VAO *pointsObject;
};

#endif // TREASURE_H
