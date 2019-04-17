#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define VIEWS 5
#define HELICOPTER_VIEW 0
#define FOLLOW_CAM_VIEW 1
#define TOP_VIEW 2
#define BOAT_VIEW 3
#define TOWER_VIEW 4

#define ROCKS 100
#define ISLANDS 3
#define SKULLS 4
#define BOSSES 1

#define HEALTH_B 3
#define POINTS_B 20
#define BOOST_B 5

struct color_t {
    int r;
    int g;
    int b;
};

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;
extern GLMatrices MatricesD;


// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float length;
    float width;
    float height;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
void scroll(int xoffset, int yoffset);
void jump();
void toggleBoard();
void changeView();
void attack();

void shoot_bomb();

void projectile();
void change_score();
void check_checkpt();
void check_vcol();
void check_rcol();

void draw_map(glm::mat4 VPD);

float RandomFloat(float min, float max);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();
void enemy_shooting();

void enemy_projectile();


void check_close();
extern int fall_down;

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;
extern const color_t COLOR_WATER;
extern const color_t COLOR_WHITE;
extern const color_t COLOR_BROWN;
extern const color_t COLOR_SKIN;
extern const color_t COLOR_DARK_BLUE;
extern const color_t COLOR_SHIRT;
extern const color_t COLOR_PLANE;
extern const color_t COLOR_GREY;
extern const color_t COLOR_ORANGE;
extern const color_t COLOR_YELLOW;
extern const color_t COLOR_PURPLE;
extern const color_t COLOR_DARK_BROWN;
extern const color_t COLOR_BOAT;
extern const color_t COLOR_DDRED;
extern const color_t COLOR_SILVER;
extern const color_t COLOR_DRED;
extern const color_t COLOR_Yellow;
extern const color_t COLOR_FIRE;
extern const color_t COLOR_DARK;
#endif
