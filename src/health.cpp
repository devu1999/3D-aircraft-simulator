#include <iostream>
using namespace std;

#include "health.h"
#include "main.h"
#include "helper.h"

Health::Health(glm::vec3 pos) {
    this -> position = pos;
    this -> rotation = 0;
    this -> taken = false;

    const int n = 9 * 5 * 5;

    GLfloat barrel_data[n*3];
    sphere(barrel_data, 0, 0, 0, 0.5f, n);
    this->object = create3DObject(GL_TRIANGLES, n, barrel_data, COLOR_DARK_BROWN, GL_FILL);

    GLfloat health_data[2*36 * 3];
    cuboid(health_data + 0*36*3, -1, 1, 3.5, 4.5, -0.2, 0.2);
    cuboid(health_data + 1*36*3, -0.5, 0.5, 3, 5, -0.2, 0.2);
    this->healthObject = create3DObject(GL_TRIANGLES, 2*36, health_data, COLOR_GREEN, GL_FILL);
}

void Health::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), V(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
    if (!taken)
        draw3DObject(this->healthObject);
}

void Health::tick() {
    rotation += 1;
}