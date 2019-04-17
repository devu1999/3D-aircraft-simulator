#include "bomb.h"
#include "main.h"
#include "helper.h"

Bomb::Bomb(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    this->hit = false;
    acc_y = speed_x = speed_y = speed_z = 0.0;
    float pi = 3.142;
    int n = 9*5*5;
    GLfloat barrel_data1[n*3];
    sphere(barrel_data1, 0.0f, 0.0f, 0.0f, 0.5f, n);
    this->object[0] = create3DObject(GL_TRIANGLES, n, barrel_data1,COLOR_Yellow, GL_FILL);

}

void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
}

void Bomb::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}
void Bomb::change_speed(){
    speed_y += acc_y;
}
void Bomb::tick() {
     change_speed();
     this->position.y -= 0.2f;

}
bounding_box_t Bomb::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x - 2, y, z, 0.6, 0.6, 0.6 };
    return bbox;
}

