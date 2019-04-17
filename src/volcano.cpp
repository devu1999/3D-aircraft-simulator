#include "volcano.h"
#include "main.h"
#include "helper.h"

Volcano::Volcano(float x, float y, color_t color) {
    this->position = glm::vec3(x, 0, y);
    this->rotation = 0;
    acc_y = speed_x = speed_y = speed_z = 0.0;
    float pi = 3.142;
    int n = 9*5*5;
    GLfloat barrel_data[n*9];
    // sphere(barrel_data, 0.0f, 40.0f, 0.0f, 10, n);
    pie(barrel_data,0,40.0f,0,10,n,0,3*360);


    GLfloat barrel_data1[n*9];
    pie(barrel_data1,0,0,0,50,n,0,3*360);
    GLfloat vertex_buffer_data[n*100];
    // cylinder(vertex_buffer_data,0,0,0,0.5f,2.0f,n,1000);
    float x1,y1,z1,x2,y2,z2,x3,y3,z3,x4,y4,z4;
    int k = 0;
    x1 = barrel_data[0];
    y1 = barrel_data[1];
    z1 = barrel_data[2];
    x2 = barrel_data1[0];
    y2 = barrel_data1[1];
    z2 = barrel_data1[2];
    for(int i = 1; i < 3*n; i++)
    {
        x3 = barrel_data[3*i + 0];
        y3 = barrel_data[3*i + 1];
        z3 = barrel_data[3*i + 2];
        x4 = barrel_data1[3*i + 0];
        y4 = barrel_data1[3*i + 1];
        z4 = barrel_data1[3*i + 2];

        vertex_buffer_data[k++] = x1;
        vertex_buffer_data[k++] = y1;
        vertex_buffer_data[k++] = z1;
        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = z2;
        vertex_buffer_data[k++] = x3;
        vertex_buffer_data[k++] = y3;
        vertex_buffer_data[k++] = z3;

        vertex_buffer_data[k++] = x2;
        vertex_buffer_data[k++] = y2;
        vertex_buffer_data[k++] = z2;
        vertex_buffer_data[k++] = x3;
        vertex_buffer_data[k++] = y3;
        vertex_buffer_data[k++] = z3;
        vertex_buffer_data[k++] = x4;
        vertex_buffer_data[k++] = y4;
        vertex_buffer_data[k++] = z4;

        x1 = barrel_data[3*i + 0];
        y1 = barrel_data[3*i + 1];
        z1 = barrel_data[3*i + 2];
        x2 = barrel_data1[3*i + 0];
        y2 = barrel_data1[3*i + 1];
        z2 = barrel_data1[3*i + 2];
    }

    
    this->object[0] = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_DARK_BROWN, GL_FILL);
    
    this->object[1] = create3DObject(GL_TRIANGLES, n, barrel_data,COLOR_ORANGE, GL_FILL);
    

}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
}

void Volcano::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}
void Volcano::change_speed(){
    speed_y += acc_y;
}
void Volcano::tick() {
     change_speed();
     this->position.x += speed_x;
     this->position.y += speed_y;
     this->position.z += speed_z;

}
bounding_box_t Volcano::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x - 2, y, z, 0.6, 0.6, 0.6 };
    return bbox;
}

