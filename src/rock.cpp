#include <iostream>
using namespace std;

#include "rock.h"
#include "main.h"
#include "helper.h"

Rock::Rock(glm::vec3 pos, const int n, float sz, float h, color_t color) {
    this -> position = pos;
    this -> r = sz;

    const int cn = n;

    GLfloat rock_data[n*3 + 2*cn*3*3];

    cylinder(rock_data, 0, 0, 0, sz, h, n, cn);

    this->object = create3DObject(GL_TRIANGLES, n + 2*cn*3, rock_data, color, GL_FILL);
}

void Rock::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
