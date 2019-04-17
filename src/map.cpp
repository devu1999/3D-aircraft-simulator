#include "map.h"
#include "main.h"
#include "helper.h"

Map::Map(float x, float y, float z, float r, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[9*n];
    float x1 = r;
    float y1 = 0.0f;
    float z1 = 0.0f;
    int k = 0;
    for(int i = 1; i <= n; i++)
    {
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        float x2 = x1*cos(2*pi/n) - sin(2*pi/n)*y1;
        float y2 = sin(2*pi/n)*x1 + cos(2*pi/n)*y1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = 0.0f;
        x1 = x2;
        y1 = y2; 
    }

    GLfloat t1[9];
    k = 0;
    int scale = 3;
    t1[k++] = 0.0f;
    t1[k++] = r + 0.02f*scale;
    t1[k++] = 0.0f;

    t1[k++] = 0.01f*scale;
    t1[k++] = r;
    t1[k++] = 0.0f;

    t1[k++] = -0.01f*scale;
    t1[k++] = r;
    t1[k++] = 0.0f;
    this->object[0] = create3DObject(GL_TRIANGLES, n*3, vertex_buffer_data, color, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 3, t1, COLOR_DARK, GL_FILL);
        

}

void Map::draw(glm::mat4 VP, int cn) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    if(cn == 1)
        draw3DObject(this->object[1]);
}

void Map::set_position(float x, float y) {
    this->position = glm::vec3(x, y, this->position.z);
}


