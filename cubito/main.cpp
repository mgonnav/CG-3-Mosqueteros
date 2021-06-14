//      ID CUBE RUBICK
//
//           03 06 09
//           02 05 08
//           01 04 07
//  03 02 01 01 04 07 07 08 09 09 06 03
//  12 11 10 10 13 16 16 17 18 18 15 12
//  21 20 19 19 22 25 25 26 27 27 24 21
//           19 22 25
//           20 23 26
//           21 24 27


//      INPUT COLOR
//
//           00 01 02
//           03 04 05
//           06 07 08
//  09 10 11 12 13 14 15 16 17 18 19 20
//  21 22 23 24 25 26 27 28 29 30 31 32
//  33 34 35 36 37 38 39 40 41 42 43 44
//           45 46 47
//           48 49 50
//           51 52 53

// INSTRUCTION
//                            UP
// USE MOUSE AND ARROWS LEFT DOWN RIGHT

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <irrklang/irrKlang.h>

#include "stb_image.h"
#include "Shader.h"
#include "Cubito.hpp"
#include "Cubo.hpp"
#include "Camera.hpp"
#include "solver/Rubik.hpp"

#include <iostream>
#include <vector>
#include <vector>
#include <algorithm>
#include <memory>

// THIS VARIABLES ARE COMPOSED LIKE THIS EXAMPLES
// MOVEMENT VERTICAL | COLUMN LEFT | DIRECTION UP => VL_U
// MOVEMENT HORIZONTAL | ROW MID | DIRECTION LEFT => HM_L
const int VL_U = 1;
const int VL_D = 2;
const int VM_U = 3;
const int VM_D = 4;
const int VR_U = 5;
const int VR_D = 6;
const int HU_L = 7;
const int HU_R = 8;
const int HM_L = 9;
const int HM_R = 10;
const int HD_L = 11;
const int HD_R = 12;

bool BCL_U = false, BCL_U_I = false;
bool BCL_D = false, BCL_D_I = false;
bool BCM_U = false, BCM_U_I = false;
bool BCM_D = false, BCM_D_I = false;
bool BCR_U = false, BCR_U_I = false;
bool BCR_D = false, BCR_D_I = false;

bool BRF_L = false, BRF_L_I = false;
bool BRF_R = false, BRF_R_I = false;
bool BRM_L = false, BRM_L_I = false;
bool BRM_R = false, BRM_R_I = false;
bool BRT_L = false, BRT_L_I = false;
bool BRT_R = false, BRT_R_I = false;

bool BF_R = false, BF_R_I = false;
bool BF_L = false, BF_L_I = false;
bool BM_R = false, BM_R_I = false;
bool BM_L = false, BM_L_I = false;
bool BB_R = false, BB_R_I = false;
bool BB_L = false, BB_L_I = false;

const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 ORANGE = glm::vec3(1.0f, 0.5f, 0.0f);
const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);

const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

const double PI = 3.14159;
float deg(float num) {
  return (num * PI / 180);
}

float scale_figure = 1.0f;
float deltaTime = 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

Cubo rubick_cube;

unsigned int VBO, VAO, EBO;

// MOUSE AND CAMERA
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 500.0f;
float lastY = 500.0f;
bool first_time_mouse = true;


const int kAroundXLeft = 1;
const int kAroundXRight = -1;
const int kAroundYLeft = 2;
const int kAroundYRight = -2;
const int kAroundZLeft = 3;
const int kAroundZRight = -3;

//======================================================== VARIABLES FOR MOVEMENTS

bool some_movement = false;
const float kRadioLarge = 0.5f * sqrt(2);
const float kRadioNormal = 0.5f;

//=============================== FRONT MID BACK

// BF_R

float angle_1 = 134.0f;
float angle_4 = 89.0f;
float angle_7 = 44.0f;
float angle_16 = -1.0f;
float angle_25 = 314.0f;
float angle_22 = 269.0f;
float angle_19 = 224.0f;
float angle_10 = 179.0f;

// BF_L

float angle_1_ = 136.0f;
float angle_4_ = 91.0f;
float angle_7_ = 46.0f;
float angle_16_ = 1.0f;
float angle_25_ = 316.0f;
float angle_22_ = 271.0f;
float angle_19_ = 226.0f;
float angle_10_ = 181.0f;

// BM_R

float angle_2 = 134.0f;
float angle_5 = 89.0f;
float angle_8 = 44.0f;
float angle_17 = -1.0f;
float angle_26 = 314.0f;
float angle_23 = 269.0f;
float angle_20 = 224.0f;
float angle_11 = 179.0f;

// BM_L

float angle_2_ = 136.0f;
float angle_5_ = 91.0f;
float angle_8_ = 46.0f;
float angle_17_ = 1.0f;
float angle_26_ = 316.0f;
float angle_23_ = 271.0f;
float angle_20_ = 226.0f;
float angle_11_ = 181.0f;

// BB_R

float angle_3 = 134.0f;
float angle_6 = 89.0f;
float angle_9 = 44.0f;
float angle_18 = -1.0f;
float angle_27 = 314.0f;
float angle_24 = 269.0f;
float angle_21 = 224.0f;
float angle_12 = 179.0f;

// BB_L

float angle_3_ = 136.0f;
float angle_6_ = 91.0f;
float angle_9_ = 46.0f;
float angle_18_ = 1.0f;
float angle_27_ = 316.0f;
float angle_24_ = 271.0f;
float angle_21_ = 226.0f;
float angle_12_ = 181.0f;

//=============================== COLUMN LEFT MID RIGHT

// BCL_R

float cl_angle_3 = 134.0f;
float cl_angle_2 = 89.0f;
float cl_angle_1 = 44.0f;
float cl_angle_12 = 179.0f;
float cl_angle_10 = 359.0f;
float cl_angle_21 = 224.0f;
float cl_angle_20 = 269.0f;
float cl_angle_19 = 314.0f;

// BCL_L

float cl_angle_3_ = 136.0f;
float cl_angle_2_ = 91.0f;
float cl_angle_1_ = 46.0f;
float cl_angle_12_ = 181.0f;
float cl_angle_10_ = 1.0f;
float cl_angle_21_ = 226.0f;
float cl_angle_20_ = 271.0f;
float cl_angle_19_ = 316.0f;

// PRINT COMMANDS

void Print() {
  std::cout << "\t\tWELCOME TO CUBITO MOSQUETERO" << std::endl;
  std::cout << "\t\t     CONTROLS TO PLAY" << std::endl << std::endl;
  std::cout << "\tQ | FIRST ROW TURN LEFT" << std::endl;
  std::cout << "\tW | FIRST ROW TURN RIGHT" << std::endl;
  std::cout << "\tA | MID ROW TURN LEFT" << std::endl;
  std::cout << "\tS | MID ROW TURN RIGHT" << std::endl;
  std::cout << "\tZ | THIRD ROW TURN LEFT" << std::endl;
  std::cout << "\tX | THIRD ROW TURN RIGHT\n" << std::endl;

  std::cout << "\tU | LEFT COLUMN TURN UP" << std::endl;
  std::cout << "\tJ | LEFT COLUMN TURN DOWN" << std::endl;
  std::cout << "\tI | MID COLUMN TURN UP" << std::endl;
  std::cout << "\tK | MID COLUMN TURN DOWN" << std::endl;
  std::cout << "\tO | RIGHT COLUMN TURN UP" << std::endl;
  std::cout << "\tL | RIGHT COLUMN TURN DOWN\n" << std::endl;

  std::cout << "\tV | FRONT GROUP TURN LEFT" << std::endl;
  std::cout << "\tB | FRONT GROUP TURN RIGHT" << std::endl;
  std::cout << "\tF | MID GROUP TURN LEFT" << std::endl;
  std::cout << "\tG | MID GROUP TURN RIGHT" << std::endl;
  std::cout << "\tR | BACK GROUP TURN LEFT" << std::endl;
  std::cout << "\tT | BACK GROUP TURN RIGHT\n" << std::endl;

}

int main() {
  // ----- Test solver --- //

  //std::string solution = rubik::solve("R' F U' D2 R F R' L2 F' B2 U' F2 B' R2 B D2 B' U2 R2");
  //std::cout << "Solution: " << solution << std::endl;

  // ----- Test solver --- //

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Coordinate Sistem", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glEnable(GL_DEPTH_TEST);

  Shader cubito_program("src/shaders/cubito.vs", "src/shaders/cubito.fs");

  //glfwSetKeyCallback(window, key_callback);
  glfwSetScrollCallback(window, scroll_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  // RANDOM COLOR TO INIT RUBICK CUBE
  std::vector<glm::vec3> input_colors;
  fill_n(back_inserter(input_colors), 9, BLUE);

  for (int i = 0; i < 3; ++i) {
    fill_n(back_inserter(input_colors), 3, ORANGE);
    fill_n(back_inserter(input_colors), 3, WHITE);
    fill_n(back_inserter(input_colors), 3, RED);
    fill_n(back_inserter(input_colors), 3, YELLOW);
  }

  fill_n(back_inserter(input_colors), 9, GREEN);
  // std::random_shuffle(input_colors.begin(), input_colors.end());

  // USER INPUT
  /*char c;
    for (int i = 0; i < 54; i++) {
    std::cin >> c;
    switch (c) {
    case 'r': {input_colors[i] == RED; break; }
    case 'g': {input_colors[i] == GREEN; break; }
    case 'b': {input_colors[i] == BLUE; break; }
    case 'y': {input_colors[i] == YELLOW; break; }
    case 'w': {input_colors[i] == WHITE; break; }
    case 'o': {input_colors[i] == ORANGE; break; }
    default: {std::cout << "WRONG INPUT" << std::endl; break;}
    }
    }
  */
  // MAIN AND EACH CUBE
  {
    rubick_cube.cubitos[3] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, -0.5f), 3, input_colors[20], input_colors[9],
      input_colors[0]);
    rubick_cube.cubitos[6] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, -0.5f), 6, input_colors[19], input_colors[1]);
    rubick_cube.cubitos[9] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, -0.5f), 9, input_colors[18], input_colors[17],
      input_colors[2]);
    rubick_cube.cubitos[12] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, -0.5f), 12, input_colors[32], input_colors[21]);
    rubick_cube.cubitos[15] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, -0.5f), 15, input_colors[31]);
    rubick_cube.cubitos[18] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, -0.5f), 18, input_colors[30], input_colors[29]);
    rubick_cube.cubitos[21] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, -0.5f), 21, input_colors[44], input_colors[33],
      input_colors[51]);
    rubick_cube.cubitos[24] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, -0.5f), 24, input_colors[43], input_colors[52]);
    rubick_cube.cubitos[27] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, -0.5f), 27, input_colors[42], input_colors[41],
      input_colors[53]);

    rubick_cube.cubitos[2] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, 0.0f), 2, input_colors[10], input_colors[3]);
    rubick_cube.cubitos[5] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, 0.0f), 5, input_colors[4]);
    rubick_cube.cubitos[8] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, 0.0f), 8, input_colors[16], input_colors[5]);
    rubick_cube.cubitos[11] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, 0.0f), 11, input_colors[22]);
    rubick_cube.cubitos[14] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, 0.0f), 14);
    rubick_cube.cubitos[17] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, 0.0f), 17, input_colors[28]);
    rubick_cube.cubitos[20] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, 0.0f), 20, input_colors[34], input_colors[48]);
    rubick_cube.cubitos[23] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, 0.0f), 23, input_colors[49]);
    rubick_cube.cubitos[26] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, 0.0f), 26, input_colors[40], input_colors[50]);

    rubick_cube.cubitos[1] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, 0.5f), 1, input_colors[12], input_colors[11],
      input_colors[6]);
    rubick_cube.cubitos[4] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, 0.5f), 4, input_colors[13], input_colors[7]);
    rubick_cube.cubitos[7] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, 0.5f), 7, input_colors[14], input_colors[15],
      input_colors[8]);
    rubick_cube.cubitos[10] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, 0.5f), 10, input_colors[24], input_colors[23]);
    rubick_cube.cubitos[13] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, 0.5f), 13, input_colors[25]);
    rubick_cube.cubitos[16] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, 0.5f), 16, input_colors[26], input_colors[27]);
    rubick_cube.cubitos[19] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, 0.5f), 19, input_colors[36], input_colors[35],
      input_colors[45]);
    rubick_cube.cubitos[22] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, 0.5f), 22, input_colors[37], input_colors[46]);
    rubick_cube.cubitos[25] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, 0.5f), 25, input_colors[38], input_colors[39],
      input_colors[47]);
  }
  
  Print();

  int a = 1;
  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    projection = glm::perspective(glm::radians(camera.Zoom),
                                  (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    view = camera.GetViewMatrix();

    if (some_movement) {
      
      // MOVEMENTS OF FRONT MID BACK

      // ONE TURN BF_R | BOOL FRONT RIGHT
      if (BF_R) {
        if (BF_R_I) {
          // CUBO 01
          if (angle_1 > 45.0f) angle_1 -= 1.0f;
          else angle_1 = 45.0f;
          rubick_cube.cubitos[1]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_1)), kRadioLarge * sin(deg(angle_1)), 0.5f));
          
          rubick_cube.cubitos[1]->Rotate(kAroundZRight);

          // CUBO 04
          if (angle_4 > 0.0f) angle_4 -= 1.0f;
          else angle_4 = 0.0f;
          rubick_cube.cubitos[4]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_4)), kRadioNormal * sin(deg(angle_4)), 0.5f));

          rubick_cube.cubitos[4]->Rotate(kAroundZRight);

          // CUBO 07
          if (angle_7 > -45.0f) angle_7 -= 1.0f;
          else angle_7 = -45.0f;
          rubick_cube.cubitos[7]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_7)), kRadioLarge * sin(deg(angle_7)), 0.5f));

          rubick_cube.cubitos[7]->Rotate(kAroundZRight);

          // CUBO 16
          if (angle_16 > -90.0f) angle_16 -= 1.0f;
          else angle_16 = -90.0f;
          rubick_cube.cubitos[16]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_16)), kRadioNormal * sin(deg(angle_16)), 0.5f));

          rubick_cube.cubitos[16]->Rotate(kAroundZRight);

          // CUBO 25
          if (angle_25 > 225.0f) angle_25 -= 1.0f;
          else angle_25 = 225.0f;
          rubick_cube.cubitos[25]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_25)), kRadioLarge * sin(deg(angle_25)), 0.5f));

          rubick_cube.cubitos[25]->Rotate(kAroundZRight);

          // CUBO 22
          if (angle_22 > 180.0f) angle_22 -= 1.0f;
          else angle_22 = 180.0f;
          rubick_cube.cubitos[22]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_22)), kRadioNormal * sin(deg(angle_22)), 0.5f));

          rubick_cube.cubitos[22]->Rotate(kAroundZRight);

          // CUBO 19
          if (angle_19 > 135.0f) angle_19 -= 1.0f;
          else angle_19 = 135.0f;
          rubick_cube.cubitos[19]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_19)), kRadioLarge * sin(deg(angle_19)), 0.5f));

          rubick_cube.cubitos[19]->Rotate(kAroundZRight);

          // CUBO 10
          if (angle_10 > 90.0f) angle_10 -= 1.0f;
          else { angle_10 = 90.0f; BF_R_I = false; }
          rubick_cube.cubitos[10]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_10)), kRadioNormal * sin(deg(angle_10)), 0.5f));

          rubick_cube.cubitos[10]->Rotate(kAroundZRight);

          // CUBO 13
          rubick_cube.cubitos[13]->Rotate(kAroundZRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_1 = rubick_cube.cubitos[1];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          std::shared_ptr<Cubito> new_10 = rubick_cube.cubitos[10];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          std::shared_ptr<Cubito> new_19 = rubick_cube.cubitos[19];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[1] = new_19;
          rubick_cube.cubitos[4] = new_10;
          rubick_cube.cubitos[7] = new_1;
          rubick_cube.cubitos[16] = new_4;
          rubick_cube.cubitos[25] = new_7;
          rubick_cube.cubitos[10] = new_22;
          rubick_cube.cubitos[19] = new_25;
          rubick_cube.cubitos[22] = new_16;

          angle_1 = 134.0f;
          angle_4 = 89.0f;
          angle_7 = 44.0f;
          angle_16 = -1.0f;
          angle_25 = 314.0f;
          angle_22 = 269.0f;
          angle_19 = 224.0f;
          angle_10 = 179.0f;

          BF_R = false;
        }
      }
      // ONE TURN BF_L | BOOL FRONT LEFT
      if (BF_L) {
        if (BF_L_I) {
          // CUBO 01
          if (angle_1_ < 225.0f) angle_1_ += 1.0f;
          else angle_1_ = 225.0f;
          rubick_cube.cubitos[1]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_1_)), kRadioLarge * sin(deg(angle_1_)), 0.5f));

          rubick_cube.cubitos[1]->Rotate(kAroundZLeft);

          // CUBO 04
          if (angle_4_ < 180.0f) angle_4_ += 1.0f;
          else angle_4_ = 180.0f;
          rubick_cube.cubitos[4]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_4_)), kRadioNormal * sin(deg(angle_4_)), 0.5f));

          rubick_cube.cubitos[4]->Rotate(kAroundZLeft);

          // CUBO 07
          if (angle_7_ < 135.0f) angle_7_ += 1.0f;
          else angle_7_ = 135.0f;
          rubick_cube.cubitos[7]->Translate(glm::vec3(kRadioLarge* cos(deg(angle_7_)), kRadioLarge* sin(deg(angle_7_)), 0.5f));

          rubick_cube.cubitos[7]->Rotate(kAroundZLeft);

          // CUBO 16
          if (angle_16_ < 90.0f) angle_16_ += 1.0f;
          else angle_16_ = 90.0f;
          rubick_cube.cubitos[16]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_16_)), kRadioNormal * sin(deg(angle_16_)), 0.5f));

          rubick_cube.cubitos[16]->Rotate(kAroundZLeft);

          // CUBO 25
          if (angle_25_ < 405.0f) angle_25_ += 1.0f;
          else angle_25_ = 405.0f;
          rubick_cube.cubitos[25]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_25_)), kRadioLarge * sin(deg(angle_25_)), 0.5f));

          rubick_cube.cubitos[25]->Rotate(kAroundZLeft);

          // CUBO 22
          if (angle_22_ < 360.0f) angle_22_ += 1.0f;
          else angle_22_ = 360.0f;
          rubick_cube.cubitos[22]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_22_)), kRadioNormal * sin(deg(angle_22_)), 0.5f));

          rubick_cube.cubitos[22]->Rotate(kAroundZLeft);

          // CUBO 19
          if (angle_19_ < 315.0f) angle_19_ += 1.0f;
          else angle_19_ = 315.0f;
          rubick_cube.cubitos[19]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_19_)), kRadioLarge * sin(deg(angle_19_)), 0.5f));

          rubick_cube.cubitos[19]->Rotate(kAroundZLeft);

          // CUBO 10
          if (angle_10_ < 270.0f) angle_10_ += 1.0f;
          else { angle_10_ = 270.0f; BF_L_I = false; }
          rubick_cube.cubitos[10]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_10_)), kRadioNormal * sin(deg(angle_10_)), 0.5f));

          rubick_cube.cubitos[10]->Rotate(kAroundZLeft);

          // CUBO 13
          rubick_cube.cubitos[13]->Rotate(kAroundZLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_1 = rubick_cube.cubitos[1];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          std::shared_ptr<Cubito> new_10 = rubick_cube.cubitos[10];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          std::shared_ptr<Cubito> new_19 = rubick_cube.cubitos[19];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[1] = new_7;
          rubick_cube.cubitos[4] = new_16;
          rubick_cube.cubitos[7] = new_25;
          rubick_cube.cubitos[16] = new_22;
          rubick_cube.cubitos[25] = new_19;
          rubick_cube.cubitos[10] = new_4;
          rubick_cube.cubitos[19] = new_1;
          rubick_cube.cubitos[22] = new_10;


          angle_1_ = 136.0f;
          angle_4_ = 91.0f;
          angle_7_ = 46.0f;
          angle_16_ = 1.0f;
          angle_25_ = 316.0f;
          angle_22_ = 271.0f;
          angle_19_ = 226.0f;
          angle_10_ = 181.0f;
          
          BF_L = false;
        }
      }
      // ONE TURN BM_R | BOOL MID RIGHT
      if (BM_R) {
        if (BM_R_I) {
          // CUBO 02
          if (angle_2 > 45.0f) angle_2 -= 1.0f;
          else angle_2 = 45.0f;
          rubick_cube.cubitos[2]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_2)), kRadioLarge * sin(deg(angle_2)), 0.0f));

          rubick_cube.cubitos[2]->Rotate(kAroundZRight);

          // CUBO 05
          if (angle_5 > 0.0f) angle_5 -= 1.0f;
          else angle_5 = 0.0f;
          rubick_cube.cubitos[5]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_5)), kRadioNormal * sin(deg(angle_5)), 0.0f));

          rubick_cube.cubitos[5]->Rotate(kAroundZRight);

          // CUBO 08
          if (angle_8 > -45.0f) angle_8 -= 1.0f;
          else angle_8 = -45.0f;
          rubick_cube.cubitos[8]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_8)), kRadioLarge * sin(deg(angle_8)), 0.0f));

          rubick_cube.cubitos[8]->Rotate(kAroundZRight);

          // CUBO 17
          if (angle_17 > -90.0f) angle_17 -= 1.0f;
          else angle_17 = -90.0f;
          rubick_cube.cubitos[17]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_17)), kRadioNormal * sin(deg(angle_17)), 0.0f));

          rubick_cube.cubitos[17]->Rotate(kAroundZRight);

          // CUBO 26
          if (angle_26 > 225.0f) angle_26 -= 1.0f;
          else angle_26 = 225.0f;
          rubick_cube.cubitos[26]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_26)), kRadioLarge * sin(deg(angle_26)), 0.0f));

          rubick_cube.cubitos[26]->Rotate(kAroundZRight);

          // CUBO 23
          if (angle_23 > 180.0f) angle_23 -= 1.0f;
          else angle_23 = 180.0f;
          rubick_cube.cubitos[23]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_23)), kRadioNormal * sin(deg(angle_23)), 0.0f));

          rubick_cube.cubitos[23]->Rotate(kAroundZRight);

          // CUBO 20
          if (angle_20 > 135.0f) angle_20 -= 1.0f;
          else angle_20 = 135.0f;
          rubick_cube.cubitos[20]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_20)), kRadioLarge * sin(deg(angle_20)), 0.0f));

          rubick_cube.cubitos[20]->Rotate(kAroundZRight);

          // CUBO 11
          if (angle_11 > 90.0f) angle_11 -= 1.0f;
          else { angle_11 = 90.0f; BM_R_I = false; }
          rubick_cube.cubitos[11]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_11)), kRadioNormal * sin(deg(angle_11)), 0.0f));

          rubick_cube.cubitos[11]->Rotate(kAroundZRight);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundZRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_2 = rubick_cube.cubitos[2];
          std::shared_ptr<Cubito> new_5 = rubick_cube.cubitos[5];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_11 = rubick_cube.cubitos[11];
          std::shared_ptr<Cubito> new_17 = rubick_cube.cubitos[17];
          std::shared_ptr<Cubito> new_20 = rubick_cube.cubitos[20];
          std::shared_ptr<Cubito> new_23 = rubick_cube.cubitos[23];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          rubick_cube.cubitos[2] = new_20;
          rubick_cube.cubitos[5] = new_11;
          rubick_cube.cubitos[8] = new_2;
          rubick_cube.cubitos[17] = new_5;
          rubick_cube.cubitos[26] = new_8;
          rubick_cube.cubitos[11] = new_23;
          rubick_cube.cubitos[20] = new_26;
          rubick_cube.cubitos[23] = new_17;

          angle_2 = 134.0f;
          angle_5 = 89.0f;
          angle_8 = 44.0f;
          angle_17 = -1.0f;
          angle_26 = 314.0f;
          angle_23 = 269.0f;
          angle_20 = 224.0f;
          angle_11 = 179.0f;

          BM_R = false;
        }
      }
      // ONE TURN BM_L | BOOL MID LEFT
      if (BM_L) {
        if (BM_L_I) {
          // CUBO 02
          if (angle_2_ < 225.0f) angle_2_ += 1.0f;
          else angle_2_ = 225.0f;
          rubick_cube.cubitos[2]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_2_)), kRadioLarge * sin(deg(angle_2_)), 0.0f));

          rubick_cube.cubitos[2]->Rotate(kAroundZLeft);

          // CUBO 05
          if (angle_5_ < 180.0f) angle_5_ += 1.0f;
          else angle_5_ = 180.0f;
          rubick_cube.cubitos[5]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_5_)), kRadioNormal * sin(deg(angle_5_)), 0.0f));

          rubick_cube.cubitos[5]->Rotate(kAroundZLeft);

          // CUBO 08
          if (angle_8_ < 135.0f) angle_8_ += 1.0f;
          else angle_8_ = 135.0f;
          rubick_cube.cubitos[8]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_8_)), kRadioLarge * sin(deg(angle_8_)), 0.0f));

          rubick_cube.cubitos[8]->Rotate(kAroundZLeft);

          // CUBO 17
          if (angle_17_ < 90.0f) angle_17_ += 1.0f;
          else angle_17_ = 90.0f;
          rubick_cube.cubitos[17]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_17_)), kRadioNormal * sin(deg(angle_17_)), 0.0f));

          rubick_cube.cubitos[17]->Rotate(kAroundZLeft);

          // CUBO 26
          if (angle_26_ < 405.0f) angle_26_ += 1.0f;
          else angle_26_ = 405.0f;
          rubick_cube.cubitos[26]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_26_)), kRadioLarge * sin(deg(angle_26_)), 0.0f));

          rubick_cube.cubitos[26]->Rotate(kAroundZLeft);

          // CUBO 23
          if (angle_23_ < 360.0f) angle_23_ += 1.0f;
          else angle_23_ = 360.0f;
          rubick_cube.cubitos[23]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_23_)), kRadioNormal * sin(deg(angle_23_)), 0.0f));

          rubick_cube.cubitos[23]->Rotate(kAroundZLeft);

          // CUBO 20
          if (angle_20_ < 315.0f) angle_20_ += 1.0f;
          else angle_20_ = 315.0f;
          rubick_cube.cubitos[20]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_20_)), kRadioLarge * sin(deg(angle_20_)), 0.0f));

          rubick_cube.cubitos[20]->Rotate(kAroundZLeft);

          // CUBO 11
          if (angle_11_ < 270.0f) angle_11_ += 1.0f;
          else { angle_11_ = 270.0f; BM_L_I = false; }
          rubick_cube.cubitos[11]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_11_)), kRadioNormal * sin(deg(angle_11_)), 0.0f));

          rubick_cube.cubitos[11]->Rotate(kAroundZLeft);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundZLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_2 = rubick_cube.cubitos[2];
          std::shared_ptr<Cubito> new_5 = rubick_cube.cubitos[5];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_11 = rubick_cube.cubitos[11];
          std::shared_ptr<Cubito> new_17 = rubick_cube.cubitos[17];
          std::shared_ptr<Cubito> new_20 = rubick_cube.cubitos[20];
          std::shared_ptr<Cubito> new_23 = rubick_cube.cubitos[23];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          rubick_cube.cubitos[2] = new_8;
          rubick_cube.cubitos[5] = new_17;
          rubick_cube.cubitos[8] = new_26;
          rubick_cube.cubitos[17] = new_23;
          rubick_cube.cubitos[26] = new_20;
          rubick_cube.cubitos[11] = new_5;
          rubick_cube.cubitos[20] = new_2;
          rubick_cube.cubitos[23] = new_11;

          angle_2_ = 136.0f;
          angle_5_ = 91.0f;
          angle_8_ = 46.0f;
          angle_17_ = 1.0f;
          angle_26_ = 316.0f;
          angle_23_ = 271.0f;
          angle_20_ = 226.0f;
          angle_11_ = 181.0f;

          BM_L = false;
        }
      }
      // ONE TURN BB_R | BOOL BACK RIGHT
      if (BB_R) {
        if (BB_R_I) {
          // CUBO 03
          if (angle_3 > 45.0f) angle_3 -= 1.0f;
          else angle_3 = 45.0f;
          rubick_cube.cubitos[3]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_3)), kRadioLarge * sin(deg(angle_3)), -0.5f));

          rubick_cube.cubitos[3]->Rotate(kAroundZRight);

          // CUBO 06
          if (angle_6 > 0.0f) angle_6 -= 1.0f;
          else angle_6 = 0.0f;
          rubick_cube.cubitos[6]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_6)), kRadioNormal * sin(deg(angle_6)), -0.5f));

          rubick_cube.cubitos[6]->Rotate(kAroundZRight);

          // CUBO 09
          if (angle_9 > -45.0f) angle_9 -= 1.0f;
          else angle_9 = -45.0f;
          rubick_cube.cubitos[9]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_9)), kRadioLarge * sin(deg(angle_9)), -0.5f));

          rubick_cube.cubitos[9]->Rotate(kAroundZRight);

          // CUBO 18
          if (angle_18 > -90.0f) angle_18 -= 1.0f;
          else angle_18 = -90.0f;
          rubick_cube.cubitos[18]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_18)), kRadioNormal * sin(deg(angle_18)), -0.5f));

          rubick_cube.cubitos[18]->Rotate(kAroundZRight);

          // CUBO 27
          if (angle_27 > 225.0f) angle_27 -= 1.0f;
          else angle_27 = 225.0f;
          rubick_cube.cubitos[27]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_27)), kRadioLarge * sin(deg(angle_27)), -0.5f));

          rubick_cube.cubitos[27]->Rotate(kAroundZRight);

          // CUBO 24
          if (angle_24 > 180.0f) angle_24 -= 1.0f;
          else angle_24 = 180.0f;
          rubick_cube.cubitos[24]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_24)), kRadioNormal * sin(deg(angle_24)), -0.5f));

          rubick_cube.cubitos[24]->Rotate(kAroundZRight);

          // CUBO 21
          if (angle_21 > 135.0f) angle_21 -= 1.0f;
          else angle_21 = 135.0f;
          rubick_cube.cubitos[21]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_21)), kRadioLarge * sin(deg(angle_21)), -0.5f));

          rubick_cube.cubitos[21]->Rotate(kAroundZRight);

          // CUBO 12
          if (angle_12 > 90.0f) angle_12 -= 1.0f;
          else { angle_12 = 90.0f; BB_R_I = false; }
          rubick_cube.cubitos[12]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_12)), kRadioNormal * sin(deg(angle_12)), -0.5f));

          rubick_cube.cubitos[12]->Rotate(kAroundZRight);

          // CUBO 15
          rubick_cube.cubitos[15]->Rotate(kAroundZRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_3 = rubick_cube.cubitos[3];
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_12 = rubick_cube.cubitos[12];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_21 = rubick_cube.cubitos[21];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          rubick_cube.cubitos[3] = new_21;
          rubick_cube.cubitos[6] = new_12;
          rubick_cube.cubitos[9] = new_3;
          rubick_cube.cubitos[18] = new_6;
          rubick_cube.cubitos[27] = new_9;
          rubick_cube.cubitos[12] = new_24;
          rubick_cube.cubitos[21] = new_27;
          rubick_cube.cubitos[24] = new_18;

          angle_3 = 134.0f;
          angle_6 = 89.0f;
          angle_9 = 44.0f;
          angle_18 = -1.0f;
          angle_27 = 314.0f;
          angle_24 = 269.0f;
          angle_21 = 224.0f;
          angle_12 = 179.0f;

          BB_R = false;
        }
      }
      // ONE TURN BB_L | BOOL BACK LEFT
      if (BB_L) {
        if (BB_L_I) {
          // CUBO 03
          if (angle_3_ < 225.0f) angle_3_ += 1.0f;
          else angle_3_ = 225.0f;
          rubick_cube.cubitos[3]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_3_)), kRadioLarge * sin(deg(angle_3_)), -0.5f));

          rubick_cube.cubitos[3]->Rotate(kAroundZLeft);

          // CUBO 06
          if (angle_6_ < 180.0f) angle_6_ += 1.0f;
          else angle_6_ = 180.0f;
          rubick_cube.cubitos[6]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_6_)), kRadioNormal * sin(deg(angle_6_)), -0.5f));

          rubick_cube.cubitos[6]->Rotate(kAroundZLeft);

          // CUBO 09
          if (angle_9_ < 135.0f) angle_9_ += 1.0f;
          else angle_9_ = 135.0f;
          rubick_cube.cubitos[9]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_9_)), kRadioLarge * sin(deg(angle_9_)), -0.5f));

          rubick_cube.cubitos[9]->Rotate(kAroundZLeft);

          // CUBO 18
          if (angle_18_ < 90.0f) angle_18_ += 1.0f;
          else angle_18_ = 90.0f;
          rubick_cube.cubitos[18]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_18_)), kRadioNormal * sin(deg(angle_18_)), -0.5f));

          rubick_cube.cubitos[18]->Rotate(kAroundZLeft);

          // CUBO 27
          if (angle_27_ < 405.0f) angle_27_ += 1.0f;
          else angle_27_ = 405.0f;
          rubick_cube.cubitos[27]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_27_)), kRadioLarge * sin(deg(angle_27_)), -0.5f));

          rubick_cube.cubitos[27]->Rotate(kAroundZLeft);

          // CUBO 24
          if (angle_24_ < 360.0f) angle_24_ += 1.0f;
          else angle_24_ = 360.0f;
          rubick_cube.cubitos[24]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_24_)), kRadioNormal * sin(deg(angle_24_)), -0.5f));

          rubick_cube.cubitos[24]->Rotate(kAroundZLeft);

          // CUBO 21
          if (angle_21_ < 315.0f) angle_21_ += 1.0f;
          else angle_21_ = 315.0f;
          rubick_cube.cubitos[21]->Translate(glm::vec3(kRadioLarge * cos(deg(angle_21_)), kRadioLarge * sin(deg(angle_21_)), -0.5f));

          rubick_cube.cubitos[21]->Rotate(kAroundZLeft);

          // CUBO 12
          if (angle_12_ < 270.0f) angle_12_ += 1.0f;
          else { angle_12_ = 270.0f; BB_L_I = false; }
          rubick_cube.cubitos[12]->Translate(glm::vec3(kRadioNormal * cos(deg(angle_12_)), kRadioNormal * sin(deg(angle_12_)), -0.5f));

          rubick_cube.cubitos[12]->Rotate(kAroundZLeft);

          // CUBO 15
          rubick_cube.cubitos[15]->Rotate(kAroundZLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_3 = rubick_cube.cubitos[3];
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_12 = rubick_cube.cubitos[12];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_21 = rubick_cube.cubitos[21];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          rubick_cube.cubitos[3] = new_9;
          rubick_cube.cubitos[6] = new_18;
          rubick_cube.cubitos[9] = new_27;
          rubick_cube.cubitos[18] = new_24;
          rubick_cube.cubitos[27] = new_21;
          rubick_cube.cubitos[12] = new_6;
          rubick_cube.cubitos[21] = new_3;
          rubick_cube.cubitos[24] = new_12;

          angle_3_ = 136.0f;
          angle_6_ = 91.0f;
          angle_9_ = 46.0f;
          angle_18_ = 1.0f;
          angle_27_ = 316.0f;
          angle_24_ = 271.0f;
          angle_21_ = 226.0f;
          angle_12_ = 181.0f;

          BB_L = false;
        }
      }

      // ====================================================================================== MOVEMENTS OF LEFT MID RIGHT - COLUMN

      // ONE TURN BCL_D | BOOL COLUMN LEFT DOWN
      if (BCL_D) {
        if (BCL_D_I) {
          // CUBO 03  
          if (cl_angle_3 > 45.0f) cl_angle_3 -= 1.0f;
          else cl_angle_3 = 45.0f;
          rubick_cube.cubitos[3]->Translate(glm::vec3(-0.5f, kRadioLarge * sin(deg(cl_angle_3)), kRadioLarge * cos(deg(cl_angle_3))));

          rubick_cube.cubitos[3]->Rotate(kAroundXLeft);

          // CUBO 02
          if (cl_angle_2 > 0.0f) cl_angle_2 -= 1.0f;
          else cl_angle_2 = 0.0f;
          rubick_cube.cubitos[2]->Translate(glm::vec3(-0.5f, kRadioNormal* sin(deg(cl_angle_2)), kRadioNormal* cos(deg(cl_angle_2))));

          rubick_cube.cubitos[2]->Rotate(kAroundXLeft);

          // CUBO 01
          if (cl_angle_1 > -135.0f) cl_angle_1 -= 1.0f;
          else cl_angle_1 = -135.0f;
          rubick_cube.cubitos[1]->Translate(glm::vec3(-0.5f, kRadioLarge * sin(deg(cl_angle_1)), kRadioLarge * cos(deg(cl_angle_1))));

          rubick_cube.cubitos[1]->Rotate(kAroundXLeft);

          // CUBO 10
          if (cl_angle_10 > 270.0f) cl_angle_10 -= 1.0f;
          else cl_angle_10 = 270.0f;
          rubick_cube.cubitos[10]->Translate(glm::vec3(-0.5f, kRadioNormal* sin(deg(cl_angle_10)), kRadioNormal* cos(deg(cl_angle_10))));
        
          rubick_cube.cubitos[10]->Rotate(kAroundXLeft);

          // CUBO 19
          if (cl_angle_19 > 225.0f) cl_angle_19 -= 1.0f;
          else cl_angle_19 = 225.0f;
          rubick_cube.cubitos[19]->Translate(glm::vec3(-0.5f, kRadioLarge * sin(deg(cl_angle_19)), kRadioLarge * cos(deg(cl_angle_19))));

          rubick_cube.cubitos[19]->Rotate(kAroundXLeft);

          // CUBO 20
          if (cl_angle_20 > 180.0f) cl_angle_20 -= 1.0f;
          else cl_angle_20 = 180.0f;
          rubick_cube.cubitos[20]->Translate(glm::vec3(-0.5f, kRadioNormal * sin(deg(cl_angle_20)), kRadioNormal* cos(deg(cl_angle_20))));

          rubick_cube.cubitos[20]->Rotate(kAroundXLeft);

          // CUBO 21
          if (cl_angle_21 > 135.0f) cl_angle_21 -= 1.0f;
          else cl_angle_21 = 135.0f;
          rubick_cube.cubitos[21]->Translate(glm::vec3(-0.5f, kRadioLarge * sin(deg(cl_angle_21)), kRadioLarge* cos(deg(cl_angle_21))));

          rubick_cube.cubitos[21]->Rotate(kAroundXLeft);

          // CUBO 12
          if (cl_angle_12 > 90.0f) cl_angle_12 -= 1.0f;
          else { cl_angle_12 = 90.0f; BCL_D_I = false; }
          rubick_cube.cubitos[12]->Translate(glm::vec3(-0.5f, kRadioNormal * sin(deg(cl_angle_12)), kRadioNormal * cos(deg(cl_angle_12))));

          rubick_cube.cubitos[12]->Rotate(kAroundXLeft);

          // CUBO 11
          rubick_cube.cubitos[11]->Rotate(kAroundXLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_3 = rubick_cube.cubitos[3];
          std::shared_ptr<Cubito> new_2 = rubick_cube.cubitos[2];
          std::shared_ptr<Cubito> new_1 = rubick_cube.cubitos[1];
          std::shared_ptr<Cubito> new_12 = rubick_cube.cubitos[12];
          std::shared_ptr<Cubito> new_10 = rubick_cube.cubitos[10];
          std::shared_ptr<Cubito> new_21 = rubick_cube.cubitos[21];
          std::shared_ptr<Cubito> new_20 = rubick_cube.cubitos[20];
          std::shared_ptr<Cubito> new_19 = rubick_cube.cubitos[19];
          rubick_cube.cubitos[3] = new_21;
          rubick_cube.cubitos[2] = new_12;
          rubick_cube.cubitos[1] = new_3;
          rubick_cube.cubitos[10] = new_2;
          rubick_cube.cubitos[19] = new_1;
          rubick_cube.cubitos[12] = new_20;
          rubick_cube.cubitos[21] = new_19;
          rubick_cube.cubitos[20] = new_10;

          cl_angle_3 = 134.0f;
          cl_angle_2 = 89.0f;
          cl_angle_1 = 44.0f;
          cl_angle_12 = 179.0f;
          cl_angle_10 = 359.0f;
          cl_angle_21 = 224.0f;
          cl_angle_20 = 269.0f;
          cl_angle_19 = 314.0f;

          BCL_D = false;
        }
      }

    }
    
    // Testing one cube
    //rubick_cube.cubitos[3]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[4]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[7]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[16]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[25]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[22]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[19]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[10]->DrawSprite(model, view, projection);
    //rubick_cube.cubitos[13]->DrawSprite(model, view, projection);
    
    // All cubes
    rubick_cube.Draw(model, view, projection);

  /*  if (0 == 1) {
      switch (type_of_move) {
      case 0: {break; }
      case VL_U: {rubick_cube.Move(VL_U); break; }
      case VL_D: {rubick_cube.Move(VL_D); break; }
      case VM_U: {rubick_cube.Move(VM_U); break; }
      case VM_D: {rubick_cube.Move(VM_D); break; }
      case VR_U: {rubick_cube.Move(VR_U); break; }
      case VR_D: {rubick_cube.Move(VR_D); break; }
      case HU_L: {rubick_cube.Move(HU_L); break; }
      case HU_R: {rubick_cube.Move(HU_R); break; }
      case HM_L: {rubick_cube.Move(HM_L); break; }
      case HM_R: {rubick_cube.Move(HM_R); break; }
      case HD_L: {rubick_cube.Move(HD_L); break; }
      case HD_R: {rubick_cube.Move(HD_R); break; }
      default: {std::cout << "ERROR ON MOVE" << std::endl; break; }
      }
    }*/

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  float cameraSpeed = 2.5 * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);


  // ROWS MOVEMENTS

  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    BRF_L = true;
    BRF_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    BRF_R = true;
    BRF_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_R);
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    BRM_L = true;
    BRM_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HM_L); BRF_R = true;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    BRM_R = true;
    BRM_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HM_R);
  }

  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
    BRT_L = true;
    BRT_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HD_L);
  }

  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS){
    BRT_R = true;
    BRT_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HD_R);
  }

  // COLUMNS MOVEMENTS

  if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
    BCL_U = true;
    BCL_U_I = true;
    some_movement = true;
    //rubick_cube.Move(VM_U);
  }

  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
    BCL_D = true;
    BCL_D_I = true;
    some_movement = true;
    //rubick_cube.Move(VM_D);
  }
  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    BCM_U = true;
    BCM_U_I = true;
    some_movement = true;
    //rubick_cube.Move(VR_U);
  }
  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
    BCM_D = true;
    BCM_D_I = true;
    some_movement = true;
    //rubick_cube.Move(VR_D);
  }
  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
    BCR_U = true;
    BCR_U_I = true;
    some_movement = true;
    //rubick_cube.Move(VL_U);
  }
  if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
    BCR_D = true;
    BCR_D_I = true;
    some_movement = true;
    //rubick_cube.Move(VL_D);
  }

  // FRONT MID AND BACK GROUP
  
  if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
    BF_L = true;
    BF_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
  if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
    BF_R = true;
    BF_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
  if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
    BM_L = true;
    BM_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
  if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
    BM_R = true;
    BM_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    BB_L = true;
    BB_L_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
  if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
    BB_R = true;
    BB_R_I = true;
    some_movement = true;
    //rubick_cube.Move(HU_L);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
  if (first_time_mouse) {
    lastX = xpos;
    lastY = ypos;
    first_time_mouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(yoffset);
}
