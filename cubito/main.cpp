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


bool U_ANIM = false, U_ANIM_I = false;
bool U_PRIME_ANIM = false, U_PRIME_ANIM_I = false;
bool D_ANIM = false, D_ANIM_I = false;
bool D_PRIME_ANIM = false, D_PRIME_ANIM_I = false;

bool L_PRIME_ANIM = false, L_PRIME_ANIM_I = false;
bool L_ANIM = false, L_ANIM_I = false;
bool R_ANIM = false, R_ANIM_I = false;
bool R_PRIME_ANIM = false, R_PRIME_ANIM_I = false;

bool F_ANIM = false, F_ANIM_I = false;
bool F_PRIME_ANIM = false, F_PRIME_ANIM_I = false;
bool B_ANIM = false, B_ANIM_I = false;
bool B_PRIME_ANIM = false, B_PRIME_ANIM_I = false;

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
void PlayAnimation();

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
const int kAroundYLeft = -2;
const int kAroundYRight = 2;
const int kAroundZLeft = 3;
const int kAroundZRight = -3;

//========================================== VARIABLES FOR MOVEMENTS

bool some_movement = false;
const float kRadioLarge = 0.5f * sqrt(2);
const float kRadioNormal = 0.5f;

void PrintCommands() {
  std::cout << "\t\tWELCOME TO CUBITO MOSQUETERO\n";
  std::cout << "\t\t     CONTROLS TO PLAY\n\n";

  std::cout << "\tU: U\n";
  std::cout << "\tShift + U: U'\n";
  std::cout << "\tD: D\n";
  std::cout << "\tShift + D: D'\n";
  std::cout << "\tR: R\n";
  std::cout << "\tShift + R: R'\n";
  std::cout << "\tL: L\n";
  std::cout << "\tShift + L: L'\n";
  std::cout << "\tF: F\n";
  std::cout << "\tShift + F: F'\n";
  std::cout << "\tB: B\n";
  std::cout << "\tShift + B: B'" << std::endl;
}

int main() {
  // ----- Test solver --- //

  // std::string solution = rubik::solve("R' F U' D2 R F R' L2 F' B2 U' F2 B' R2 B D2 B' U2 R2");
  // std::cout << "Solution: " << solution << std::endl;

  // ----- Test solver --- //

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Coordinate System", NULL, NULL);

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
  
  PrintCommands();

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
      PlayAnimation();
    }
    
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

  // Standard rubik's cube movements
  if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ||
      glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
      U_PRIME_ANIM = true;
      U_PRIME_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      D_PRIME_ANIM = true;
      D_PRIME_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      R_ANIM = true;
      R_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
      L_PRIME_ANIM = true;
      L_PRIME_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
      F_PRIME_ANIM = true;
      F_PRIME_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
      B_ANIM = true;
      B_ANIM_I = true;
      some_movement = true;
    }
  }
  else {
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
      U_ANIM = true;
      U_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      D_ANIM = true;
      D_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      R_PRIME_ANIM = true;
      R_PRIME_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
      L_ANIM = true;
      L_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
      F_ANIM = true;
      F_ANIM_I = true;
      some_movement = true;
    }

    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
      B_PRIME_ANIM = true;
      B_PRIME_ANIM_I = true;
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

float move_angles[9] = {
  135.0f,
  90.0f,
  45.0f,
  180.0f,
  0.0f,
  0.0f,
  225.0f,
  270.0f,
  315.0f,
};

const float angles_upper_limit[9] = {
  225.0f,
  180.0f,
  135.0f,
  270.0f,
  0.0f,
  90.0f,
  315.0f,
  360.0f,
  405.0f,
};

const float angles_lower_limit[9] = {
  45.0f,
  0.0f,
  -45.0f,
  90.0f,
  0.0f,
  -90.0f,
  135.0f,
  180.0f,
  225.0f,
};

void ResetAngles() {
  move_angles[0] = 135.0f;
  move_angles[1] = 90.0f;
  move_angles[2] = 45.0f;
  move_angles[3] = 180.0f;
  move_angles[4] = 0.0f;
  move_angles[5] = 0.0f;
  move_angles[6] = 225.0f;
  move_angles[7] = 270.0f;
  move_angles[8] = 315.0f;
}

glm::vec3 CalculateTranslatePosition(float angle, Move m, const float& radius) {
  switch (m) {
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

    case R:
    case RP:
      return glm::vec3(0.5f, 
                       radius * sin(deg(angle)),
                       radius * cos(deg(angle)));
      break;

    case L:
    case LP:
      return glm::vec3(-0.5f,
                       radius * sin(deg(angle)),
                       radius * cos(deg(angle)));
      break;

    case U:
    case UP:
      return glm::vec3(radius * cos(deg(angle)),
                       0.5f,
                       radius * sin(deg(angle)));
      break;

    case D:
    case DP:
      return glm::vec3(radius * cos(deg(angle)),
                       -0.5f,
                       radius * sin(deg(angle)));
  }
}

void PlayAnimation() {
  std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;
  float* angles = move_angles;
  const float* angles_limit;
  float step;
  int clockwise;
  Move current_move;
  int normalMove;

  if (F_ANIM_I) {
    current_move = F;
    clockwise = 1;
    normalMove = kAroundZLeft;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (F_PRIME_ANIM_I) {
    current_move = FP;
    clockwise = -1;
    normalMove = kAroundZLeft;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_ANIM_I) {
    current_move = B;
    clockwise = 1;
    normalMove = kAroundZLeft;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_PRIME_ANIM_I) {
    current_move = BP;
    clockwise = -1;
    normalMove = kAroundZLeft;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (L_ANIM_I) {
    current_move = L;
    clockwise = 1;
    normalMove = kAroundXRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (L_PRIME_ANIM_I) {
    current_move = LP;
    clockwise = -1;
    normalMove = kAroundXRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (R_ANIM_I) {
    current_move = R;
    clockwise = 1;
    normalMove = kAroundXRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 9; i <= 27; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (R_PRIME_ANIM_I) {
    current_move = RP;
    clockwise = -1;
    normalMove = kAroundXRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 9; i <= 27; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (U_ANIM) {
    current_move = U;
    clockwise = -1;
    normalMove = kAroundYRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 1; i <= 9; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (U_PRIME_ANIM) {
    current_move = UP;
    clockwise = 1;
    normalMove = kAroundYRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 1; i <= 9; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (D_PRIME_ANIM) {
    current_move = DP;
    clockwise = -1;
    normalMove = kAroundYRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 19; i <= 21; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (D_ANIM) {
    current_move = D;
    clockwise = 1;
    normalMove = kAroundYRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 19; i <= 21; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }

  for (int i = 1; i <= 7; i += 2) {
    if (std::abs(angles_limit[i] - angles[i]) > 0.5f) angles[i] += step;
    else {
      angles[i] = angles_limit[i];
      cubitos[i].get()->Rotate(normalMove * clockwise);
    }

    cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i],
                                  current_move, kRadioNormal));

    cubitos[i].get()->Rotate(normalMove * -1 * clockwise);
  }

  for (int i = 0; i < 8; i += 2) {
    if (i != 4) {
      if (std::abs(angles_limit[i] - angles[i]) > 0.5f) angles[i] += step;
      else {
        angles[i] = angles_limit[i];
        cubitos[i].get()->Rotate(normalMove * clockwise);
      }

      cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i],
                                    current_move, kRadioLarge));
    }

    cubitos[i].get()->Rotate(normalMove * -1 * clockwise);
  }

  if (std::abs(angles_limit[8] - angles[8]) > 0.5f) angles[8] += step;
  else {
    angles[8] = angles_limit[8];
    cubitos[8].get()->Rotate(normalMove * clockwise);
    cubitos[4].get()->Rotate(normalMove * clockwise);
    F_ANIM_I = false;
    B_ANIM_I = false;
    F_PRIME_ANIM_I = false;
    B_PRIME_ANIM_I = false;
    L_ANIM_I = false;
    L_PRIME_ANIM_I = false;
    R_PRIME_ANIM_I = false;
    R_ANIM_I = false;
    U_ANIM_I = false;
    U_PRIME_ANIM_I = false;
    D_ANIM_I = false;
    D_PRIME_ANIM_I = false;
    some_movement = false;
  }

  cubitos[8].get()->SetPosition(CalculateTranslatePosition(angles[8],
                                current_move, kRadioLarge));

  cubitos[8].get()->Rotate(normalMove * -1 * clockwise);

  // REASIGN POINTER
  if (!some_movement) {
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

    ResetAngles();

    B_ANIM = false;
    B_PRIME_ANIM = false;
    F_ANIM = false;
    F_PRIME_ANIM = false;
    L_PRIME_ANIM = false;
    L_ANIM = false;
    R_ANIM = false;
    R_PRIME_ANIM = false;
    U_ANIM = false;
    U_PRIME_ANIM = false;
    D_ANIM = false;
    D_PRIME_ANIM = false;
  }
}
