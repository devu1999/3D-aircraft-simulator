#include <string.h>
#include "main.h"
#include "timer.h"
#include "ball.h"
#include "water.h"
#include "helper.h"
#include "rock.h"
#include "health.h"
#include "points.h"
#include "treasure.h"
#include "goli.h"
#include "enemy.h"
#include "checkpoint.h"
#include "dashboard.h"
#include "bomb.h"
#include "volcano.h"
#include "map.h"
#include "boss.h"
#include "arrow.h"
#include "boss.h"
#include "ring.h"



using namespace std;

GLMatrices Matrices,MatricesD;
GLuint     programID,programID2;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball plane;
Water water;
Rock rock[ROCKS], island[ISLANDS];
Rock visland;
Volcano volcano;
Arrow arrow;
// Barrel barrel[BARRELS];
// Sound music;
// Wind wind;
Health health[HEALTH_B];
Points points[POINTS_B];
// Skull skull[SKULLS];
// Boss boss[BOSSES];
Treasure treasure[ISLANDS];
// Boost boost[BOOST_B];
Boss  Cenemy[3];

float cenemy_health[3];


Scoreboard sc;
vector<Score> s;
int ac_ck = 0;
int killedMonsters = 0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, near = 0.1f, far = 500.0f;
float camera_rotation_angle = 0;
int shoot_i = -1,shoot_b = -1;


float currHealth = 100;
float maxHealth = 100;
int score = 0;
int level = 1;



float temp;

int fall_down;
int gtype = 0;


// Camera vectors
float cameraDistance = 5.0f;
float xzAngle = -90.0f;
float yAngle = 40.0f;
glm::vec3 spotlight;
glm::vec3 eye;
glm::vec3 towerEye;
glm::vec3 target;
int fcnt = 0;
int currentView = 0;
glm::vec3 planeV[] = {
                        V(-0.4, 0.3, 0.2),
                        V(0, 0.3, 1),
                        V(-0.3, 0.3, -1),
                        V(0.3, 0.3, -1),
                        V(0.4, 0.3, 0.2)
                    };


Timer t60(1.0 / 60);
int timeLeft = 60 * 60 * 10;
Timer t6(1.0/6);
Timer t3(1.0/3);


#define total_enemies 100
#define total_shots 1000
#define score_kill_enemy 20
#define health_dec_enemy 30
#define total_checkpoints 3
#define total_bombs 1000

Enemy enemy[total_enemies];
Goli shoot[total_shots];
Checkpoint ckpt[total_checkpoints];
Bomb bomb[total_bombs];


Goli enemy_shoot[3][100];
int enemy_shooti[3];

float store_camera_angle = 0 ;
int count_enemy = 0;    // For Boss
#define out_boundary 1000


#define total_rings 100
Ring ring[total_rings];


//DASHBOARD VALUE  
#define fuel_value 10
#define fuel_loss 0.3 
float fuel = 100;
int speedup = 1;

int b_time = - 1000;
int count = 0;
float prev_ang;
float ini_plane_angle;
float pt_ang = 0;





/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    glm::vec3 pos(2.0f, 0, 2.0f);

    glm::vec3 spotDirection;
    float spotRotation;
    switch(currentView) {
        case HELICOPTER_VIEW:   eye = V(spotlight.x + cameraDistance * cos(xzAngle*M_PI/180.0f), spotlight.y + cameraDistance * sin(yAngle*M_PI/180.0f), spotlight.z + cameraDistance * sin(xzAngle*M_PI/180.0f));
                                target = V(spotlight.x -20 * cameraDistance * cos(xzAngle*M_PI/180.0f), spotlight.y + cameraDistance * 0, spotlight.z -20 * cameraDistance * sin(xzAngle*M_PI/180.0f));
                                break;
        case FOLLOW_CAM_VIEW:   spotRotation = ( plane.rotation);
                                eye = V(spotlight.x + cameraDistance * cos((-90 - spotRotation)*M_PI/180.0f), spotlight.y + cameraDistance * sin(yAngle*M_PI/180.0f), spotlight.z + cameraDistance * sin((-90 - spotRotation)*M_PI/180.0f));
                                target = V(spotlight.x -20 * cameraDistance * cos((-90 - spotRotation)*M_PI/180.0f), spotlight.y + cameraDistance * 0, spotlight.z -20 * cameraDistance * sin((-90 - spotRotation)*M_PI/180.0f));
                                break;
        case TOP_VIEW:          eye = V(spotlight.x, spotlight.y + 3 * cameraDistance, spotlight.z-0.0001f);
                                target = spotlight;
                                break;
        case BOAT_VIEW:         spotDirection = (plane.direction);
                                eye = spotlight + 2.5f * spotDirection;
                                target = spotlight + 10.0f * spotDirection;
                                eye.y = ( plane.position.y);
                                target.y = 0;
                                eye.y += 1;
                                break;
        case TOWER_VIEW:        eye = towerEye;
                                target = spotlight;
                                break;
    }

    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    plane.draw(VP);
    water.draw(VP);
    for (int i=0 ; i<ROCKS ; ++i)
        rock[i].draw(VP);
    for (int i=0 ; i<ISLANDS ; ++i) {
        island[i].draw(VP);
        treasure[i].draw(VP);
    }

    for (int i=0 ; i<HEALTH_B ; ++i)
        health[i].draw(VP);

    for (int i=0 ; i<POINTS_B ; ++i)
        points[i].draw(VP);


    for(int i=0;i<total_enemies;i++)    enemy[i].draw(VP);
    for (int i=0;i<total_shots;i++) shoot[i].draw(VP);

    for(int i = 0; i < total_bombs; i++) bomb[i].draw(VP);
    for(int i = 0; i < total_checkpoints; i++)
        ckpt[i].draw(VP);

    for(int i = 0; i < 3; i++)
    {
        if(cenemy_health[i] > 0)
        {    
            for(int j = 0; j < enemy_shooti[i]; j++)
            {
                if(enemy_shoot[i][j].hit == false)
                    enemy_shoot[i][j].draw(VP);
            }
        }
    }

    for(int i = 0 ; i < 3; i++)
    {
        if(cenemy_health[i] > 0)
        Cenemy[i].draw(VP);
    }

    for(int i = 0; i < total_rings; i++)
    {
        if(ring[i].taken == false)
            ring[i].draw(VP);
    }

    visland.draw(VP);
    volcano.draw(VP);
    arrow.draw(VP);

    glUseProgram (programID2);
     MatricesD.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane
    glm::mat4 VPD = MatricesD.projection * MatricesD.view;

    change_score();
    for(int i = 0; i < s.size();i++)
        s[i].draw(VPD);

    sc.draw(VPD);


    // health bar
    if(currHealth > 100)
        currHealth = 100;
    float hlevel = currHealth * 5/100;
    Lifebar lf;
    if(hlevel > 10/3)
        lf = Lifebar(0,-0.2, COLOR_GREEN,hlevel);
    else if(hlevel > 5/3)
        lf = Lifebar(0,-0.2, COLOR_Yellow,hlevel);
    else
        lf = Lifebar(0,-0.2, COLOR_RED,hlevel);
    lf.draw(VPD);
    Emptybar eb = Emptybar(0,-0.2,COLOR_WHITE,hlevel);
    eb.draw(VPD);


    //fuel bar
    if(fuel > 100)
        fuel = 100;
    hlevel = fuel * 5/100;
    if(hlevel > 10/3)
        lf = Lifebar(0,-1.2, COLOR_GREEN,hlevel);
    else if(hlevel > 5/3)
        lf = Lifebar(0,-1.2, COLOR_Yellow,hlevel);
    else
        lf = Lifebar(0,-1.2, COLOR_RED,hlevel);
    lf.draw(VPD);
    eb = Emptybar(0,-1.2,COLOR_WHITE,hlevel);
    eb.draw(VPD);

    draw_map(VPD);

    
}

void moveCamera(float xz, float y, float d, glm::vec3 pos) {
    xzAngle += xz;
    yAngle = max(min(yAngle + y, 90.0f), 5.0f);
    cameraDistance = min(10.0f, max(cameraDistance + d, 2.0f));
    // spotlight = pos;
}

void tick_mouse(GLFWwindow *window) {
    double currX, currY;
    glfwGetCursorPos(window, &currX, &currY);

    moveCamera(currX / 10.0f, currY / 10.0f, 0, V(0, 0, 0));

    glfwSetCursorPos(window, 0, 0);
}

void tick_input(GLFWwindow *window) {
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int a = glfwGetKey(window ,GLFW_KEY_A);
    int d = glfwGetKey(window ,GLFW_KEY_D);
    int f = glfwGetKey(window ,GLFW_KEY_F);
    int s = glfwGetKey(window ,GLFW_KEY_S);
    int inc_rotate = 2;
    float inc_forward = 0.3;

    if (left)
    {
        pt_ang += inc_rotate;
        plane.rotation += inc_rotate;
        xzAngle -= inc_rotate;
    }
    if (right)
    {
        pt_ang -= inc_rotate;
        plane.rotation -= inc_rotate;
        xzAngle += inc_rotate;
    }
    if (up)
    {
        temp = cos((M_PI/180)*xzAngle);
        plane.position.x-=speedup*inc_forward*temp;
        temp = sin((M_PI/180)*xzAngle);
        plane.position.z-=speedup*inc_forward*temp;
    }
    if(space)
    {
       temp = cos((M_PI/180)*yAngle);
       plane.position.y+=0.3; 
    }
    if(down)
    {
        plane.position.y -= 0.3;
    }
    if(a)
        plane.rotate(-1);
    if(d)
        plane.rotate(1);
    if(f)
        speedup ++;
    if(speedup > 5)
        speedup = 5;
    if(s)
        speedup --;
    if(speedup < 1)
        speedup = 1;
    int z = glfwGetKey(window ,GLFW_KEY_Z);
    int c = glfwGetKey(window ,GLFW_KEY_C);
    if(z)
        plane.rxrotation -= inc_rotate;
    if(c)
        plane.rxrotation += inc_rotate;
    int b = glfwGetKey(window ,GLFW_KEY_B);
    if(b)
    {
        prev_ang = plane.rzrotation;
        b_time = count;
    }
}

void updateScoreCard() {
    char title[1000];
    strcpy(title,"Speed:   ");

    
    int speed;
    if(fall_down == 1)
        speed = 0;
    else 
        speed = speedup*20;
    strcat(title, to_string(speed).c_str());

    glfwSetWindowTitle(window, title);
}



void checkCollisions() {

    for (int i=0 ; i<HEALTH_B ; ++i) {
            if (!health[i].taken and detectCollision(plane.position, 1, health[i].position + V(0, 4, 0), 1)) {
                health[i].taken = true;
                currHealth = 100;
            }
    }


    float x = plane.position.x;
    float y = plane.position.y;
    float z = plane.position.z;


    for(int i = 0; i < 3; i++)
    {
        for(int j= 0; j < enemy_shooti[i]; j++)
        {
            float x1 = enemy_shoot[i][j].position.x;
            float y1 = enemy_shoot[i][j].position.y;
            float z1 = enemy_shoot[i][j].position.z;
            float d = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1));
            if(d < 2 && enemy_shoot[i][j].hit == false && cenemy_health[i] > 0)
            {
                currHealth -= 10;
                enemy_shoot[i][j].hit = true;   
            }
        }
    }






    for (int i=0 ; i<POINTS_B ; ++i) {
            if (!points[i].taken and detectCollision(plane.position, 1, points[i].position + V(0, 4, 0), 1)) {
                // cerr << "Collided with points " << i << endl;
                points[i].taken = true;
                fuel += fuel_value;
            }
    }
    

}

void respawnElements() {
    if (!detectCollision(spotlight, 40, towerEye, 0)) {
        towerEye = getRandomLocation(spotlight, 0, 30);
        towerEye.y = Rand(10, 20);
    }

    for (int i=0 ; i<ROCKS ; ++i) {
        if (!detectCollision(spotlight, 300, rock[i].position, 0)) {
            rock[i].position = getRandomLocation(plane.position, 60, 200);
            rock[i].taken = false;
        }
    }
    for (int i=0 ; i<ISLANDS ; ++i) {
        if (!detectCollision(spotlight, 500, island[i].position, 0))
            island[i].position = getRandomLocation(plane.position, 150, 350);
    }
    for (int i=0 ; i<HEALTH_B ; ++i) {
        if (!detectCollision(spotlight, 150, health[i].position, 0)) {
            health[i].position = getRandomLocation(plane.position, 50, 100);
            health[i].taken = false;
        }
    }
    for (int i=0 ; i<POINTS_B ; ++i) {
        if (!detectCollision(spotlight, 150, points[i].position, 0)) {
            points[i].position = getRandomLocation(plane.position, 50, 100);
            points[i].taken = false;
        }
    }    
}

void tick_elements() {
   // wind.tick();

    for (int i=0 ; i<HEALTH_B ; ++i)
        health[i].tick();

    for (int i=0 ; i<POINTS_B ; ++i)
        points[i].tick();

    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < enemy_shooti[i]; j++)
        {
            enemy_shoot[i][j].tick();
        }
    }

    for(int i = 0; i < total_shots; i++)
    {
        for(int i = 0; i < 3; i++)
        {
            float x1 = Cenemy[i].position.x;
            float y1 = Cenemy[i].position.y;
            float z1 = Cenemy[i].position.z;
            float x = shoot[i].position.x;
            float z = shoot[i].position.z;
            float y = shoot[i].position.y;
            float d = sqrt((x-x1)*(x-x1) + (z-z1)*(z-z1));
            if(d < 5 && y < 10 && shoot[i].hit == false)
            {
                shoot[i].hit = false;
                cenemy_health[i] -= 30;
            }
        }
        shoot[i].tick();
    }

    for(int i = 0; i < total_bombs; i++)
    {
        for(int i = 0; i < 3; i++)
        {
            float x1 = Cenemy[i].position.x;
            float y1 = Cenemy[i].position.y;
            float z1 = Cenemy[i].position.z;
            float x = bomb[i].position.x;
            float z = bomb[i].position.z;
            float y = bomb[i].position.y;
            float d = sqrt((x-x1)*(x-x1) + (z-z1)*(z-z1));
            if(d < 3 && y < 7 && bomb[i].hit == false)
            {
                bomb[i].hit = true;
                cenemy_health[i] -= 20;
            }
        }
        bomb[i].tick();
    }

    for(int i=0;i<total_enemies;i++)
    {
        enemy[i].tick();
        // enemy killed

        float x1 = enemy[i].position.x;
        float y1 = enemy[i].position.y;
        float z1 = enemy[i].position.z;
        float x2 = shoot[shoot_i].position.x;
        float y2 = shoot[shoot_i].position.y;
        float z2 = shoot[shoot_i].position.z;
        // if(detect_collision(enemy[i].bounding_box(),shoot[shoot_i].bounding_box()))
        float dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
        if(dist <= 4 && shoot[shoot_i].hit == false)
        {
            shoot[shoot_i].hit = true;
            if(shoot_i >= 0 )
                score += score_kill_enemy;
    
            enemy[i].position.x = enemy[i].position.z = 2*out_boundary;
            count_enemy++;

        }

        x2 = bomb[shoot_b].position.x;
        y2 = bomb[shoot_b].position.y;
        z2 = bomb[shoot_b].position.z;

        // collision with bomb
        dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
        if(dist <= 4 && shoot[shoot_i].hit == false)
        {
            shoot[shoot_i].hit = true;
            if(shoot_b >= 0 )
                score += score_kill_enemy;
    
            enemy[i].position.x = enemy[i].position.z = 2*out_boundary;
            count_enemy++;

        }

        // plane collide with enemy
        x2 = plane.position.x;
        y2 = plane.position.y;
        z2 = plane.position.z;
        dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) + (z1-z2)*(z1-z2));
        if(dist <= 5)
        {
            enemy[i].position.x = enemy[i].position.z = 2*out_boundary;
            currHealth -= health_dec_enemy;
        }



        
    }
        check_checkpt();
        check_rcol();
        check_vcol();


    checkCollisions();
    respawnElements();

    spotlight.x = plane.position.x;
    spotlight.z = plane.position.z;
    water.setPosition(spotlight);
}

void createScene() {
    for (int i=0 ; i<ROCKS ; ++i)
        rock[i] = Rock(getRandomLocation(plane.position, 5, 200), 100, Rand(1, 1.5), 0.4, COLOR_BROWN);

    for (int i=0 ; i<ISLANDS ; ++i) {
        srand(time(0));
        island[i] = Rock(getRandomLocation(plane.position, 150, 350), 100, Rand(80, 130), 0.5, COLOR_GREEN);
        treasure[i] = Treasure(getRandomLocation(island[i].position, 0, island[i].r));
    }

    srand(time(0));
    visland = Rock(getRandomLocation(plane.position, 150, 350), 100, Rand(80, 130), 0.5, COLOR_GREEN);
    volcano = Volcano(visland.position.x,visland.position.z, COLOR_GREEN);

    for (int i=0 ; i<HEALTH_B ; ++i)
        health[i] = Health(getRandomLocation(plane.position, 20, 200));

    for (int i=0 ; i<POINTS_B ; ++i)
        points[i] = Points(getRandomLocation(plane.position, 10, 200));


    for(int i = 0; i < total_rings; i++)
    {
        srand(time(0));
        ring[i] = Ring((getRandomLocation(plane.position, 10, 200)));
        srand(time(0));
        ring[i].position.y = 10;
    }

}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    plane      = Ball(0, 5, COLOR_BLACK);
    water     = Water(0, 0, 200.0f, COLOR_WATER);
    // music     = Sound("assets/song.mp3", true);
    // wind      = Wind();

    towerEye = getRandomLocation(spotlight, 0, 30);
    towerEye.y = Rand(10, 20);


    ini_plane_angle = tanh(plane.position.x/plane.position.z);


    createScene();

    for (int i=0 ; i<5 ; ++i)
        planeV[i] *= 2.5;

    sc = Scoreboard(0,-0.2, COLOR_BLACK);

    s.push_back(Score(2,3.85,0,COLOR_WHITE));
    s.push_back(Score(1.7,3.85,0,COLOR_WHITE));
    s.push_back(Score(1.4,3.85,0,COLOR_WHITE));
    s.push_back(Score(1.1,3.85,0,COLOR_WHITE));
    s.push_back(Score(0.8,3.85,0,COLOR_WHITE));

    for(int i=0; i<total_shots;i++)
        shoot[i]     =   Goli(999,999,COLOR_RED);

    for(int i=0; i<total_bombs;i++)
        bomb[i]     =   Bomb(999,999,COLOR_RED);



    for(int i=0;i<total_enemies;i++)
    {
            enemy[i]    =     Enemy(getRandomLocation(plane.position, 20, 200),COLOR_RED,1);
    }


    
    ckpt[0] = Checkpoint(-500,0.2f,-500/sqrt(3),COLOR_DDRED);
    ckpt[1] = Checkpoint(500,0.2f,-500/sqrt(3),COLOR_DDRED);
    ckpt[2] = Checkpoint(0,0.2f,1000/sqrt(3),COLOR_DDRED);  
    

    for(int i = 0; i < 3; i++)
    {
        cenemy_health[i] = 100;
        Cenemy[i] = Boss(glm::vec3(ckpt[i].position.x,ckpt[i].position.y + 1.0f,ckpt[i].position.z ));
    }

    arrow = Arrow(-500,0.2f,-500/sqrt(3),COLOR_DDRED);
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    programID2 = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    MatricesD.MatrixID = glGetUniformLocation(programID2, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    // int width  = 600;
    // int height = 600;

    int width  = 1366;
    int height = 768;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        check_close();

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            count++;
            
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
            if(count - b_time < 30)
            {
                plane.rzrotation += 12;
            }
            updateScoreCard();
        }
        if(t6.processTick()){
            enemy_shooting();
        }
        if(t3.processTick())
        {
            if(speedup < 1)
                speedup = 1;
            fuel -= speedup*fuel_loss;
            score += 10;

        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.length + b.length)) &&
           (abs(a.y - b.y) * 2 < (a.width + b.width)) &&
           (abs(a.z - b.z) * 2 < (a.height + b.height));
}

void reset_screen() {
    // float aspect_ratio = 1;
    float aspect_ratio = 16.0f/9.0f;
    // cout << near << endl;
    Matrices.projection = glm::perspective(glm::radians(far), aspect_ratio, near, far);
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    MatricesD.projection = glm::ortho(left, right, bottom, top, 0.1f, 50.0f);
}

void scroll(int xoffset, int yoffset) {
    if (yoffset == 1)
        moveCamera(0, 0, -0.1f, glm::vec3(0, 0, 0));
    else if (yoffset == -1)
        moveCamera(0, 0, 0.1f, glm::vec3(0, 0, 0));

    reset_screen();
}



void changeView() {
    currentView = (currentView + 1) % VIEWS;
}



void attack(){
    if(shoot[shoot_i + 1].position.y<=0)
    {
        shoot[shoot_i + 1].position.x = plane.position.x;
        shoot[shoot_i + 1].position.y = plane.position.y;
        shoot[shoot_i + 1].position.z = plane.position.z;
        shoot[shoot_i + 1].rotation = plane.rotation - 90;
        projectile();
        shoot_i++;
    }
}

void shoot_bomb()
{
    if(bomb[shoot_b + 1].position.y<=0)
    {
        bomb[shoot_b + 1].position.x = plane.position.x;
        bomb[shoot_b + 1].position.y = plane.position.y;
        bomb[shoot_b + 1].position.z = plane.position.z;
        bomb[shoot_b + 1].rotation = plane.rotation - 90;
        shoot_b++;  
    } 
}


void enemy_shooting()
{
    for(int i = 0; i < 3; i++)
    {
        if(gtype == 0)
            enemy_shoot[i][enemy_shooti[i]] = Goli(Cenemy[i].position.x + 4, Cenemy[i].position.z + 4, COLOR_WHITE);
        else if(gtype == 1)
            enemy_shoot[i][enemy_shooti[i]] = Goli(Cenemy[i].position.x + 4, Cenemy[i].position.z - 4, COLOR_WHITE);
        else if(gtype == 2)
            enemy_shoot[i][enemy_shooti[i]] = Goli(Cenemy[i].position.x - 4, Cenemy[i].position.z + 4, COLOR_WHITE);
        else
            enemy_shoot[i][enemy_shooti[i]] = Goli(Cenemy[i].position.x - 4, Cenemy[i].position.z - 4, COLOR_WHITE);
        enemy_shoot[i][enemy_shooti[i]].rotation = -((gtype+1)%2)*60 - 60;
        enemy_projectile();
        enemy_shooti[i] =  (enemy_shooti[i] + 1)%100;
        gtype = (gtype + 1)%4;
    }       
}

void projectile(){
    store_camera_angle = xzAngle;
    temp = cos((M_PI/180)*store_camera_angle);
    float range = 0.5;    
    shoot[shoot_i + 1].speed_x = -range*temp;
    shoot[shoot_i + 1].acc_y = -range/10;
    shoot[shoot_i + 1].speed_y = 0.5;
    temp = sin((M_PI/180)*store_camera_angle);
    shoot[shoot_i + 1].speed_z = -range*temp;
}


void enemy_projectile(){
    store_camera_angle = xzAngle;
    temp = cos((M_PI/180)*store_camera_angle);
    float range = 0.35;
    int d1,d2;
    if(gtype == 0)
    {
        d1 = d2 = 1;    
    }
    else if(gtype == 1)
    {
        d1 = d2 = -1;
    }
    else if(gtype == 2)
    {
        d1 =1 ;
        d2 = -1;
    }
    else
    {
        d1 = -1;
        d2 = 1;
    }
    for(int i = 0; i < 3; i++)
    { 
        enemy_shoot[i][enemy_shooti[i] - 1].speed_x = -d1*range*temp;
        enemy_shoot[i][enemy_shooti[i] - 1].acc_y = -range/10;
        enemy_shoot[i][enemy_shooti[i] - 1].speed_y = 0.5;
        temp = sin((M_PI/180)*store_camera_angle);
        enemy_shoot[i][enemy_shooti[i] - 1].speed_z = -d2*range*temp;
    }
}

void check_checkpt()
{
    float x = plane.position.x;
    float y = plane.position.z;
    if(ckpt[ac_ck].achieved == false)
    {
        float x1 = ckpt[ac_ck].position.x;
        float y1 = ckpt[ac_ck].position.z;
        float r = 5;
        float f = (x-x1)*(x-x1)+(y-y1)*(y-y1) -r*r;
        if(f < 0 && cenemy_health[ac_ck] <= 0)
        {
            score += 500;
            level ++;
            currHealth += 100;
            ckpt[ac_ck].achieved = true;
            ac_ck ++;
            arrow.set_position(ckpt[ac_ck].position.x,ckpt[ac_ck].position.z);
        }
    }
    if(ac_ck >= 3)
        quit(window);
}

void check_vcol()
{
    float y = plane.position.y;
    if(y > 40.0f)
        return; 
    float x = volcano.position.x;
    float z = volcano.position.z;
    float x1 = plane.position.x;
    float z1 = plane.position.z;
    float r = 10 + (40 - y);
    float dist = sqrt((x - x1)*(x - x1) + (z - z1)*(z - z1));
    if(dist < r)
        quit(window);

}


void change_score(){
    s.clear();
    int no = score;
    int absicca = 2;
    
    s.push_back(Score(2,3.85,no%10,COLOR_WHITE));
    no = no/10;
    s.push_back(Score(1.7,3.85,no%10,COLOR_WHITE));
    no = no/10;
    s.push_back(Score(1.4,3.85,no%10,COLOR_WHITE));
    no = no/10;
    s.push_back(Score(1.1,3.85,no%10,COLOR_WHITE));
    no = no/10;
    s.push_back(Score(0.8,3.85,no%10,COLOR_WHITE));
    no = no/10;
}


float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

void draw_map(glm::mat4 VPD)
{
    float scale = 1/100;
    float r = 1.0f;
    Map oc1 = Map(3,2.2,0,r,COLOR_WATER);
    r = 1.05f;
    Map oc2 = Map(3,2.2,-0.1f,r,COLOR_WHITE);

    Map cp[3];
    Map VOLC;
    float max_d = -1;
    float x1 = plane.position.x;
    float y1 = plane.position.y;
    float z1 = plane.position.z;
    for(int i = 0; i < 3; i++ )
    {
        float x = ckpt[i].position.x;
        float y = ckpt[i].position.y;
        float z = ckpt[i].position.z;
        float d = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1));
        if(d > max_d)
            max_d = d;
    }
    float x = volcano.position.x;
    float y = volcano.position.y;
    float z = volcano.position.z;
    float d = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1));
    if(d > max_d)
        max_d = d;

    scale = 1/(2*max_d);

    VOLC = Map(3 + x*scale , 2.2 + z*scale ,0.1f,0.05f, COLOR_FIRE);

    for(int i = 0; i < 3; i++)
    {
        x = ckpt[i].position.x;
        y = ckpt[i].position.y;
        z = ckpt[i].position.z;
        if(cenemy_health[i] > 0)
            cp[i] = Map(3 + x*scale , 2.2 + z*scale ,0.1f,0.05f, COLOR_DDRED );
        else
            cp[i] = Map(3 + x*scale , 2.2 + z*scale ,0.1f,0.05f, COLOR_DARK );
        cp[i].draw(VPD,0);
    }
    x = plane.position.x;
    z = plane.position.z;
    Map P = Map(3 + x*scale,2.2 + z *scale,0.12f,0.05f,COLOR_BLACK);
    // Movedir mv = Movedir(3 + x*scale,2.2 + z *scale,0.115f,0.07f,COLOR_PLANE);
    // float new_ang = tanh(plane.position.x/plane.position.z);
    // mv.rotation = 360 - pt_ang;
    // mv.rx = plane.rotation;

    //pointer 
    x = ckpt[ac_ck].position.x;
    y = ckpt[ac_ck].position.y;
    z = ckpt[ac_ck].position.z;
    Map Pt = Map(3 + x*scale,2.2 + z *scale,0.11f,0.02f,COLOR_Yellow);
    Pt.draw(VPD,0);
    
    P.draw(VPD,0);
    // mv.draw(VPD);
    VOLC.draw(VPD,0);
    oc1.draw(VPD,0);
    oc2.draw(VPD,0);
}

void check_rcol()
{
    float x1 = plane.position.x;
    float y1 = plane.position.y;
    float z1 = plane.position.z;
    for(int i = 0; i < total_rings; i++)
    {
        float x = ring[i].position.x;
        float y = ring[i].position.y;
        float z = ring[i].position.z;
        if(abs(z-z1) < 0.2f)
        {
            float dist = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1) + (z-z1)*(z-z1));
            if(dist < 4.5f)
            {
                ring[i].taken = true;
                score += 100;
            }
        }
    }
}

void check_close()
{
    if(fuel <=0 || currHealth <= 0)
        quit(window);
}
