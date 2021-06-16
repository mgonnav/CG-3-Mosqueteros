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

#include <cmath>
#include <functional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

// IF YOU WANT TO KNOW INFO AFTER ONE MOVEMENT
#define DEBUG 0

enum Move {
  L, LP,
  R, RP,
  U, UP,
  D, DP,
  F, FP,
  B, BP
};

bool BCL_U = false, BCL_U_I = false;
bool BCL_D = false, BCL_D_I = false;
bool BCM_U = false, BCM_U_I = false;
bool BCM_D = false, BCM_D_I = false;
bool BCR_U = false, BCR_U_I = false;
bool BCR_D = false, BCR_D_I = false;

bool BRF_L = false, BRF_L_I = false;
bool BRF_R = false, BRF_R_I = false;
bool BRS_L = false, BRS_L_I = false;
bool BRS_R = false, BRS_R_I = false;
bool BRT_L = false, BRT_L_I = false;
bool BRT_R = false, BRT_R_I = false;

bool F_R = false, F_R_I = false;
bool F_L = false, F_L_I = false;
bool BM_R = false, BM_R_I = false;
bool BM_L = false, BM_L_I = false;
bool B_R = false, B_R_I = false;
bool B_L = false, B_L_I = false;

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
void ParallelAnimation();

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

// MAIN OBJECT THAT CONTROL CUBE RUBICK
Cubo rubick_cube;

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

//========================================== VARIABLES FOR MOVEMENTS

bool some_movement = false;
const float kRadioLarge = 0.5f * sqrt(2);
const float kRadioNormal = 0.5f;

// ========================================= PARALEL MOVEMENTS | FRONT MID BACK

// BM_R

float mr_angle_2 = 134.0f;
float mr_angle_5 = 89.0f;
float mr_angle_8 = 44.0f;
float mr_angle_17 = -1.0f;
float mr_angle_26 = 314.0f;
float mr_angle_23 = 269.0f;
float mr_angle_20 = 224.0f;
float mr_angle_11 = 179.0f;

// BM_L

float ml_angle_2 = 136.0f;
float ml_angle_5 = 91.0f;
float ml_angle_8 = 46.0f;
float ml_angle_17 = 1.0f;
float ml_angle_26 = 316.0f;
float ml_angle_23 = 271.0f;
float ml_angle_20 = 226.0f;
float ml_angle_11 = 181.0f;

// ========================================= COLUMN MOVEMENTS | LEFT MID RIGHT

// COLUMN LEFT DOWN

float cld_angle_3 = 134.0f;
float cld_angle_2 = 89.0f;
float cld_angle_1 = 44.0f;
float cld_angle_12 = 179.0f;
float cld_angle_10 = 0.0f;
float cld_angle_21 = 224.0f;
float cld_angle_20 = 269.0f;
float cld_angle_19 = 314.0f;

// COLUMN LEFT UP

float clu_angle_3 = 136.0f;
float clu_angle_2 = 91.0f;
float clu_angle_1 = 46.0f;
float clu_angle_12 = 181.0f;
float clu_angle_10 = 1.0f;
float clu_angle_21 = 226.0f;
float clu_angle_20 = 271.0f;
float clu_angle_19 = -45.0f;

// COLUMN MID DOWN

float cmd_angle_6 = 134.0f;
float cmd_angle_5 = 89.0f;
float cmd_angle_4 = 44.0f;
float cmd_angle_15 = 179.0f;
float cmd_angle_13 = 359.0f;
float cmd_angle_24 = 224.0f;
float cmd_angle_23 = 269.0f;
float cmd_angle_22 = 314.0f;

// COLUMN MID UP

float cmu_angle_6 = 136.0f;
float cmu_angle_5 = 91.0f;
float cmu_angle_4 = 46.0f;
float cmu_angle_15 = 181.0f;
float cmu_angle_13 = 1.0f;
float cmu_angle_24 = 226.0f;
float cmu_angle_23 = 271.0f;
float cmu_angle_22 = -45.0f;

// COLUMN RIGHT DOWN

float crd_angle_9 = 134.0f;
float crd_angle_8 = 89.0f;
float crd_angle_7 = 44.0f;
float crd_angle_18 = 179.0f;
float crd_angle_16 = 359.0f;
float crd_angle_27 = 224.0f;
float crd_angle_26 = 269.0f;
float crd_angle_25 = 314.0f;

// COLUMN RIGHT UP

float cru_angle_9 = 136.0f;
float cru_angle_8 = 91.0f;
float cru_angle_7 = 46.0f;
float cru_angle_18 = 181.0f;
float cru_angle_16 = 1.0f;
float cru_angle_27 = 226.0f;
float cru_angle_26 = 271.0f;
float cru_angle_25 = -45.0f;

// ========================================= ROWS MOVEMENTS | FIRST SECOND THIRD

// ROW FIRST LEFT

float rfl_angle_3 = 226.0f;
float rfl_angle_6 = 271.0f;
float rfl_angle_9 = -44.0f;
float rfl_angle_2 = 181.0f;
float rfl_angle_8 = 1.0f;
float rfl_angle_1 = 136.0f;
float rfl_angle_4 = 91.0f;
float rfl_angle_7 = 46.0f;

// ROW FIRST RIGHT

float rfr_angle_3 = 224.0f;
float rfr_angle_6 = 269.0f;
float rfr_angle_9 = 314.0f;
float rfr_angle_2 = 179.0f;
float rfr_angle_8 = 359.0f;
float rfr_angle_1 = 134.0f;
float rfr_angle_4 = 89.0f;
float rfr_angle_7 = 44.0f;

// ROW SECOND LEFT

float rsl_angle_12 = 226.0f;
float rsl_angle_15 = 271.0f;
float rsl_angle_18 = -44.0f;
float rsl_angle_11 = 181.0f;
float rsl_angle_17 = 1.0f;
float rsl_angle_10 = 136.0f;
float rsl_angle_13 = 91.0f;
float rsl_angle_16 = 46.0f;

// ROW SECOND RIGHT

float rsr_angle_12 = 224.0f;
float rsr_angle_15 = 269.0f;
float rsr_angle_18 = 314.0f;
float rsr_angle_11 = 179.0f;
float rsr_angle_17 = 359.0f;
float rsr_angle_10 = 134.0f;
float rsr_angle_13 = 89.0f;
float rsr_angle_16 = 44.0f;

// ROW THIRD LEFT

float rtl_angle_21 = 226.0f;
float rtl_angle_24 = 271.0f;
float rtl_angle_27 = -44.0f;
float rtl_angle_20 = 181.0f;
float rtl_angle_26 = 1.0f;
float rtl_angle_19 = 136.0f;
float rtl_angle_22 = 91.0f;
float rtl_angle_25 = 46.0f;

// ROW THIRD RIGHT

float rtr_angle_21 = 224.0f;
float rtr_angle_24 = 269.0f;
float rtr_angle_27 = 314.0f;
float rtr_angle_20 = 179.0f;
float rtr_angle_26 = 359.0f;
float rtr_angle_19 = 134.0f;
float rtr_angle_22 = 89.0f;
float rtr_angle_25 = 44.0f;

// PRINT COMMANDS

void Print() {
  std::cout << "\n\t\tWELCOME TO CUBITO MOSQUETERO" << std::endl;
  std::cout << "\t\t     CONTROLS TO PLAY" << std::endl << std::endl;

  std::cout << "\t    FIRST GROUP OF MOVEMENT" << std::endl;
  std::cout << "\tQ | FIRST ROW TURN LEFT" << std::endl;
  std::cout << "\tW | FIRST ROW TURN RIGHT" << std::endl;
  std::cout << "\tA | SECOND ROW TURN LEFT" << std::endl;
  std::cout << "\tS | SECOND ROW TURN RIGHT" << std::endl;
  std::cout << "\tZ | THIRD ROW TURN LEFT" << std::endl;
  std::cout << "\tX | THIRD ROW TURN RIGHT\n" << std::endl;

  std::cout << "\t    SECOND GROUP OF MOVEMENT" << std::endl;
  std::cout << "\tU | LEFT COLUMN TURN UP" << std::endl;
  std::cout << "\tJ | LEFT COLUMN TURN DOWN" << std::endl;
  std::cout << "\tI | MID COLUMN TURN UP" << std::endl;
  std::cout << "\tK | MID COLUMN TURN DOWN" << std::endl;
  std::cout << "\tO | RIGHT COLUMN TURN UP" << std::endl;
  std::cout << "\tL | RIGHT COLUMN TURN DOWN\n" << std::endl;

  std::cout << "\t    THIRD GROUP OF MOVEMENT" << std::endl;
  std::cout << "\tV | FRONT GROUP TURN LEFT" << std::endl;
  std::cout << "\tB | FRONT GROUP TURN RIGHT" << std::endl;
  std::cout << "\tF | MID GROUP TURN LEFT" << std::endl;
  std::cout << "\tG | MID GROUP TURN RIGHT" << std::endl;
  std::cout << "\tR | BACK GROUP TURN LEFT" << std::endl;
  std::cout << "\tT | BACK GROUP TURN RIGHT\n" << std::endl;
  std::cout << "\tPLEASE PRESS ONE BUTTON ONCE AND WAIT IT FINISH UNTIL NEXT PRESS\n" << std::endl;
  std::cout << "\tYOU CAN MOVE SIMULTANEOUSLY SOME PARTS THAT NOT HAVE CUBES IN COMMON\n" << std::endl;

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
  
  // CREATING EACH CUBITO OF RUBICK CUBE
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
      if ((F_R && F_R_I) || (B_R && B_R_I)
          || (F_L && F_L_I) || (B_L && B_L_I)) {
        ParallelAnimation();
      }

      // BOOL COLUMN LEFT DOWN
      if (BCL_D && BCL_D_I) {
        ParallelAnimation();
      }
      if (BCL_U && BCL_U_I) {
        ParallelAnimation();
      }

      // BOOL COLUMN MID DOWN
      if (BCM_D) {
        if (BCM_D_I) {
          // CUBO 06
          if (cmd_angle_6 > 45.0f) cmd_angle_6 -= 1.0f;
          else cmd_angle_6 = 45.0f;
          rubick_cube.cubitos[6]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmd_angle_6)),
              kRadioLarge * cos(deg(cmd_angle_6))));

          rubick_cube.cubitos[6]->Rotate(kAroundXLeft);

          // CUBO 05
          if (cmd_angle_5 > 0.0f) cmd_angle_5 -= 1.0f;
          else cmd_angle_5 = 0.0f;
          rubick_cube.cubitos[5]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmd_angle_5)),
              kRadioNormal * cos(deg(cmd_angle_5))));

          rubick_cube.cubitos[5]->Rotate(kAroundXLeft);

          // CUBO 04
          if (cmd_angle_4 > -135.0f) cmd_angle_4 -= 1.0f;
          else cmd_angle_4 = -135.0f;
          rubick_cube.cubitos[4]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmd_angle_4)),
              kRadioLarge * cos(deg(cmd_angle_4))));

          rubick_cube.cubitos[4]->Rotate(kAroundXLeft);

          // CUBO 13
          if (cmd_angle_13 > 270.0f) cmd_angle_13 -= 1.0f;
          else cmd_angle_13 = 270.0f;
          rubick_cube.cubitos[13]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmd_angle_13)),
              kRadioNormal * cos(deg(cmd_angle_13))));

          rubick_cube.cubitos[13]->Rotate(kAroundXLeft);

          // CUBO 22
          if (cmd_angle_22 > 225.0f) cmd_angle_22 -= 1.0f;
          else cmd_angle_22 = 225.0f;
          rubick_cube.cubitos[22]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmd_angle_22)),
              kRadioLarge * cos(deg(cmd_angle_22))));

          rubick_cube.cubitos[22]->Rotate(kAroundXLeft);

          // CUBO 23
          if (cmd_angle_23 > 180.0f) cmd_angle_23 -= 1.0f;
          else cmd_angle_23 = 180.0f;
          rubick_cube.cubitos[23]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmd_angle_23)),
              kRadioNormal * cos(deg(cmd_angle_23))));

          rubick_cube.cubitos[23]->Rotate(kAroundXLeft);

          // CUBO 24
          if (cmd_angle_24 > 135.0f) cmd_angle_24 -= 1.0f;
          else cmd_angle_24 = 135.0f;
          rubick_cube.cubitos[24]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmd_angle_24)),
              kRadioLarge * cos(deg(cmd_angle_24))));

          rubick_cube.cubitos[24]->Rotate(kAroundXLeft);

          // CUBO 15
          if (cmd_angle_15 > 90.0f) cmd_angle_15 -= 1.0f;
          else { cmd_angle_15 = 90.0f; BCM_D_I = false; }
          rubick_cube.cubitos[15]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmd_angle_15)),
              kRadioNormal * cos(deg(cmd_angle_15))));

          rubick_cube.cubitos[15]->Rotate(kAroundXLeft);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundXLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_5 = rubick_cube.cubitos[5];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_15 = rubick_cube.cubitos[15];
          std::shared_ptr<Cubito> new_13 = rubick_cube.cubitos[13];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_23 = rubick_cube.cubitos[23];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          rubick_cube.cubitos[6] = new_24;
          rubick_cube.cubitos[5] = new_15;
          rubick_cube.cubitos[4] = new_6;
          rubick_cube.cubitos[13] = new_5;
          rubick_cube.cubitos[22] = new_4;
          rubick_cube.cubitos[15] = new_23;
          rubick_cube.cubitos[24] = new_22;
          rubick_cube.cubitos[23] = new_13;

          cmd_angle_6 = 134.0f;
          cmd_angle_5 = 89.0f;
          cmd_angle_4 = 44.0f;
          cmd_angle_15 = 179.0f;
          cmd_angle_13 = 359.0f;
          cmd_angle_24 = 224.0f;
          cmd_angle_23 = 269.0f;
          cmd_angle_22 = 314.0f;

          BCM_D = false;
          if (DEBUG) {
            rubick_cube.cubitos[6]->MyData();
            rubick_cube.cubitos[5]->MyData();
            rubick_cube.cubitos[4]->MyData();
            rubick_cube.cubitos[13]->MyData();
            rubick_cube.cubitos[22]->MyData();
            rubick_cube.cubitos[15]->MyData();
            rubick_cube.cubitos[24]->MyData();
            rubick_cube.cubitos[23]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL COLUMN MID UP
      if (BCM_U) {
        if (BCM_U_I) {
          // CUBO 06
          if (cmu_angle_6 < 255.0f) cmu_angle_6 += 1.0f;
          else cmu_angle_6 = 255.0f;
          rubick_cube.cubitos[6]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmu_angle_6)),
              kRadioLarge * cos(deg(cmu_angle_6))));

          rubick_cube.cubitos[6]->Rotate(kAroundXRight);

          // CUBO 05
          if (cmu_angle_5 < 180.0f) cmu_angle_5 += 1.0f;
          else cmu_angle_5 = 180.0f;
          rubick_cube.cubitos[5]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmu_angle_5)),
              kRadioNormal * cos(deg(cmu_angle_5))));

          rubick_cube.cubitos[5]->Rotate(kAroundXRight);

          // CUBO 04
          if (cmu_angle_4 < 135.0f) cmu_angle_4 += 1.0f;
          else cmu_angle_4 = 135.0f;
          rubick_cube.cubitos[4]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmu_angle_4)),
              kRadioLarge * cos(deg(cmu_angle_4))));

          rubick_cube.cubitos[4]->Rotate(kAroundXRight);

          // CUBO 13
          if (cmu_angle_13 < 90.0f) cmu_angle_13 += 1.0f;
          else cmu_angle_13 = 90.0f;
          rubick_cube.cubitos[13]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmu_angle_13)),
              kRadioNormal * cos(deg(cmu_angle_13))));

          rubick_cube.cubitos[13]->Rotate(kAroundXRight);

          // CUBO 22
          if (cmu_angle_22 < 45.0f) cmu_angle_22 += 1.0f;
          else cmu_angle_22 = 45.0f;
          rubick_cube.cubitos[22]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmu_angle_22)),
              kRadioLarge * cos(deg(cmu_angle_22))));

          rubick_cube.cubitos[22]->Rotate(kAroundXRight);

          // CUBO 23
          if (cmu_angle_23 < 360.0f) cmu_angle_23 += 1.0f;
          else cmu_angle_23 = 360.0f;
          rubick_cube.cubitos[23]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmu_angle_23)),
              kRadioNormal * cos(deg(cmu_angle_23))));

          rubick_cube.cubitos[23]->Rotate(kAroundXRight);

          // CUBO 24
          if (cmu_angle_24 < 315.0f) cmu_angle_24 += 1.0f;
          else cmu_angle_24 = 315.0f;
          rubick_cube.cubitos[24]->
            Translate(glm::vec3(0.0f, 
              kRadioLarge * sin(deg(cmu_angle_24)),
              kRadioLarge * cos(deg(cmu_angle_24))));

          rubick_cube.cubitos[24]->Rotate(kAroundXRight);

          // CUBO 15
          if (cmu_angle_15 < 270.0f) cmu_angle_15 += 1.0f;
          else { cmu_angle_15 = 270.0f; BCM_U_I = false; }
          rubick_cube.cubitos[15]->
            Translate(glm::vec3(0.0f, 
              kRadioNormal * sin(deg(cmu_angle_15)),
              kRadioNormal * cos(deg(cmu_angle_15))));

          rubick_cube.cubitos[15]->Rotate(kAroundXRight);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundXRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_5 = rubick_cube.cubitos[5];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_15 = rubick_cube.cubitos[15];
          std::shared_ptr<Cubito> new_13 = rubick_cube.cubitos[13];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_23 = rubick_cube.cubitos[23];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          rubick_cube.cubitos[6] = new_4;
          rubick_cube.cubitos[5] = new_13;
          rubick_cube.cubitos[4] = new_22;
          rubick_cube.cubitos[15] = new_5;
          rubick_cube.cubitos[13] = new_23;
          rubick_cube.cubitos[24] = new_6;
          rubick_cube.cubitos[23] = new_15;
          rubick_cube.cubitos[22] = new_24;

          cmu_angle_6 = 136.0f;
          cmu_angle_5 = 91.0f;
          cmu_angle_4 = 46.0f;
          cmu_angle_15 = 181.0f;
          cmu_angle_13 = 1.0f;
          cmu_angle_24 = 226.0f;
          cmu_angle_23 = 271.0f;
          cmu_angle_22 = -45.0f;

          BCM_U = false;
          if (DEBUG) {
            rubick_cube.cubitos[6]->MyData();
            rubick_cube.cubitos[5]->MyData();
            rubick_cube.cubitos[4]->MyData();
            rubick_cube.cubitos[15]->MyData();
            rubick_cube.cubitos[13]->MyData();
            rubick_cube.cubitos[24]->MyData();
            rubick_cube.cubitos[23]->MyData();
            rubick_cube.cubitos[22]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL COLUMN RIGHT DOWN
      if (BCR_D) {
        if (BCR_D_I) {
          // CUBO 09
          if (crd_angle_9 > 45.0f) crd_angle_9 -= 1.0f;
          else crd_angle_9 = 45.0f;
          rubick_cube.cubitos[9]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(crd_angle_9)),
              kRadioLarge * cos(deg(crd_angle_9))));

          rubick_cube.cubitos[9]->Rotate(kAroundXLeft);

          // CUBO 08
          if (crd_angle_8 > 0.0f) crd_angle_8 -= 1.0f;
          else crd_angle_8 = 0.0f;
          rubick_cube.cubitos[8]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(crd_angle_8)),
              kRadioNormal * cos(deg(crd_angle_8))));

          rubick_cube.cubitos[8]->Rotate(kAroundXLeft);

          // CUBO 07
          if (crd_angle_7 > -135.0f) crd_angle_7 -= 1.0f;
          else crd_angle_7 = -135.0f;
          rubick_cube.cubitos[7]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(crd_angle_7)),
              kRadioLarge * cos(deg(crd_angle_7))));

          rubick_cube.cubitos[7]->Rotate(kAroundXLeft);

          // CUBO 16
          if (crd_angle_16 > 270.0f) crd_angle_16 -= 1.0f;
          else crd_angle_16 = 270.0f;
          rubick_cube.cubitos[16]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(crd_angle_16)),
              kRadioNormal * cos(deg(crd_angle_16))));

          rubick_cube.cubitos[16]->Rotate(kAroundXLeft);

          // CUBO 25
          if (crd_angle_25 > 225.0f) crd_angle_25 -= 1.0f;
          else crd_angle_25 = 225.0f;
          rubick_cube.cubitos[25]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(crd_angle_25)),
              kRadioLarge * cos(deg(crd_angle_25))));

          rubick_cube.cubitos[25]->Rotate(kAroundXLeft);

          // CUBO 26
          if (crd_angle_26 > 180.0f) crd_angle_26 -= 1.0f;
          else crd_angle_26 = 180.0f;
          rubick_cube.cubitos[26]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(crd_angle_26)),
              kRadioNormal * cos(deg(crd_angle_26))));

          rubick_cube.cubitos[26]->Rotate(kAroundXLeft);

          // CUBO 27
          if (crd_angle_27 > 135.0f) crd_angle_27 -= 1.0f;
          else crd_angle_27 = 135.0f;
          rubick_cube.cubitos[27]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(crd_angle_27)),
              kRadioLarge * cos(deg(crd_angle_27))));

          rubick_cube.cubitos[27]->Rotate(kAroundXLeft);

          // CUBO 18
          if (crd_angle_18 > 90.0f) crd_angle_18 -= 1.0f;
          else { crd_angle_18 = 90.0f; BCR_D_I = false; }
          rubick_cube.cubitos[18]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(crd_angle_18)),
              kRadioNormal * cos(deg(crd_angle_18))));

          rubick_cube.cubitos[18]->Rotate(kAroundXLeft);

          // CUBO 17
          rubick_cube.cubitos[17]->Rotate(kAroundXLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[9] = new_27;
          rubick_cube.cubitos[8] = new_18;
          rubick_cube.cubitos[7] = new_9;
          rubick_cube.cubitos[18] = new_26;
          rubick_cube.cubitos[16] = new_8;
          rubick_cube.cubitos[27] = new_25;
          rubick_cube.cubitos[26] = new_16;
          rubick_cube.cubitos[25] = new_7;

          crd_angle_9 = 134.0f;
          crd_angle_8 = 89.0f;
          crd_angle_7 = 44.0f;
          crd_angle_18 = 179.0f;
          crd_angle_16 = 359.0f;
          crd_angle_27 = 224.0f;
          crd_angle_26 = 269.0f;
          crd_angle_25 = 314.0f;

          BCR_D = false;
          if (DEBUG) {
            rubick_cube.cubitos[9]->MyData();
            rubick_cube.cubitos[8]->MyData();
            rubick_cube.cubitos[7]->MyData();
            rubick_cube.cubitos[18]->MyData();
            rubick_cube.cubitos[17]->MyData();
            rubick_cube.cubitos[16]->MyData();
            rubick_cube.cubitos[27]->MyData();
            rubick_cube.cubitos[26]->MyData();
            rubick_cube.cubitos[25]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL COLUMN RIGHT UP
      if (BCR_U) {
        if (BCR_U_I) {
          // CUBO 09
          if (cru_angle_9 < 255.0f) cru_angle_9 += 1.0f;
          else cru_angle_9 = 255.0f;
          rubick_cube.cubitos[9]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(cru_angle_9)),
              kRadioLarge * cos(deg(cru_angle_9))));

          rubick_cube.cubitos[9]->Rotate(kAroundXRight);

          // CUBO 08
          if (cru_angle_8 < 180.0f) cru_angle_8 += 1.0f;
          else cru_angle_8 = 180.0f;
          rubick_cube.cubitos[8]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(cru_angle_8)),
              kRadioNormal * cos(deg(cru_angle_8))));

          rubick_cube.cubitos[8]->Rotate(kAroundXRight);

          // CUBO 07
          if (cru_angle_7 < 135.0f) cru_angle_7 += 1.0f;
          else cru_angle_7 = 135.0f;
          rubick_cube.cubitos[7]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(cru_angle_7)),
              kRadioLarge * cos(deg(cru_angle_7))));

          rubick_cube.cubitos[7]->Rotate(kAroundXRight);

          // CUBO 16
          if (cru_angle_16 < 90.0f) cru_angle_16 += 1.0f;
          else cru_angle_16 = 90.0f;
          rubick_cube.cubitos[16]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(cru_angle_16)),
              kRadioNormal * cos(deg(cru_angle_16))));

          rubick_cube.cubitos[16]->Rotate(kAroundXRight);

          // CUBO 25
          if (cru_angle_25 < 45.0f) cru_angle_25 += 1.0f;
          else cru_angle_25 = 45.0f;
          rubick_cube.cubitos[25]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(cru_angle_25)),
              kRadioLarge * cos(deg(cru_angle_25))));

          rubick_cube.cubitos[25]->Rotate(kAroundXRight);

          // CUBO 26
          if (cru_angle_26 < 360.0f) cru_angle_26 += 1.0f;
          else cru_angle_26 = 360.0f;
          rubick_cube.cubitos[26]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(cru_angle_26)),
              kRadioNormal * cos(deg(cru_angle_26))));

          rubick_cube.cubitos[26]->Rotate(kAroundXRight);

          // CUBO 27
          if (cru_angle_27 < 315.0f) cru_angle_27 += 1.0f;
          else cru_angle_27 = 315.0f;
          rubick_cube.cubitos[27]->
            Translate(glm::vec3(0.5f, 
              kRadioLarge * sin(deg(cru_angle_27)),
              kRadioLarge * cos(deg(cru_angle_27))));

          rubick_cube.cubitos[27]->Rotate(kAroundXRight);

          // CUBO 18
          if (cru_angle_18 < 270.0f) cru_angle_18 += 1.0f;
          else { cru_angle_18 = 270.0f; BCR_U_I = false; }
          rubick_cube.cubitos[18]->
            Translate(glm::vec3(0.5f, 
              kRadioNormal * sin(deg(cru_angle_18)),
              kRadioNormal * cos(deg(cru_angle_18))));

          rubick_cube.cubitos[18]->Rotate(kAroundXRight);

          // CUBO 17
          rubick_cube.cubitos[17]->Rotate(kAroundXRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[9] = new_7;
          rubick_cube.cubitos[8] = new_16;
          rubick_cube.cubitos[7] = new_25;
          rubick_cube.cubitos[18] = new_8;
          rubick_cube.cubitos[16] = new_26;
          rubick_cube.cubitos[27] = new_9;
          rubick_cube.cubitos[26] = new_18;
          rubick_cube.cubitos[25] = new_27;

          cru_angle_9 = 136.0f;
          cru_angle_8 = 91.0f;
          cru_angle_7 = 46.0f;
          cru_angle_18 = 181.0f;
          cru_angle_16 = 1.0f;
          cru_angle_27 = 226.0f;
          cru_angle_26 = 271.0f;
          cru_angle_25 = -45.0f;

          BCR_U = false;
          if (DEBUG) {
            rubick_cube.cubitos[9]->MyData();
            rubick_cube.cubitos[8]->MyData();
            rubick_cube.cubitos[7]->MyData();
            rubick_cube.cubitos[18]->MyData();
            rubick_cube.cubitos[17]->MyData();
            rubick_cube.cubitos[16]->MyData();
            rubick_cube.cubitos[27]->MyData();
            rubick_cube.cubitos[26]->MyData();
            rubick_cube.cubitos[25]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // ========================================= ROWS MOVEMENTS | LEFT SECOND RIGHT

      // BOOL ROW FIRST LEFT
      if (BRF_L) {
        if (BRF_L_I) {
          // CUBO 03  
          if (rfl_angle_3 < 315.0f) rfl_angle_3 += 1.0f;
          else rfl_angle_3 = 315.0f;
          rubick_cube.cubitos[3]->
            Translate(glm::vec3(kRadioLarge* cos(deg(rfl_angle_3)),
              0.5f,
              kRadioLarge * sin(deg(rfl_angle_3))));

          rubick_cube.cubitos[3]->Rotate(kAroundYLeft);

          // CUBO 06
          if (rfl_angle_6 < 360.0f) rfl_angle_6 += 1.0f;
          else rfl_angle_6 = 360.0f;
          rubick_cube.cubitos[6]->
            Translate(glm::vec3(kRadioNormal* cos(deg(rfl_angle_6)),
              0.5f,
              kRadioNormal* sin(deg(rfl_angle_6))));

          rubick_cube.cubitos[6]->Rotate(kAroundYLeft);

          // CUBO 09
          if (rfl_angle_9 < 45.0f) rfl_angle_9 += 1.0f;
          else rfl_angle_9 = 45.0f;
          rubick_cube.cubitos[9]->
            Translate(glm::vec3(kRadioLarge* cos(deg(rfl_angle_9)),
               0.5f,
               kRadioLarge* sin(deg(rfl_angle_9))));

          rubick_cube.cubitos[9]->Rotate(kAroundYLeft);

          // CUBO 8
          if (rfl_angle_8 < 90.0f) rfl_angle_8 += 1.0f;
          else rfl_angle_8 = 90.0f;
          rubick_cube.cubitos[8]->
            Translate(glm::vec3(kRadioNormal* cos(deg(rfl_angle_8)),
               0.5f,
               kRadioNormal* sin(deg(rfl_angle_8))));

          rubick_cube.cubitos[8]->Rotate(kAroundYLeft);

          // CUBO 7
          if (rfl_angle_7 < 135.0f) rfl_angle_7 += 1.0f;
          else rfl_angle_7 = 135.0f;
          rubick_cube.cubitos[7]->
            Translate(glm::vec3(kRadioLarge* cos(deg(rfl_angle_7)),
               0.5f,
               kRadioLarge* sin(deg(rfl_angle_7))));

          rubick_cube.cubitos[7]->Rotate(kAroundYLeft);

          // CUBO 4
          if (rfl_angle_4 < 180.0f) rfl_angle_4 += 1.0f;
          else rfl_angle_4 = 180.0f;
          rubick_cube.cubitos[4]->
            Translate(glm::vec3(kRadioNormal* cos(deg(rfl_angle_4)),
               0.5f,
               kRadioNormal* sin(deg(rfl_angle_4))));

          rubick_cube.cubitos[4]->Rotate(kAroundYLeft);

          // CUBO 1
          if (rfl_angle_1 < 225.0f) rfl_angle_1 += 1.0f;
          else rfl_angle_1 = 225.0f;
          rubick_cube.cubitos[1]->
            Translate(glm::vec3(kRadioLarge* cos(deg(rfl_angle_1)),
                0.5f,
                kRadioLarge* sin(deg(rfl_angle_1))));

          rubick_cube.cubitos[1]->Rotate(kAroundYLeft);

          // CUBO 2
          if (rfl_angle_2 < 270.0f) rfl_angle_2 += 1.0f;
          else { rfl_angle_2 = 270.0f; BRF_L_I = false; }
          rubick_cube.cubitos[2]->
            Translate(glm::vec3(kRadioNormal* cos(deg(rfl_angle_2)),
              0.5f,
              kRadioNormal* sin(deg(rfl_angle_2))));

          rubick_cube.cubitos[2]->Rotate(kAroundYLeft);

          // CUBO 5
          rubick_cube.cubitos[5]->Rotate(kAroundYLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_3 = rubick_cube.cubitos[3];
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_2 = rubick_cube.cubitos[2];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_1 = rubick_cube.cubitos[1];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          rubick_cube.cubitos[3] = new_1;
          rubick_cube.cubitos[6] = new_2;
          rubick_cube.cubitos[9] = new_3;
          rubick_cube.cubitos[2] = new_4;
          rubick_cube.cubitos[8] = new_6;
          rubick_cube.cubitos[1] = new_7;
          rubick_cube.cubitos[4] = new_8;
          rubick_cube.cubitos[7] = new_9;

          rfl_angle_3 = 226.0f;
          rfl_angle_6 = 271.0f;
          rfl_angle_9 = -44.0f;
          rfl_angle_2 = 181.0f;
          rfl_angle_8 = 1.0f;
          rfl_angle_1 = 136.0f;
          rfl_angle_4 = 91.0f;
          rfl_angle_7 = 46.0f;

          BRF_L = false;
          if (DEBUG) {
            rubick_cube.cubitos[3]->MyData();
            rubick_cube.cubitos[6]->MyData();
            rubick_cube.cubitos[9]->MyData();
            rubick_cube.cubitos[2]->MyData();
            rubick_cube.cubitos[8]->MyData();
            rubick_cube.cubitos[1]->MyData();
            rubick_cube.cubitos[4]->MyData();
            rubick_cube.cubitos[7]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL ROW FIRST RIGHT
      if (BRF_R) {
        if (BRF_R_I) {
          // CUBO 03  
          if (rfr_angle_3 > 135.0f) rfr_angle_3 -= 1.0f;
          else rfr_angle_3 = 135.0f;
          rubick_cube.cubitos[3]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rfr_angle_3)),
              0.5f,
              kRadioLarge * sin(deg(rfr_angle_3))));

          rubick_cube.cubitos[3]->Rotate(kAroundYRight);

          // CUBO 06
          if (rfr_angle_6 > 180.0f) rfr_angle_6 -= 1.0f;
          else rfr_angle_6 = 180.0f;
          rubick_cube.cubitos[6]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rfr_angle_6)),
              0.5f,
              kRadioNormal * sin(deg(rfr_angle_6))));

          rubick_cube.cubitos[6]->Rotate(kAroundYRight);

          // CUBO 09
          if (rfr_angle_9 > 225.0f) rfr_angle_9 -= 1.0f;
          else rfr_angle_9 = 225.0f;
          rubick_cube.cubitos[9]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rfr_angle_9)),
              0.5f,
              kRadioLarge * sin(deg(rfr_angle_9))));

          rubick_cube.cubitos[9]->Rotate(kAroundYRight);

          // CUBO 8
          if (rfr_angle_8 > 270.0f) rfr_angle_8 -= 1.0f;
          else rfr_angle_8 = 270.0f;
          rubick_cube.cubitos[8]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rfr_angle_8)),
              0.5f,
              kRadioNormal * sin(deg(rfr_angle_8))));

          rubick_cube.cubitos[8]->Rotate(kAroundYRight);

          // CUBO 7
          if (rfr_angle_7 > -45.0f) rfr_angle_7 -= 1.0f;
          else rfr_angle_7 = -45.0f;
          rubick_cube.cubitos[7]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rfr_angle_7)),
              0.5f,
              kRadioLarge * sin(deg(rfr_angle_7))));

          rubick_cube.cubitos[7]->Rotate(kAroundYRight);

          // CUBO 4
          if (rfr_angle_4 > 0.0f) rfr_angle_4 -= 1.0f;
          else rfr_angle_4 = 0.0f;
          rubick_cube.cubitos[4]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rfr_angle_4)),
              0.5f,
              kRadioNormal * sin(deg(rfr_angle_4))));

          rubick_cube.cubitos[4]->Rotate(kAroundYRight);

          // CUBO 1
          if (rfr_angle_1 > 45.0f) rfr_angle_1 -= 1.0f;
          else rfr_angle_1 = 45.0f;
          rubick_cube.cubitos[1]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rfr_angle_1)),
              0.5f,
              kRadioLarge * sin(deg(rfr_angle_1))));

          rubick_cube.cubitos[1]->Rotate(kAroundYRight);

          // CUBO 2
          if (rfr_angle_2 > 90.0f) rfr_angle_2 -= 1.0f;
          else { rfr_angle_2 = 90.0f; BRF_R_I = false; }
          rubick_cube.cubitos[2]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rfr_angle_2)),
              0.5f,
              kRadioNormal * sin(deg(rfr_angle_2))));

          rubick_cube.cubitos[2]->Rotate(kAroundYRight);

          // CUBO 5
          rubick_cube.cubitos[5]->Rotate(kAroundYRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_3 = rubick_cube.cubitos[3];
          std::shared_ptr<Cubito> new_6 = rubick_cube.cubitos[6];
          std::shared_ptr<Cubito> new_9 = rubick_cube.cubitos[9];
          std::shared_ptr<Cubito> new_2 = rubick_cube.cubitos[2];
          std::shared_ptr<Cubito> new_8 = rubick_cube.cubitos[8];
          std::shared_ptr<Cubito> new_1 = rubick_cube.cubitos[1];
          std::shared_ptr<Cubito> new_4 = rubick_cube.cubitos[4];
          std::shared_ptr<Cubito> new_7 = rubick_cube.cubitos[7];
          rubick_cube.cubitos[3] = new_9;
          rubick_cube.cubitos[6] = new_8;
          rubick_cube.cubitos[9] = new_7;
          rubick_cube.cubitos[2] = new_6;
          rubick_cube.cubitos[8] = new_4;
          rubick_cube.cubitos[1] = new_3;
          rubick_cube.cubitos[4] = new_2;
          rubick_cube.cubitos[7] = new_1;

          rfr_angle_3 = 224.0f;
          rfr_angle_6 = 269.0f;
          rfr_angle_9 = 314.0f;
          rfr_angle_2 = 179.0f;
          rfr_angle_8 = 359.0f;
          rfr_angle_1 = 134.0f;
          rfr_angle_4 = 89.0f;
          rfr_angle_7 = 44.0f;

          BRF_R = false;
          if (DEBUG) {
            rubick_cube.cubitos[3]->MyData();
            rubick_cube.cubitos[6]->MyData();
            rubick_cube.cubitos[9]->MyData();
            rubick_cube.cubitos[2]->MyData();
            rubick_cube.cubitos[8]->MyData();
            rubick_cube.cubitos[1]->MyData();
            rubick_cube.cubitos[4]->MyData();
            rubick_cube.cubitos[7]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL ROW SECOND LEFT
      if (BRS_L) {
        if (BRS_L_I) {
          // CUBO 12
          if (rsl_angle_12 < 315.0f) rsl_angle_12 += 1.0f;
          else rsl_angle_12 = 315.0f;
          rubick_cube.cubitos[12]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsl_angle_12)),
              0.0f,
              kRadioLarge * sin(deg(rsl_angle_12))));

          rubick_cube.cubitos[12]->Rotate(kAroundYLeft);

          // CUBO 15
          if (rsl_angle_15 < 360.0f) rsl_angle_15 += 1.0f;
          else rsl_angle_15 = 360.0f;
          rubick_cube.cubitos[15]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsl_angle_15)),
              0.0f,
              kRadioNormal * sin(deg(rsl_angle_15))));

          rubick_cube.cubitos[15]->Rotate(kAroundYLeft);

          // CUBO 18
          if (rsl_angle_18 < 45.0f) rsl_angle_18 += 1.0f;
          else rsl_angle_18 = 45.0f;
          rubick_cube.cubitos[18]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsl_angle_18)),
              0.0f,
              kRadioLarge * sin(deg(rsl_angle_18))));

          rubick_cube.cubitos[18]->Rotate(kAroundYLeft);

          // CUBO 17
          if (rsl_angle_17 < 90.0f) rsl_angle_17 += 1.0f;
          else rsl_angle_17 = 90.0f;
          rubick_cube.cubitos[17]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsl_angle_17)),
              0.0f,
              kRadioNormal * sin(deg(rsl_angle_17))));

          rubick_cube.cubitos[17]->Rotate(kAroundYLeft);

          // CUBO 16
          if (rsl_angle_16 < 135.0f) rsl_angle_16 += 1.0f;
          else rsl_angle_16 = 135.0f;
          rubick_cube.cubitos[16]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsl_angle_16)),
              0.0f,
              kRadioLarge * sin(deg(rsl_angle_16))));

          rubick_cube.cubitos[16]->Rotate(kAroundYLeft);

          // CUBO 13
          if (rsl_angle_13 < 180.0f) rsl_angle_13 += 1.0f;
          else rsl_angle_13 = 180.0f;
          rubick_cube.cubitos[13]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsl_angle_13)),
              0.0f,
              kRadioNormal * sin(deg(rsl_angle_13))));

          rubick_cube.cubitos[13]->Rotate(kAroundYLeft);

          // CUBO 10
          if (rsl_angle_10 < 225.0f) rsl_angle_10 += 1.0f;
          else rsl_angle_10 = 225.0f;
          rubick_cube.cubitos[10]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsl_angle_10)),
              0.0f,
              kRadioLarge * sin(deg(rsl_angle_10))));

          rubick_cube.cubitos[10]->Rotate(kAroundYLeft);

          // CUBO 11
          if (rsl_angle_11 < 270.0f) rsl_angle_11 += 1.0f;
          else { rsl_angle_11 = 270.0f; BRS_L_I = false; }
          rubick_cube.cubitos[11]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsl_angle_11)),
              0.0f,
              kRadioNormal * sin(deg(rsl_angle_11))));

          rubick_cube.cubitos[11]->Rotate(kAroundYLeft);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundYLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_12 = rubick_cube.cubitos[12];
          std::shared_ptr<Cubito> new_15 = rubick_cube.cubitos[15];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_11 = rubick_cube.cubitos[11];
          std::shared_ptr<Cubito> new_17 = rubick_cube.cubitos[17];
          std::shared_ptr<Cubito> new_10 = rubick_cube.cubitos[10];
          std::shared_ptr<Cubito> new_13 = rubick_cube.cubitos[13];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          rubick_cube.cubitos[12] = new_10;
          rubick_cube.cubitos[15] = new_11;
          rubick_cube.cubitos[18] = new_12;
          rubick_cube.cubitos[11] = new_13;
          rubick_cube.cubitos[17] = new_15;
          rubick_cube.cubitos[10] = new_16;
          rubick_cube.cubitos[13] = new_17;
          rubick_cube.cubitos[16] = new_18;

          rsl_angle_12 = 226.0f;
          rsl_angle_15 = 271.0f;
          rsl_angle_18 = -44.0f;
          rsl_angle_11 = 181.0f;
          rsl_angle_17 = 1.0f;
          rsl_angle_10 = 136.0f;
          rsl_angle_13 = 91.0f;
          rsl_angle_16 = 46.0f;

          BRS_L = false;
          if (DEBUG) {
            rubick_cube.cubitos[12]->MyData();
            rubick_cube.cubitos[15]->MyData();
            rubick_cube.cubitos[18]->MyData();
            rubick_cube.cubitos[11]->MyData();
            rubick_cube.cubitos[14]->MyData();
            rubick_cube.cubitos[17]->MyData();
            rubick_cube.cubitos[10]->MyData();
            rubick_cube.cubitos[13]->MyData();
            rubick_cube.cubitos[16]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL ROW SECOND RIGHT
      if (BRS_R) {
        if (BRS_R_I) {
          // CUBO 12
          if (rsr_angle_12 > 135.0f) rsr_angle_12 -= 1.0f;
          else rsr_angle_12 = 135.0f;
          rubick_cube.cubitos[12]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsr_angle_12)),
              0.0f,
              kRadioLarge * sin(deg(rsr_angle_12))));

          rubick_cube.cubitos[12]->Rotate(kAroundYRight);

          // CUBO 15
          if (rsr_angle_15 > 180.0f) rsr_angle_15 -= 1.0f;
          else rsr_angle_15 = 180.0f;
          rubick_cube.cubitos[15]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsr_angle_15)),
              0.0f,
              kRadioNormal * sin(deg(rsr_angle_15))));

          rubick_cube.cubitos[15]->Rotate(kAroundYRight);

          // CUBO 18
          if (rsr_angle_18 > 225.0f) rsr_angle_18 -= 1.0f;
          else rsr_angle_18 = 225.0f;
          rubick_cube.cubitos[18]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsr_angle_18)),
              0.0f,
              kRadioLarge * sin(deg(rsr_angle_18))));

          rubick_cube.cubitos[18]->Rotate(kAroundYRight);

          // CUBO 17
          if (rsr_angle_17 > 270.0f) rsr_angle_17 -= 1.0f;
          else rsr_angle_17 = 270.0f;
          rubick_cube.cubitos[17]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsr_angle_17)),
              0.0f,
              kRadioNormal * sin(deg(rsr_angle_17))));

          rubick_cube.cubitos[17]->Rotate(kAroundYRight);

          // CUBO 16
          if (rsr_angle_16 > -45.0f) rsr_angle_16 -= 1.0f;
          else rsr_angle_16 = -45.0f;
          rubick_cube.cubitos[16]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsr_angle_16)),
              0.0f,
              kRadioLarge * sin(deg(rsr_angle_16))));

          rubick_cube.cubitos[16]->Rotate(kAroundYRight);

          // CUBO 13
          if (rsr_angle_13 > 0.0f) rsr_angle_13 -= 1.0f;
          else rsr_angle_13 = 0.0f;
          rubick_cube.cubitos[13]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsr_angle_13)),
              0.0f,
              kRadioNormal * sin(deg(rsr_angle_13))));

          rubick_cube.cubitos[13]->Rotate(kAroundYRight);

          // CUBO 10
          if (rsr_angle_10 > 45.0f) rsr_angle_10 -= 1.0f;
          else rsr_angle_10 = 45.0f;
          rubick_cube.cubitos[10]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rsr_angle_10)),
              0.0f,
              kRadioLarge * sin(deg(rsr_angle_10))));

          rubick_cube.cubitos[10]->Rotate(kAroundYRight);

          // CUBO 11
          if (rsr_angle_11 > 90.0f) rsr_angle_11 -= 1.0f;
          else { rsr_angle_11 = 90.0f; BRS_R_I = false; }
          rubick_cube.cubitos[11]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rsr_angle_11)),
              0.0f,
              kRadioNormal * sin(deg(rsr_angle_11))));

          rubick_cube.cubitos[11]->Rotate(kAroundYRight);

          // CUBO 14
          rubick_cube.cubitos[14]->Rotate(kAroundYRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_12 = rubick_cube.cubitos[12];
          std::shared_ptr<Cubito> new_15 = rubick_cube.cubitos[15];
          std::shared_ptr<Cubito> new_18 = rubick_cube.cubitos[18];
          std::shared_ptr<Cubito> new_11 = rubick_cube.cubitos[11];
          std::shared_ptr<Cubito> new_17 = rubick_cube.cubitos[17];
          std::shared_ptr<Cubito> new_10 = rubick_cube.cubitos[10];
          std::shared_ptr<Cubito> new_13 = rubick_cube.cubitos[13];
          std::shared_ptr<Cubito> new_16 = rubick_cube.cubitos[16];
          rubick_cube.cubitos[12] = new_18;
          rubick_cube.cubitos[15] = new_17;
          rubick_cube.cubitos[18] = new_16;
          rubick_cube.cubitos[11] = new_15;
          rubick_cube.cubitos[17] = new_13;
          rubick_cube.cubitos[10] = new_12;
          rubick_cube.cubitos[13] = new_11;
          rubick_cube.cubitos[16] = new_10;

          rsr_angle_12 = 224.0f;
          rsr_angle_15 = 269.0f;
          rsr_angle_18 = 314.0f;
          rsr_angle_11 = 179.0f;
          rsr_angle_17 = 359.0f;
          rsr_angle_10 = 134.0f;
          rsr_angle_13 = 89.0f;
          rsr_angle_16 = 44.0f;

          BRS_R = false;
          if (DEBUG) {
            rubick_cube.cubitos[12]->MyData();
            rubick_cube.cubitos[15]->MyData();
            rubick_cube.cubitos[18]->MyData();
            rubick_cube.cubitos[11]->MyData();
            rubick_cube.cubitos[14]->MyData();
            rubick_cube.cubitos[17]->MyData();
            rubick_cube.cubitos[10]->MyData();
            rubick_cube.cubitos[13]->MyData();
            rubick_cube.cubitos[16]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL ROW THIRD LEFT
      if (BRT_L) {
        if (BRT_L_I) {
          // CUBO 21
          if (rtl_angle_21 < 315.0f) rtl_angle_21 += 1.0f;
          else rtl_angle_21 = 315.0f;
          rubick_cube.cubitos[21]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtl_angle_21)),
              -0.5f,
              kRadioLarge * sin(deg(rtl_angle_21))));

          rubick_cube.cubitos[21]->Rotate(kAroundYLeft);

          // CUBO 24
          if (rtl_angle_24 < 360.0f) rtl_angle_24 += 1.0f;
          else rtl_angle_24 = 360.0f;
          rubick_cube.cubitos[24]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtl_angle_24)),
              -0.5f,
              kRadioNormal * sin(deg(rtl_angle_24))));

          rubick_cube.cubitos[24]->Rotate(kAroundYLeft);

          // CUBO 27
          if (rtl_angle_27 < 45.0f) rtl_angle_27 += 1.0f;
          else rtl_angle_27 = 45.0f;
          rubick_cube.cubitos[27]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtl_angle_27)),
              -0.5f,
              kRadioLarge * sin(deg(rtl_angle_27))));

          rubick_cube.cubitos[27]->Rotate(kAroundYLeft);

          // CUBO 26
          if (rtl_angle_26 < 90.0f) rtl_angle_26 += 1.0f;
          else rtl_angle_26 = 90.0f;
          rubick_cube.cubitos[26]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtl_angle_26)),
              -0.5f,
              kRadioNormal * sin(deg(rtl_angle_26))));

          rubick_cube.cubitos[26]->Rotate(kAroundYLeft);

          // CUBO 25
          if (rtl_angle_25 < 135.0f) rtl_angle_25 += 1.0f;
          else rtl_angle_25 = 135.0f;
          rubick_cube.cubitos[25]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtl_angle_25)),
              -0.5f,
              kRadioLarge * sin(deg(rtl_angle_25))));

          rubick_cube.cubitos[25]->Rotate(kAroundYLeft);

          // CUBO 22
          if (rtl_angle_22 < 180.0f) rtl_angle_22 += 1.0f;
          else rtl_angle_22 = 180.0f;
          rubick_cube.cubitos[22]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtl_angle_22)),
              -0.5f,
              kRadioNormal * sin(deg(rtl_angle_22))));

          rubick_cube.cubitos[22]->Rotate(kAroundYLeft);

          // CUBO 19
          if (rtl_angle_19 < 225.0f) rtl_angle_19 += 1.0f;
          else rtl_angle_19 = 225.0f;
          rubick_cube.cubitos[19]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtl_angle_19)),
              -0.5f,
              kRadioLarge * sin(deg(rtl_angle_19))));

          rubick_cube.cubitos[19]->Rotate(kAroundYLeft);

          // CUBO 20
          if (rtl_angle_20 < 270.0f) rtl_angle_20 += 1.0f;
          else { rtl_angle_20 = 270.0f; BRT_L_I = false; }
          rubick_cube.cubitos[20]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtl_angle_20)),
              -0.5f,
              kRadioNormal * sin(deg(rtl_angle_20))));

          rubick_cube.cubitos[20]->Rotate(kAroundYLeft);

          // CUBO 23
          rubick_cube.cubitos[23]->Rotate(kAroundYLeft);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_21 = rubick_cube.cubitos[21];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          std::shared_ptr<Cubito> new_20 = rubick_cube.cubitos[20];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          std::shared_ptr<Cubito> new_19 = rubick_cube.cubitos[19];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[21] = new_19;
          rubick_cube.cubitos[24] = new_20;
          rubick_cube.cubitos[27] = new_21;
          rubick_cube.cubitos[20] = new_22;
          rubick_cube.cubitos[26] = new_24;
          rubick_cube.cubitos[19] = new_25;
          rubick_cube.cubitos[22] = new_26;
          rubick_cube.cubitos[25] = new_27;

          rtl_angle_21 = 226.0f;
          rtl_angle_24 = 271.0f;
          rtl_angle_27 = -44.0f;
          rtl_angle_20 = 181.0f;
          rtl_angle_26 = 1.0f;
          rtl_angle_19 = 136.0f;
          rtl_angle_22 = 91.0f;
          rtl_angle_25 = 46.0f;

          BRT_L = false;
          if (DEBUG) {
            rubick_cube.cubitos[21]->MyData();
            rubick_cube.cubitos[24]->MyData();
            rubick_cube.cubitos[27]->MyData();
            rubick_cube.cubitos[20]->MyData();
            rubick_cube.cubitos[23]->MyData();
            rubick_cube.cubitos[26]->MyData();
            rubick_cube.cubitos[19]->MyData();
            rubick_cube.cubitos[22]->MyData();
            rubick_cube.cubitos[25]->MyData();
            std::cout << std::endl;
          }
        }
      }

      // BOOL ROW THIRD RIGHT
      if (BRT_R) {
        if (BRT_R_I) {
          // CUBO 21
          if (rtr_angle_21 > 135.0f) rtr_angle_21 -= 1.0f;
          else rtr_angle_21 = 135.0f;
          rubick_cube.cubitos[21]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtr_angle_21)),
              -0.5f,
              kRadioLarge * sin(deg(rtr_angle_21))));

          rubick_cube.cubitos[21]->Rotate(kAroundYRight);

          // CUBO 24
          if (rtr_angle_24 > 180.0f) rtr_angle_24 -= 1.0f;
          else rtr_angle_24 = 180.0f;
          rubick_cube.cubitos[24]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtr_angle_24)),
              -0.5f,
              kRadioNormal * sin(deg(rtr_angle_24))));

          rubick_cube.cubitos[24]->Rotate(kAroundYRight);

          // CUBO 27
          if (rtr_angle_27 > 225.0f) rtr_angle_27 -= 1.0f;
          else rtr_angle_27 = 225.0f;
          rubick_cube.cubitos[27]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtr_angle_27)),
              -0.5f,
              kRadioLarge * sin(deg(rtr_angle_27))));

          rubick_cube.cubitos[27]->Rotate(kAroundYRight);

          // CUBO 26
          if (rtr_angle_26 > 270.0f) rtr_angle_26 -= 1.0f;
          else rtr_angle_26 = 270.0f;
          rubick_cube.cubitos[26]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtr_angle_26)),
              -0.5f,
              kRadioNormal * sin(deg(rtr_angle_26))));

          rubick_cube.cubitos[26]->Rotate(kAroundYRight);

          // CUBO 25
          if (rtr_angle_25 > -45.0f) rtr_angle_25 -= 1.0f;
          else rtr_angle_25 = -45.0f;
          rubick_cube.cubitos[25]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtr_angle_25)),
              -0.5f,
              kRadioLarge * sin(deg(rtr_angle_25))));

          rubick_cube.cubitos[25]->Rotate(kAroundYRight);

          // CUBO 22
          if (rtr_angle_22 > 0.0f) rtr_angle_22 -= 1.0f;
          else rtr_angle_22 = 0.0f;
          rubick_cube.cubitos[22]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtr_angle_22)),
              -0.5f,
              kRadioNormal * sin(deg(rtr_angle_22))));

          rubick_cube.cubitos[22]->Rotate(kAroundYRight);

          // CUBO 19
          if (rtr_angle_19 > 45.0f) rtr_angle_19 -= 1.0f;
          else rtr_angle_19 = 45.0f;
          rubick_cube.cubitos[19]->
            Translate(glm::vec3(kRadioLarge * cos(deg(rtr_angle_19)),
              -0.5f,
              kRadioLarge * sin(deg(rtr_angle_19))));

          rubick_cube.cubitos[19]->Rotate(kAroundYRight);

          // CUBO 20
          if (rtr_angle_20 > 90.0f) rtr_angle_20 -= 1.0f;
          else { rtr_angle_20 = 90.0f; BRT_R_I = false; }
          rubick_cube.cubitos[20]->
            Translate(glm::vec3(kRadioNormal * cos(deg(rtr_angle_20)),
              -0.5f,
              kRadioNormal * sin(deg(rtr_angle_20))));

          rubick_cube.cubitos[20]->Rotate(kAroundYRight);

          // CUBO 23
          rubick_cube.cubitos[23]->Rotate(kAroundYRight);
        }
        // REASIGN POINTER
        else {
          std::shared_ptr<Cubito> new_21 = rubick_cube.cubitos[21];
          std::shared_ptr<Cubito> new_24 = rubick_cube.cubitos[24];
          std::shared_ptr<Cubito> new_27 = rubick_cube.cubitos[27];
          std::shared_ptr<Cubito> new_20 = rubick_cube.cubitos[20];
          std::shared_ptr<Cubito> new_26 = rubick_cube.cubitos[26];
          std::shared_ptr<Cubito> new_19 = rubick_cube.cubitos[19];
          std::shared_ptr<Cubito> new_22 = rubick_cube.cubitos[22];
          std::shared_ptr<Cubito> new_25 = rubick_cube.cubitos[25];
          rubick_cube.cubitos[21] = new_27;
          rubick_cube.cubitos[24] = new_26;
          rubick_cube.cubitos[27] = new_25;
          rubick_cube.cubitos[20] = new_24;
          rubick_cube.cubitos[26] = new_22;
          rubick_cube.cubitos[19] = new_21;
          rubick_cube.cubitos[22] = new_20;
          rubick_cube.cubitos[25] = new_19;

          rtr_angle_21 = 224.0f;
          rtr_angle_24 = 269.0f;
          rtr_angle_27 = 314.0f;
          rtr_angle_20 = 179.0f;
          rtr_angle_26 = 359.0f;
          rtr_angle_19 = 134.0f;
          rtr_angle_22 = 89.0f;
          rtr_angle_25 = 44.0f;

          BRT_R = false;
          if (DEBUG) {
            rubick_cube.cubitos[21]->MyData();
            rubick_cube.cubitos[24]->MyData();
            rubick_cube.cubitos[27]->MyData();
            rubick_cube.cubitos[20]->MyData();
            rubick_cube.cubitos[23]->MyData();
            rubick_cube.cubitos[26]->MyData();
            rubick_cube.cubitos[19]->MyData();
            rubick_cube.cubitos[22]->MyData();
            rubick_cube.cubitos[25]->MyData();
            std::cout << std::endl;
          }
        }
      }
    }
    
    // PRINT RUBICK CUBE
    rubick_cube.Draw(model, view, projection);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    BRF_R = true;
    BRF_R_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    BRS_L = true;
    BRS_L_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    BRS_R = true;
    BRS_R_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
    BRT_L = true;
    BRT_L_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
    BRT_R = true;
    BRT_R_I = true;
    some_movement = true;
  }

  // COLUMNS MOVEMENTS

  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
    BCM_U = true;
    BCM_U_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
    BCM_D = true;
    BCM_D_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
    BCR_U = true;
    BCR_U_I = true;
    some_movement = true;
  }

  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
    BCR_D = true;
    BCR_D_I = true;
    some_movement = true;
  }

  // Standard movements
  if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
      F_L = true;
      F_L_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
      B_R = true;
      B_R_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
      BCL_U = true;
      BCL_U_I = true;
      some_movement = true;
    }
  }
  else {
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
      B_L = true;
      B_L_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
      F_R = true;
      F_R_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
      BCL_D = true;
      BCL_D_I = true;
      some_movement = true;
    }
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

float back_front_move_angles[8] = {
  135.0f,
  90.0f,
  45.0f,
  180.0f,
  0.0f,
  225.0f,
  270.0f,
  315.0f,
};

float angles_prime_limit[8] = {
  225.0f,
  180.0f,
  135.0f,
  270.0f,
  90.0f,
  315.0f,
  360.0f,
  405.0f,
};

float angles_normal_limit[8] = {
  45.0f,
  0.0f,
  -45.0f,
  90.0f,
  -90.0f,
  135.0f,
  180.0f,
  225.0f,
};

void ResetBackFrontAngles() {
  back_front_move_angles[0] = 135.0f;
  back_front_move_angles[1] = 90.0f;
  back_front_move_angles[2] = 45.0f;
  back_front_move_angles[3] = 180.0f;
  back_front_move_angles[4] = 0.0f;
  back_front_move_angles[5] = 225.0f;
  back_front_move_angles[6] = 270.0f;
  back_front_move_angles[7] = 315.0f;
}

glm::vec3 CalculateTranslatePosition(float angle, Move m, const float& radius) {
  switch (m) {
    case L:
    case LP:
      return glm::vec3(-0.5f,
                       radius * sin(deg(angle)),
                       radius * cos(deg(angle)));
      break;

    case F:
    case FP:
      return glm::vec3(radius * cos(deg(angle)),
                       radius * sin(deg(angle)),
                       0.5f);
      break;

    case B:
    case BP:
      return glm::vec3(radius * cos(deg(angle)),
                       radius * sin(deg(angle)),
                       -0.5f);
      break;
  }
}

void ParallelAnimation() {
  std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;
  float* angles = back_front_move_angles;
  float* angles_limit;
  float step;
  int clockwise;
  Move current_move;
  int normalMove = 1;

  if (F_R_I) {
    current_move = F;
    clockwise = 1;
    normalMove = 3;
    angles_limit = angles_normal_limit;
    step = -1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_R_I) {
    current_move = B;
    clockwise = 1;
    normalMove = 3;
    angles_limit = angles_normal_limit;
    step = -1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (F_L_I) {
    current_move = FP;
    clockwise = -1;
    normalMove = 3;
    angles_limit = angles_prime_limit;
    step = 1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_L_I) {
    current_move = BP;
    clockwise = -1;
    normalMove = 3;
    angles_limit = angles_prime_limit;
    step = 1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (BCL_D_I) {
    current_move = L;
    clockwise = 1;
    normalMove = -1;
    angles_limit = angles_normal_limit;
    step = -1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (BCL_U_I) {
    current_move = LP;
    clockwise = -1;
    normalMove = -1;
    angles_limit = angles_prime_limit;
    step = 1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }

  // CUBO 01
  if (std::abs(angles_limit[0] - angles[0]) > 0.5f) angles[0] += step;
  else {
    angles[0] = angles_limit[0];
    cubitos[0].get()->Rotate(normalMove * clockwise);
  }

  cubitos[0].get()->SetPosition(CalculateTranslatePosition(angles[0],
                                current_move, kRadioLarge));

  cubitos[0].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 04
  if (std::abs(angles_limit[1] - angles[1]) > 0.5f) angles[1] += step;
  else {
    angles[1] = angles_limit[1];
    cubitos[1].get()->Rotate(normalMove * clockwise);
  }

  cubitos[1].get()->SetPosition(CalculateTranslatePosition(angles[1],
                                current_move, kRadioNormal));

  cubitos[1].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 07
  if (std::abs(angles_limit[2] - angles[2]) > 0.5f) angles[2] += step;
  else {
    angles[2] = angles_limit[2];
    cubitos[2].get()->Rotate(normalMove * clockwise);
  }

  cubitos[2].get()->SetPosition(CalculateTranslatePosition(angles[2],
                                current_move, kRadioLarge));

  cubitos[2].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 10
  if (std::abs(angles_limit[3] - angles[3]) > 0.5f) angles[3] += step;
  else {
    angles[3] = angles_limit[3];
    cubitos[3].get()->Rotate(normalMove * clockwise);
    cubitos[4].get()->Rotate(normalMove * clockwise);
  }

  cubitos[3].get()->SetPosition(CalculateTranslatePosition(angles[3],
                                current_move, kRadioNormal));

  cubitos[3].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 13
  cubitos[4].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 16
  if (std::abs(angles_limit[4] - angles[4]) > 0.5f) angles[4] += step;
  else {
    angles[4] = angles_limit[4];
    cubitos[5].get()->Rotate(normalMove * clockwise);
  }

  cubitos[5].get()->SetPosition(CalculateTranslatePosition(angles[4],
                                current_move, kRadioNormal));

  cubitos[5].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 19
  if (std::abs(angles_limit[5] - angles[5]) > 0.5f) angles[5] += step;
  else {
    angles[5] = angles_limit[5];
    cubitos[6].get()->Rotate(normalMove * clockwise);
  }

  cubitos[6].get()->SetPosition(CalculateTranslatePosition(angles[5],
                                current_move, kRadioLarge));

  cubitos[6].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 22
  if (std::abs(angles_limit[6] - angles[6]) > 0.5f) angles[6] += step;
  else {
    angles[6] = angles_limit[6];
    cubitos[7].get()->Rotate(normalMove * clockwise);
  }

  cubitos[7].get()->SetPosition(CalculateTranslatePosition(angles[6],
                                current_move, kRadioNormal));

  cubitos[7].get()->Rotate(normalMove * -1 * clockwise);

  // CUBO 25
  if (std::abs(angles_limit[7] - angles[7]) > 0.5f) angles[7] += step;
  else {
    angles[7] = angles_limit[7];
    cubitos[8].get()->Rotate(normalMove * clockwise);
    F_R_I = false;
    B_R_I = false;
    F_L_I = false;
    B_L_I = false;
    BCL_D_I = false;
    BCL_U_I = false;
  }

  cubitos[8].get()->SetPosition(CalculateTranslatePosition(angles[7],
                                current_move, kRadioLarge));

  cubitos[8].get()->Rotate(normalMove * -1 * clockwise);

  // REASIGN POINTER
  if ((B_R && !B_R_I) || (F_R && !F_R_I)
      || (B_L && !B_L_I) || (F_L && !F_L_I)
      || (BCL_D && !BCL_D_I) || (BCL_U && !BCL_U_I)) {
    if (clockwise > 0) {
      auto temp = cubitos[0].get();
      cubitos[0].get() = cubitos[6].get();
      cubitos[6].get() = cubitos[8].get();
      cubitos[8].get() = cubitos[2].get();
      cubitos[2].get() = temp;

      temp = cubitos[1].get();
      cubitos[1].get() = cubitos[3].get();
      cubitos[3].get() = cubitos[7].get();
      cubitos[7].get() = cubitos[5].get();
      cubitos[5].get() = temp;
    }
    else {
      auto temp = cubitos[0].get();
      cubitos[0].get() = cubitos[2].get();
      cubitos[2].get() = cubitos[8].get();
      cubitos[8].get() = cubitos[6].get();
      cubitos[6].get() = temp;

      temp = cubitos[1].get();
      cubitos[1].get() = cubitos[5].get();
      cubitos[5].get() = cubitos[7].get();
      cubitos[7].get() = cubitos[3].get();
      cubitos[3].get() = temp;
    }

    ResetBackFrontAngles();

    B_R = false;
    F_R = false;
    B_L = false;
    F_L = false;
    BCL_D = false;
    BCL_U = false;
  }
}
