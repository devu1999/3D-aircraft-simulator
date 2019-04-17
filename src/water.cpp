#include <iostream>
using namespace std;

#include "water.h"
#include "main.h"
#include "helper.h"

Water::Water(float x, float y, float r, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->r = r;

    const int n = 100;

    GLfloat water_data[3*3*n];
    pie(water_data, 0, 0, 0, r, n, 0, 360);

    this->object = create3DObject(GL_TRIANGLES, 3*n, water_data, color, GL_FILL);
}

void Water::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    this->direction = glm::vec3(rotate * glm::vec4(0, 0, 1, 1.0f));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Water::setPosition(glm::vec3 newPosition) {
    this->position = newPosition;
}
