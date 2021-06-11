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

bool type_of_move = false;

// Movements of each cubito first face

bool first_face = false;
bool xxx = false;

float angle_1 = 134.0f;
float rota_1 = 0.0f;
float rad_1 = 0.5f*sqrt(2);

float angle_4 = 89.0f;
float rota_4 = 0.0f;
float rad_4 = 0.5f;

float angle_7 = 44.0f;
float rota_7 = 0.0f;
float rad_7 = 0.5f * sqrt(2);

float angle_16 = -1.0f;
float rota_16 = 0.0f;
float rad_16 = 0.5f;

float angle_25 = 314.0f;
float rota_25 = 0.0f;
float rad_25 = 0.5f * sqrt(2);

float angle_22 = 269.0f;
float rota_22 = 0.0f;
float rad_22 = 0.5f;

float angle_19 = 224.0f;
float rota_19 = 0.0f;
float rad_19 = 0.5f * sqrt(2);

float angle_10 = 179.0f;
float rota_10 = 0.0f;
float rad_10 = 0.5f;

float rota_13 = 0.0f;

int main() {
  // ----- Test solver --- //

  std::string solution = rubik::solve("R' F U' D2 R F R' L2 F' B2 U' F2 B' R2 B D2 B' U2 R2");
  std::cout << "Solution: " << solution << std::endl;

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
  int a = 1;
  // MAIN AND EACH CUBE
  {
    rubick_cube.cubitos[3] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, 0.0f), 3, input_colors[20], input_colors[9],
      input_colors[0]);
    rubick_cube.cubitos[6] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, 0.0f), 6, input_colors[19], input_colors[1]);
    rubick_cube.cubitos[9] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, 0.0f), 9, input_colors[18], input_colors[17],
      input_colors[2]);
    rubick_cube.cubitos[12] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, 0.0f), 12, input_colors[32], input_colors[21]);
    rubick_cube.cubitos[15] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, 0.0f), 15, input_colors[31]);
    rubick_cube.cubitos[18] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, 0.0f), 18, input_colors[30], input_colors[29]);
    rubick_cube.cubitos[21] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, 0.0f), 21, input_colors[44], input_colors[33],
      input_colors[51]);
    rubick_cube.cubitos[24] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, 0.0f), 24, input_colors[43], input_colors[52]);
    rubick_cube.cubitos[27] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, 0.0f), 27, input_colors[42], input_colors[41],
      input_colors[53]);

    rubick_cube.cubitos[2] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, 0.5f), 2, input_colors[10], input_colors[3]);
    rubick_cube.cubitos[5] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, 0.5f), 5, input_colors[4]);
    rubick_cube.cubitos[8] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, 0.5f), 8, input_colors[16], input_colors[5]);
    rubick_cube.cubitos[11] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, 0.5f), 11, input_colors[22]);
    rubick_cube.cubitos[14] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, 0.5f), 14);
    rubick_cube.cubitos[17] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, 0.5f), 17, input_colors[28]);
    rubick_cube.cubitos[20] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, 0.5f), 20, input_colors[34], input_colors[48]);
    rubick_cube.cubitos[23] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, 0.5f), 23, input_colors[49]);
    rubick_cube.cubitos[26] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, 0.5f), 26, input_colors[40], input_colors[50]);

    rubick_cube.cubitos[1] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.5f, 1.0f), 1, input_colors[12], input_colors[11],
      input_colors[6]);
    rubick_cube.cubitos[4] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.5f, 1.0f), 4, input_colors[13], input_colors[7]);
    rubick_cube.cubitos[7] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.5f, 1.0f), 7, input_colors[14], input_colors[15],
      input_colors[8]);
    rubick_cube.cubitos[10] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, 0.0f, 1.0f), 10, input_colors[24], input_colors[23]);
    rubick_cube.cubitos[13] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, 0.0f, 1.0f), 13, input_colors[25]);
    rubick_cube.cubitos[16] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, 0.0f, 1.0f), 16, input_colors[26], input_colors[27]);
    rubick_cube.cubitos[19] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(-0.5f, -0.5f, 1.0f), 19, input_colors[36], input_colors[35],
      input_colors[45]);
    rubick_cube.cubitos[22] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.0f, -0.5f, 1.0f), 22, input_colors[37], input_colors[46]);
    rubick_cube.cubitos[25] = std::make_shared<Cubito>(cubito_program,
      glm::vec3(0.5f, -0.5f, 1.0f), 25, input_colors[38], input_colors[39],
      input_colors[47]);
  }
  
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

    if (type_of_move) {
      if (xxx) {
        if (first_face) {
          std::cout << "aa " << a++ << std::endl;
          // CUBO 01
          if (angle_1 > 45.0f) angle_1 -= 1.0f;
          else angle_1 = 45.0f;
          rubick_cube.cubitos[1]->Translate(glm::vec3(rad_1 * cos(deg(angle_1)), rad_1 * sin(deg(angle_1)), 1.0f));
          
          if (rota_1 > -90) rota_1 -= 1.0f;
          else rota_1 = -90.0f;
          rubick_cube.cubitos[1]->Rotate(rota_1, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 04
          if (angle_4 > 0.0f) angle_4 -= 1.0f;
          else angle_4 = 0.0f;
          rubick_cube.cubitos[4]->Translate(glm::vec3(rad_4 * cos(deg(angle_4)), rad_4 * sin(deg(angle_4)), 1.0f));

          if (rota_4 > -90) rota_4 -= 1.0f;
          else rota_4 = -90.0f;
          rubick_cube.cubitos[4]->Rotate(rota_4, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 07
          if (angle_7 > -45.0f) angle_7 -= 1.0f;
          else angle_7 = -45.0f;
          rubick_cube.cubitos[7]->Translate(glm::vec3(rad_7 * cos(deg(angle_7)), rad_7 * sin(deg(angle_7)), 1.0f));

          if (rota_7 > -90) { rota_7 -= 1.0f; }
          else rota_7 = -90.0f;
          rubick_cube.cubitos[7]->Rotate(rota_7, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 16
          if (angle_16 > -90.0f) angle_16 -= 1.0f;
          else angle_16 = -90.0f;
          rubick_cube.cubitos[16]->Translate(glm::vec3(rad_16 * cos(deg(angle_16)), rad_16 * sin(deg(angle_16)), 1.0f));

          if (rota_16 > -90) rota_16 -= 1.0f;
          else rota_16 = -90.0f;
          rubick_cube.cubitos[16]->Rotate(rota_16, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 25
          if (angle_25 > 225.0f) angle_25 -= 1.0f;
          else angle_25 = 225.0f;
          rubick_cube.cubitos[25]->Translate(glm::vec3(rad_25 * cos(deg(angle_25)), rad_25 * sin(deg(angle_25)), 1.0f));

          if (rota_25 > -90) rota_25 -= 1.0f;
          else rota_25 = -90.0f;
          rubick_cube.cubitos[25]->Rotate(rota_25, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 22
          if (angle_22 > 180.0f) angle_22 -= 1.0f;
          else angle_22 = 180.0f;
          rubick_cube.cubitos[22]->Translate(glm::vec3(rad_22 * cos(deg(angle_22)), rad_22 * sin(deg(angle_22)), 1.0f));

          if (rota_22 > -90) rota_22 -= 1.0f;
          else rota_22 = -90.0f;
          rubick_cube.cubitos[22]->Rotate(rota_22, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 19
          if (angle_19 > 135.0f) angle_19 -= 1.0f;
          else angle_19 = 135.0f;
          rubick_cube.cubitos[19]->Translate(glm::vec3(rad_19 * cos(deg(angle_19)), rad_19 * sin(deg(angle_19)), 1.0f));

          if (rota_19 > -90) rota_19 -= 1.0f;
          else rota_19 = -90.0f;
          rubick_cube.cubitos[19]->Rotate(rota_19, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 10
          if (angle_10 > 90.0f) angle_10 -= 1.0f;
          else { angle_10 = 90.0f; first_face = false; }
          rubick_cube.cubitos[10]->Translate(glm::vec3(rad_10 * cos(deg(angle_10)), rad_10 * sin(deg(angle_10)), 1.0f));

          if (rota_10 > -90) rota_10 -= 1.0f;
          else rota_10 = -90.0f;
          rubick_cube.cubitos[10]->Rotate(rota_10, glm::vec3(0.0f, 0.0f, 1.0f));

          // CUBO 13
          if (rota_13 > -90) rota_13 -= 1.0f;
          else rota_13 = -90.0f;
          rubick_cube.cubitos[13]->Rotate(rota_13, glm::vec3(0.0f, 0.0f, 1.0f));
        }
        else {
          std::cout << "finish first_face false" << std::endl;

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

          /*rubick_cube.cubitos[1].swap(rubick_cube.cubitos[19]);
          rubick_cube.cubitos[4].swap(rubick_cube.cubitos[10]);
          rubick_cube.cubitos[7].swap(rubick_cube.cubitos[1]);
          rubick_cube.cubitos[10].swap(rubick_cube.cubitos[22]);
          rubick_cube.cubitos[16].swap(rubick_cube.cubitos[4]);
          rubick_cube.cubitos[19].swap(rubick_cube.cubitos[25]);
          rubick_cube.cubitos[22].swap(rubick_cube.cubitos[16]);
          rubick_cube.cubitos[25].swap(rubick_cube.cubitos[7]);*/

          angle_1 = 134.0f;
          rota_1 = 0.0f;
          rad_1 = 0.5f * sqrt(2);

          angle_4 = 89.0f;
          rota_4 = 0.0f;
          rad_4 = 0.5f;

          angle_7 = 44.0f;
          rota_7 = 0.0f;
          rad_7 = 0.5f * sqrt(2);

          angle_16 = -1.0f;
          rota_16 = 0.0f;
          rad_16 = 0.5f;

          angle_25 = 314.0f;
          rota_25 = 0.0f;
          rad_25 = 0.5f * sqrt(2);

          angle_22 = 269.0f;
          rota_22 = 0.0f;
          rad_22 = 0.5f;

          angle_19 = 224.0f;
          rota_19 = 0.0f;
          rad_19 = 0.5f * sqrt(2);

          angle_10 = 179.0f;
          rota_10 = 0.0f;
          rad_10 = 0.5f;

          rota_13 = 0.0f;
          xxx = false;
        }
      }
      else {
        std::cout << "Not inside xxx" << std::endl;
        type_of_move = false;
      }
    }
    else std::cout << "nothing press" << std::endl;
    
    // Testing one cube
    //rubick_cube.cubitos[1]->DrawSprite(model, view, projection);
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

  if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
    xxx = true;
    first_face = true;
    type_of_move = true;
    //rubick_cube.Move(HU_L);
  }

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    rubick_cube.Move(HU_R);

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    rubick_cube.Move(HM_L);

  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    rubick_cube.Move(HM_R);

  if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    rubick_cube.Move(HD_L);

  if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    rubick_cube.Move(HD_R);

  if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    rubick_cube.Move(VL_U);

  if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    rubick_cube.Move(VL_D);

  if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
    rubick_cube.Move(VM_U);

  if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
    rubick_cube.Move(VM_D);

  if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    rubick_cube.Move(VR_U);

  if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
    rubick_cube.Move(VR_D);
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
