#include "goli.h"
#include "main.h"
#include "helper.h"

Goli::Goli(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    this->hit = false;
    acc_y = speed_x = speed_y = speed_z = 0.0;
    float pi = 3.142;
    int n = 1000;
    GLfloat vertex_buffer_data[n*100];
    cylinder(vertex_buffer_data,0,0,0,0.5f,2.0f,n,1000);
    for(int i = 0; i < 7*n; i++)
    {
        float x1 = vertex_buffer_data[i*3];
        float y1 = vertex_buffer_data[i*3+1];
        float z1 = vertex_buffer_data[i*3+2];
        // float x2 = x1;
        // float y2 = -z1;
        // float z2 = y1;

        float x3 = -y1;
        float y3 = x1;
        float z3 = z1;
        vertex_buffer_data[i*3] = x3;
        vertex_buffer_data[i*3+1] = y3;
        vertex_buffer_data[i*3+2] = z3;
    }

    
    this->object[0] = create3DObject(GL_TRIANGLES, n, vertex_buffer_data,COLOR_Yellow, GL_FILL);
    n = 9*5*5;
    GLfloat barrel_data[n*3];
    sphere(barrel_data, -2.0f, 0.0f, 0.0f, 0.6f, n);
    this->object[1] = create3DObject(GL_TRIANGLES, n, barrel_data,COLOR_DDRED, GL_FILL);
    GLfloat barrel_data1[n*3];
    sphere(barrel_data1, 0.0f, 0.0f, 0.0f, 0.5f, n);
    this->object[2] = create3DObject(GL_TRIANGLES, n, barrel_data1,COLOR_Yellow, GL_FILL);

}

void Goli::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
        draw3DObject(this->object[2]);
}

void Goli::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}
void Goli::change_speed(){
    speed_y += acc_y;
}
void Goli::tick() {
     change_speed();
     this->position.x += speed_x;
     this->position.y += speed_y;
     this->position.z += speed_z;

}
bounding_box_t Goli::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x - 2, y, z, 0.6, 0.6, 0.6 };
    return bbox;
}

