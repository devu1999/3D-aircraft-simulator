#include <iostream>
using namespace std;

#include "ring.h"
#include "main.h"
#include "helper.h"

Ring::Ring(glm::vec3 pos) {
    this -> position = pos;
    this -> rotation = 0;
    this -> taken = false;
    this -> health = 60;

    
    int n = 9*5*5;
    // GLfloat vertex_buffer_data1[n*9];
    
    float x1 = 5;
    float y1 = 0;
    float z1 = 0;
    int k = 0;
    int nob = 100;
    float pi = 3.142;
    float theta = 2*pi/nob;
    GLfloat vertex_buffer_data[n*6*nob];


    GLfloat vertex_buffer_data1[n*3];
    
    for(int i = 0; i < 2*nob; i++)
    {
        sphere(vertex_buffer_data1, x1, y1, z1, 0.5f, n);
        float x2 = cos(theta)*x1 - sin(theta)*y1;
        float y2 = sin(theta)*x1 + cos(theta)*y1;
        x1 = x2;
        y1 = y2;


        for(int i = 0; i < n*3; i++)
        {
            vertex_buffer_data[k++] = vertex_buffer_data1[i];
        }
    }
    this->object = create3DObject(GL_TRIANGLES, n*nob, vertex_buffer_data, COLOR_DDRED, GL_FILL);
}

void Ring::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), V(1, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
        draw3DObject(this->object);
}

void Ring::tick(glm::vec3 pos) {
    rotation += 3;
    glm::vec3 dir = glm::normalize(pos - this->position);
    position += (0.05f * dir);
}