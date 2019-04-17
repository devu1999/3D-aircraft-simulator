#include "main.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H
class Score {
public:
    Score() {}
    Score(float x, float y,int no, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Scoreboard {
public:
    Scoreboard() {}
    Scoreboard(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};
class Lifebar {
public:
    Lifebar() {}
    Lifebar(float x, float y, color_t color,float score);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

class Emptybar {
public:
    Emptybar() {}
    Emptybar(float x, float y, color_t color,float score);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    double speed;
private:
    VAO *object;
};

#endif