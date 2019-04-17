#include "dashboard.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Score::Score(float x, float y, int no, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[400];
    int k = 0;
    int notr = 0;

//1
    if(no == 0 || no == 2 || no == 3 || (no >=5  && no <=9))
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //2
    if(no != 7 && no >=2 && no <= 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.2f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //3
    if(no == 0 || no == 2 || no == 3 || no == 5 || no == 6 || no == 8 || no == 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f ;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.05f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.2f;
        vertex_buffer_data[k++] = 0.05f -0.4f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //4
    if(no == 0 || no == 4 || no == 5 || no == 6 || no == 8 || no == 9)
    {
        notr ++;        
        vertex_buffer_data[k++] = 0.0f ;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }

    //5
    if((no >=0 && no <= 4) || (no >=7 && no <= 9))
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //6
    if(no == 0 || no == 2 || no == 6 || no == 8 || no == 9)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }
    //7
    if(no != 2)
    {
        notr ++;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f  + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;

        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = 0.0f + 0.2f;
        vertex_buffer_data[k++] = -0.2f - 0.2f;
        vertex_buffer_data[k++] = 0.0f;
        vertex_buffer_data[k++] = -0.05f + 0.2f;
        vertex_buffer_data[k++] = 0.0f - 0.2f + 0.05f;
        vertex_buffer_data[k++] = 0.0f;
    }

    
    this->object = create3DObject(GL_TRIANGLES, notr*6, vertex_buffer_data, color, GL_FILL);
}

void Score::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Scoreboard::Scoreboard(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    int n = 100;
    float pi = 3.142;
    GLfloat vertex_buffer_data[40];
    int k = 0;

    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;

    vertex_buffer_data[k++] = -4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 4.5f;
    vertex_buffer_data[k++] = -1.0f;
    vertex_buffer_data[k++] = 4.0f;
    vertex_buffer_data[k++] = 3.5f;
    vertex_buffer_data[k++] = -1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Scoreboard::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}




Lifebar::Lifebar(float x, float y, color_t color, float score) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    GLfloat vertex_buffer_data[40];
    int k = 0;
    float add = score * 0.5f;

    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;

    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Lifebar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


Emptybar::Emptybar(float x, float y, color_t color, float score) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.005;
    GLfloat vertex_buffer_data[40];
    int k = 0;
    float add = score * 0.5f;

    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;

    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    vertex_buffer_data[k++] = -3.5f + 2.5f;
    vertex_buffer_data[k++] = 4.2f - 0.1f;
    vertex_buffer_data[k++] =1.0f;
    vertex_buffer_data[k++] = -3.5f + add;
    vertex_buffer_data[k++] = 3.8f - 0.1f;
    vertex_buffer_data[k++] = 1.0f;
    
    this->object = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data, color, GL_FILL);
}

void Emptybar::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.3f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 0.3f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}
