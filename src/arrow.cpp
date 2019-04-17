#include "arrow.h"
#include "helper.h"
#include "main.h"
Arrow::Arrow(float x, float y, float z, color_t color) {
    this->position = glm::vec3(x,0,z);
    this->rotation = 0;
    this->achieved = false;


    int n = 1000;
    GLfloat vertex_buffer_data[n*100];
    cylinder(vertex_buffer_data,0,20,0,20.0f,80.0f,n,1000);
    this->object[0] = create3DObject(GL_TRIANGLES, n, vertex_buffer_data, COLOR_DDRED, GL_FILL);


    speed = 1;
    n = 9*5*5;
    GLfloat vertex_buffer_data1[n*9];
    pie(vertex_buffer_data1,0,100,0,40.0f,n,0,3*360);

    float x1 = 0.0f;
    float y1 = 140.0f;
    float z1 = 0.0f;

    for(int i = 0; i < n; i++)
    {
        vertex_buffer_data1[9*i + 0] = x1;
        vertex_buffer_data1[9*i + 1] = y1;
        vertex_buffer_data1[9*i + 2] = z1;
    }
    
    this->object[1] = create3DObject(GL_TRIANGLES, n, vertex_buffer_data1, COLOR_DDRED, GL_FILL);

}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Arrow::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Arrow::tick() {
    this->rotation += speed;
}