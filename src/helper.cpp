#include <iostream>
using namespace std;

#include "helper.h"

void rectangle(GLfloat arr[], float x1, float x2, float y1, float y2, float z) {
    for (int j=0 ; j<18 ; ++j)
        arr[j] = z;

    arr[0]  = x1;
    arr[1]  = y1;
            
    arr[3]  = x2;
    arr[4]  = y1;

    arr[6]  = x2;
    arr[7]  = y2;

    arr[9]  = x1;
    arr[10] = y1;

    arr[12] = x2;
    arr[13] = y2;

    arr[15] = x1;
    arr[16] = y2;
}

void quad(GLfloat arr[], glm::vec3 c1, glm::vec3 c2, glm::vec3 c3, glm::vec3 c4) {
    GLfloat temp[] = {
        c1.x, c1.y, c1.z,
        c2.x, c2.y, c2.z,
        c3.x, c3.y, c3.z,

        c1.x, c1.y, c1.z,
        c2.x, c2.y, c2.z,
        c4.x, c4.y, c4.z,

        c2.x, c2.y, c2.z,
        c3.x, c3.y, c3.z,
        c4.x, c4.y, c4.z,

    };

    for (int i=0 ; i<27 ; ++i)
        arr[i] = temp[i];    
}

void triangle(GLfloat arr[], glm::vec3 c1, glm::vec3 c2, glm::vec3 c3) {
    GLfloat temp[] = {
        c1.x, c1.y, c1.z,
        c2.x, c2.y, c2.z,
        c3.x, c3.y, c3.z,
    };

    for (int i=0 ; i<9 ; ++i)
        arr[i] = temp[i];    
}

void cuboid(GLfloat arr[], float x1, float x2, float y1, float y2, float z1, float z2) {
    // if (x1 == )
    GLfloat temp[] = {
        x1, y1, z1,
        x1, y1, z2,
        x1, y2, z2,

        x1, y1, z1,
        x1, y2, z2,
        x1, y2, z1,

        x2, y1, z1,
        x2, y1, z2,
        x2, y2, z2,

        x2, y1, z1,
        x2, y2, z2,
        x2, y2, z1,

        x1, y1, z1,
        x2, y1, z1,
        x2, y2, z1,

        x1, y1, z1,
        x2, y2, z1,
        x1, y2, z1,

        x1, y1, z2,
        x2, y1, z2,
        x2, y2, z2,

        x1, y1, z2,
        x2, y2, z2,
        x1, y2, z2,


        x1, y1, z1,
        x1, y1, z2,
        x2, y1, z1,

        x2, y1, z1,
        x1, y1, z2,
        x2, y1, z2,

        x1, y2, z1,
        x1, y2, z2,
        x2, y2, z1,

        x2, y2, z1,
        x1, y2, z2,
        x2, y2, z2,

    };

    for (int i=0 ; i<36*3 ; ++i)
        arr[i] = temp[i];
}

void sphere(GLfloat arr[], float x, float y, float z, float r, int n) {
    int quads = n/9;
    int k = sqrt(quads);

    int curr = 0;
    for (int i=0 ; i<k ; ++i) {
        float zUp = -r + (2*r * (k-i)) / k;
        float zDown = -r + (2*r * (k-i-1)) / k;
        float thisR1 = sqrt(r*r - zUp*zUp);
        float thisR2 = sqrt(r*r - zDown*zDown);
        float deg = 360.0f / (float) k;
        for (int j=0 ; j<k ; ++j) {
            quad(arr + curr, V(x + (thisR1 * Cos(j*deg)), y + (thisR1 * Sin(j*deg)), z + zUp), 
                             V(x + (thisR1 * Cos((j+1)*deg)), y + (thisR1 * Sin((j+1)*deg)), z + zUp), 
                             V(x + (thisR2 * Cos(j*deg)), y + (thisR2 * Sin(j*deg)), z + zDown), 
                             V(x + (thisR2 * Cos((j+1)*deg)), y + (thisR2 * Sin((j+1)*deg)), z + zDown));
            curr += 27;
        }
    }
}


float Cos(float x) {
    return cos((x * M_PI) / 180.f);
}

float Sin(float x) {
    return sin((x * M_PI) / 180.f);
}

void pie(GLfloat arr[], float x, float y, float z, float r, int n, float offset, float deg) {
    deg /= (float)n;
    for (int i=0 ; i<n ; ++i) {
        arr[i*9 + 0] = x;
        arr[i*9 + 1] = y;
        arr[i*9 + 2] = z;

        arr[i*9 + 3] = x + r * Cos(offset + deg * i);
        arr[i*9 + 4] = y;
        arr[i*9 + 5] = z + r * Sin(offset + deg * i);

        arr[i*9 + 6] = x + r * Cos(offset + deg * (i+1));
        arr[i*9 + 7] = y;
        arr[i*9 + 8] = z + r * Sin(offset + deg * (i+1));
    }
}

int randomNum(int a, int b) {
    return a + rand() % (b - a + 1);
}

void printVec(glm::vec3 v) {
    cerr << v.x << ' ' << v.y << ' ' << v.z << endl;
}

void cylinder(GLfloat arr[], float x, float y, float z, float r, float h, int n, int cn) {
    int quads = n/9;
 
   float deg = 360.0/quads;
    int curr = 0;
    for (int i=0 ; i<quads ; ++i) {
        quad(arr + curr, V(x + r * Cos(deg*i), y, z + r * Sin(deg*i)), 
                         V(x + r * Cos(deg*(i+1)), y, z + r * Sin(deg*(i+1))), 
                         V(x + r * Cos(deg*i), y + h, z + r * Sin(deg*i)), 
                         V(x + r * Cos(deg*(i+1)), y + h, z + r * Sin(deg*(i+1))));
        curr += 27;
    }
    pie(arr + curr, x, y + h, z, r, cn, 0, 360); curr += (cn * 9);
    pie(arr + curr, x, y, z, r, cn, 0, 360); curr += (cn * 9);
}

void diamond(GLfloat arr[], float x, float y, float z, float sz) {
    // n == 16 * 9
    
    float x1 = x + sz * (-1.3f), x2 = x + sz * (-1.0f), x3 = x + sz * 0, x4 = x + sz * 1, x5 = x + sz * 1.3f;
    float y1 = y + sz * (-2.3f), y2 = y + sz * (-2), y3 = y + sz * (-1), y4 = y + sz * 1, y5 = y + sz * 2, y6 = y + sz * 2.3f;
    float z1 = z + sz * (-0.3f), z2 = z + sz * 0, z3 = z + sz * 0.3f;

    // Front
    int curr = 0;
    quad(arr + curr, V(x3, y5, z1), V(x2, y4, z1), V(x2, y3, z1), V(x3, y2, z1)); curr += 27;
    quad(arr + curr, V(x3, y5, z1), V(x4, y4, z1), V(x4, y3, z1), V(x3, y2, z1)); curr += 27;

    // Back
    quad(arr + curr, V(x3, y5, z3), V(x2, y4, z3), V(x2, y3, z3), V(x3, y2, z3)); curr += 27;
    quad(arr + curr, V(x3, y5, z3), V(x4, y4, z3), V(x4, y3, z3), V(x3, y2, z3)); curr += 27;

    // Top front
    quad(arr + curr, V(x3, y6, z2), V(x3, y5, z1), V(x2, y4, z1), V(x1, y4, z2)); curr += 27;
    quad(arr + curr, V(x3, y6, z2), V(x3, y5, z1), V(x4, y4, z1), V(x5, y4, z2)); curr += 27;

    // Bottom front
    quad(arr + curr, V(x3, y1, z2), V(x3, y2, z1), V(x2, y3, z1), V(x1, y3, z2)); curr += 27;
    quad(arr + curr, V(x3, y1, z2), V(x3, y2, z1), V(x4, y3, z1), V(x5, y3, z2)); curr += 27;

    // Middle front
    quad(arr + curr, V(x5, y3, z2), V(x4, y3, z1), V(x4, y4, z1), V(x5, y4, z2)); curr += 27;
    quad(arr + curr, V(x5, y3, z2), V(x4, y3, z1), V(x4, y4, z1), V(x5, y4, z2)); curr += 27;


    // Top back
    quad(arr + curr, V(x3, y6, z2), V(x3, y5, z3), V(x2, y4, z3), V(x1, y4, z2)); curr += 27;
    quad(arr + curr, V(x3, y6, z2), V(x3, y5, z3), V(x4, y4, z3), V(x5, y4, z2)); curr += 27;

    // Bottom back
    quad(arr + curr, V(x3, y1, z2), V(x3, y2, z3), V(x2, y3, z3), V(x1, y3, z2)); curr += 27;
    quad(arr + curr, V(x3, y1, z2), V(x3, y2, z3), V(x4, y3, z3), V(x5, y3, z2)); curr += 27;

    // Middle back
    quad(arr + curr, V(x5, y3, z2), V(x4, y3, z3), V(x4, y4, z3), V(x5, y4, z2)); curr += 27;
    quad(arr + curr, V(x5, y3, z2), V(x4, y3, z3), V(x4, y4, z3), V(x5, y4, z2)); curr += 27;
}

glm::vec3 getRandomLocation(glm::vec3 pos, float r, float R) {
    float range = R - r;
    float dist = r + ((rand() % (int)(range * 1000)) / 1000.0);
    // cerr << dist << endl;
    float angle = (rand() % 36000) / 100.0;

    glm::vec3 ret = pos;
    ret += V(dist * Sin(angle), 0, dist * Cos(angle));
    ret.y = 0;

    // assert(abs(length(pos - ret) - dist) < 0.1);
    // assert()

    return ret;
}

float Rand(float x, float y) {
    float range = y - x;
    return x + ((rand() % (int)(range * 1000)) / 1000.0);
}

bool detectCollision(glm::vec3 v1, float r1, glm::vec3 v2, float r2) {
    return length(v2 - v1) <= (r1 + r2);
}