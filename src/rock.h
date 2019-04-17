#include "main.h"

#ifndef ROCK_H
#define ROCK_H


class Rock {
public:
    Rock() {}
    Rock(glm::vec3 pos, int n, float sz, float h, color_t color);
    void draw(glm::mat4 VP);

    glm::vec3 position;
    glm::vec3 direction;
    float r, h;
    bool taken;
private:
    VAO *object;
};

#endif // ROCK_H
