#include "main.h"

#ifndef HELPER_H
#define HELPER_H

#define V(x, y, z) glm::vec3(x, y, z)

float Cos(float x);
float Sin(float x);
void rectangle(GLfloat arr[], float x1, float x2, float y1, float y2, float z);
void cuboid(GLfloat arr[], float x1, float x2, float y1, float y2, float z1, float z2);
void cylinder(GLfloat arr[], float x, float y, float z, float r, float h, int n, int cn);
void pie(GLfloat arr[], float x, float y, float z, float r, int n, float offset, float deg);
void sphere(GLfloat arr[], float x, float y, float z, float r, int n);
void quad(GLfloat arr[], glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4);
void traingle(GLfloat arr[], glm::vec3 c1, glm::vec3 c2, glm::vec3 c3);
int randomNum(int a, int b);
void printVec(glm::vec3 v);
void diamond(GLfloat arr[], float x, float y, float z, float sz);
glm::vec3 getRandomLocation(glm::vec3 pos, float r, float R);
float Rand(float x, float y);
bool detectCollision(glm::vec3 v1, float r1, glm::vec3 v2, float r2);


#endif // HELPER_H
