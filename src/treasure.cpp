#include <iostream>
using namespace std;

#include "treasure.h"
#include "main.h"
#include "helper.h"

Treasure::Treasure(glm::vec3 pos) {
    this -> position = pos;
    position.y += 0.5;
    this -> rotation = 0;
    this -> taken = false;

    int curr = 0;
    GLfloat treasure_data[36 * 3];
    cuboid(treasure_data, -1, 1, 0, 1, -0.5, 0.5); curr += (36 * 3);
    this->treasureObject = create3DObject(GL_TRIANGLES, curr / 3, treasure_data, COLOR_DARK_BROWN, GL_FILL);


    GLfloat points_data[5*16*9 * 3];
    curr = 0;
    diamond(points_data, 0, 1, 0, 0.2); curr += 16*9 * 3;
    diamond(points_data + curr, 0.3, 1, 0, 0.2); curr += 16*9 * 3;
    diamond(points_data + curr, 0, 1, 0.4, 0.2); curr += 16*9 * 3;
    diamond(points_data + curr, -0.5, 1, -0.1, 0.2); curr += 16*9 * 3;
    diamond(points_data + curr, 0.5, 1, -0.3, 0.2); curr += 16*9 * 3;
    this->pointsObject = create3DObject(GL_TRIANGLES, 5*16*9, points_data, COLOR_PURPLE, GL_FILL);
}

void Treasure::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), V(0, 1, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    if (!taken) {
        draw3DObject(this->treasureObject);
        draw3DObject(this->pointsObject);
    }
}

void Treasure::tick() {
    rotation += 1;
}