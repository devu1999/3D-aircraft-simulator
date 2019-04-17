#include "enemy.h"
#include "main.h"
#include "helper.h"

Enemy::Enemy(glm::vec3 pos, color_t color,int type) {
    this->position = pos;
    this->position.y += 5 + rand()%10;
    this->rotation = 90;
    speed_y = 0.0001;
    float scale = 5.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    




    float lower = -1.0f;

    static const GLfloat vertex_buffer_data1[] = {
        
        0.0f*scale, lower*scale + 0.0f*scale,-1.0f*scale,
        -0.1f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        -0.3f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        
        0.0f*scale, lower*scale + 0.0f*scale,-1.0f*scale,
        0.1f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        0.3f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        
        
    };
    static const GLfloat vertex_buffer_data2[] = {

        0.0f*scale, lower*scale + 0.0f*scale,-1.0f*scale,
        -0.1f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        0.0f*scale,lower*scale + -1.0f*scale,1.1f*scale,
    };
    
    static const GLfloat vertex_buffer_data3[] = {
        
        
        
        0.0f*scale, lower*scale + 0.0f*scale,-1.0f*scale,
        0.1f*scale,lower*scale + 0.0f*scale,1.0f*scale,
        0.0f*scale,lower*scale + -1.0f*scale,1.1f*scale,
    };

    float pi = 3.142;
    int n = 9*5*5;
    GLfloat barrel_data[n*9];
    // sphere(barrel_data, 0.0f, 40.0f, 0.0f, 10, n);
    pie(barrel_data,0,0,0,3,n,0,3*360);


    GLfloat barrel_data1[n*9];
    pie(barrel_data1,0,5.0f,0,6,n,0,3*360);
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

    
    this->object[5] = create3DObject(GL_TRIANGLES, n, barrel_data1,COLOR_Yellow, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, 6*n, vertex_buffer_data,COLOR_FIRE, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, n, barrel_data,COLOR_ORANGE, GL_FILL);


    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_RED, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_DRED, GL_FILL);
    this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_DDRED, GL_FILL);

    n = 1000;
    GLfloat barrel_data2[n*100];
    cylinder(barrel_data2, 0.0f, -2.0f, 0.0f, 3,3, n,100);
    this->object[6] = create3DObject(GL_TRIANGLES, n, barrel_data2,COLOR_DARK, GL_LINE);

    GLfloat barrel_data3[n*100];
    cylinder(barrel_data3, 0.0f, -7.5f, 0.0f, 4,5, n,100);
    this->object[7] = create3DObject(GL_TRIANGLES, n, barrel_data3,COLOR_PLANE, GL_FILL);
    // GLfloat t1[9];
    // k = 0;
    // t1[k++] = 1.0f;
    // t1[k++] = 0.0f;
    // t1[k++] = -1.0f;
    // t1[k++] = 1.0f;
    // t1[k++] = 0.0f;
    // t1[k++] = 1.0f;
    // t1[k++] =   0.0f;
    // t1[k++] = -lower*scale;
    // t1[k++] =  0.0f;

    // this->object[7] = create3DObject(GL_TRIANGLES, 1, t1,COLOR_DDRED, GL_FILL);
}

void Enemy::draw(glm::mat4 VP) {

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);
    draw3DObject(this->object[6]);
    draw3DObject(this->object[7]);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, -0.01, y);
}

void Enemy::change_speed(){
//    if(this->position.y == 0.1)
//        speed_y = -speed_y;
}

void Enemy::tick() {
    change_speed();
    // this->rotation += speed;
     this->position.x += 0.05f;
     this->position.z += 0.05f;
}

bounding_box_t Enemy::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 1.4, 1.4, 1.4 };
    return bbox;
}

