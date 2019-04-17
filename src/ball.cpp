#include "ball.h"
#include "main.h"
#include "helper.h"


color_t COLOR_BLUE ={ 0 , 0, 190};

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, 2, y);
    this -> direction = glm::vec3(0, 0, 1);
    this->rotation = 180;
    this->rzrotation = 0;
    this->rxrotation = 0;
    this -> detached = false;
    speed_y = 0.0001;
    float scale = 2.0f;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
     GLfloat vertex_buffer_data1[] = {
        
        0.0f*scale, 0.0f*scale,-1.0f*scale,
        -0.1f*scale,0.0f*scale,1.0f*scale,
        -0.8f*scale,0.0f*scale,1.0f*scale,
        
        0.0f*scale, 0.0f*scale,-1.0f*scale,
        0.1f*scale,0.0f*scale,1.0f*scale,
        0.8f*scale,0.0f*scale,1.0f*scale,
        
        
    };
     GLfloat vertex_buffer_data2[] = {
        
        0.0f*scale, 0.0f*scale,-1.0f*scale,
        -0.1f*scale,0.0f*scale,1.0f*scale,
        0.0f*scale,1.0f*scale,1.1f*scale,
    };
    
    GLfloat vertex_buffer_data3[] = {
        
        0.0f*scale, 0.0f*scale,-1.0f*scale,
        0.1f*scale,0.0f*scale,1.0f*scale,
        0.0f*scale,-1.0f*scale,1.1f*scale,
    };

    int n = 1000;
    GLfloat vertex_buffer_data4[n*100];
    cylinder(vertex_buffer_data4,0,-0.7*scale,0,0.2f*scale,2.0f*scale,n,1000);

    for(int i = 0; i < 7*n; i++)
    {
        float x1 = vertex_buffer_data4[i*3];
        float y1 = vertex_buffer_data4[i*3+1];
        float z1 = vertex_buffer_data4[i*3+2];
        // float x2 = x1;
        // float y2 = -z1;
        // float z2 = y1;

        float x3 = x1;
        float y3 = -z1;
        float z3 = y1;
        vertex_buffer_data4[i*3] = x3;
        vertex_buffer_data4[i*3+1] = y3;
        vertex_buffer_data4[i*3+2] = z3;
    }

    GLfloat rec1[18];
    int k = 0;

    float rx = 1.2f*scale;
    float ry = 0.3f*scale;


    rec1[k++] = rx;
    rec1[k++] = ry;
    rec1[k++] = -0.5f*scale;

    rec1[k++] = rx;
    rec1[k++] = ry;
    rec1[k++] = 0.0f*scale;

    rec1[k++] = -rx;
    rec1[k++] = ry;
    rec1[k++] = -0.5f*scale;





    rec1[k++] = -rx;
    rec1[k++] = ry;
    rec1[k++] = -0.5f*scale;
 
    rec1[k++] = -rx;
    rec1[k++] = ry;
    rec1[k++] = 0.0f;

    rec1[k++] = rx;
    rec1[k++] = ry;
    rec1[k++] = 0.0f;


    GLfloat rec2[18];

    k = 0;
    ry = -ry;

    rec2[k++] = rx;
    rec2[k++] = ry;
    rec2[k++] = -0.5f*scale;

    rec2[k++] = rx;
    rec2[k++] = ry;
    rec2[k++] = 0.0f*scale;

    rec2[k++] = -rx;
    rec2[k++] = ry;
    rec2[k++] = -0.5f*scale;





    rec2[k++] = -rx;
    rec2[k++] = ry;
    rec2[k++] = -0.5f*scale;
 
    rec2[k++] = -rx;
    rec2[k++] = ry;
    rec2[k++] = 0.0f;

    rec2[k++] = rx;
    rec2[k++] = ry;
    rec2[k++] = 0.0f;


    GLfloat fan[18];

    rectangle(fan,0.22f,0.3f,-0.22f,-0.3f, -1.02f);



    this->object[0] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data1, COLOR_BROWN, GL_FILL);
    this->object[1] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data2, COLOR_DARK_BROWN, GL_FILL);
    // this->object[2] = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data3, COLOR_ddbrown, GL_FILL);
    this->object[3] = create3DObject(GL_TRIANGLES, n, vertex_buffer_data4, COLOR_BLUE, GL_FILL);

    n = 9*5*5;
    GLfloat barrel_data[n*3];
    sphere(barrel_data, 0.0f, 0.0f ,-0.8f*scale, 0.22f*scale, n);
    this->object[2] = create3DObject(GL_TRIANGLES, n, barrel_data, COLOR_BOAT, GL_FILL);
    this->object[4] = create3DObject(GL_TRIANGLES, 6, rec1, COLOR_FIRE,GL_FILL);
    this->object[5] = create3DObject(GL_TRIANGLES, 6, rec2, COLOR_FIRE,GL_FILL);
    this->object[6] = create3DObject(GL_TRIANGLES, 6, fan, COLOR_Yellow,GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    glm::mat4 rzrotate    = glm::rotate((float) (this->rzrotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    glm::mat4 rxrotate    = glm::rotate((float) (this->rxrotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    this->direction = glm::vec3(rotate * glm::vec4(0, 0, 1, 1.0f));
    Matrices.model *= (translate * rotate * rzrotate *rxrotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object[0]);
    draw3DObject(this->object[1]);
    draw3DObject(this->object[2]);
    draw3DObject(this->object[3]);
    draw3DObject(this->object[4]);
    draw3DObject(this->object[5]);
    draw3DObject(this->object[6]);    
}


void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, -0.01, y);
}

void Ball::tick(int t, float camera_rotation_angle) {
    float inc_forward = 0.3f;
    float temp;
    temp = cos((M_PI/180)*camera_rotation_angle);
    this->position.x-=inc_forward*temp;
    temp = sin((M_PI/180)*camera_rotation_angle);
    this->position.z-=inc_forward*temp;
     this->position.y -= speed_y*t*t;
}





void Ball::rotate(int dir)
{
    this->rzrotation += dir*5;
   
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y,z= this->position.z;
    bounding_box_t bbox = { x, y, z, 2, 2, 2 };
    return bbox;
}