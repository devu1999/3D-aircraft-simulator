#include <iostream>
using namespace std;

#include "boss.h"
#include "main.h"
#include "helper.h"

Boss::Boss(glm::vec3 pos) {
    this -> position = pos;
    this -> rotation = 0;
    this -> taken = false;
    this -> health = 60;

    GLfloat eye_data[4*36 * 3];
    cuboid(eye_data + 0*36*3, -0.7, -0.4, 3.5, 4, -2.0, 2.0);
    cuboid(eye_data + 1*36*3, 0.4, 0.7, 3.5, 4, -2.0, 2.0);
    cuboid(eye_data + 2*36*3, -0.3, 0.3, 1, 6.5, -0.5, 0.5);
    cuboid(eye_data + 3*36*3, -2.75, 2.75, 3.45, 4.05, -0.5, 0.5);
    this->object = create3DObject(GL_TRIANGLES, 4*36, eye_data, COLOR_BLACK, GL_FILL);

    const int n = 9 * 10 * 10;

    GLfloat skull_data[n*3];

    sphere(skull_data, 0, 3.75f, 0, 2.0f, n);
    // cuboid(skull_data + 0*36*3, -1, 1, 2.5, 5, -1, 1);
    // cuboid(skull_data + 1*36*3, -1, 1, 1.7, 2.1, -1, 1);
    this->healthObject = create3DObject(GL_TRIANGLES, n, skull_data, COLOR_RED, GL_FILL);
}

void Boss::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), V(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (!taken) {
        draw3DObject(this->object);
        draw3DObject(this->healthObject);
    }
}

void Boss::tick(glm::vec3 pos) {
    rotation += 3;
    glm::vec3 dir = glm::normalize(pos - this->position);
    position += (0.05f * dir);
}