#ifndef CUBITO_SETTING_HPP
#define CUBITO_SETTING_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Size of screen
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;
glm::mat4 model = glm::mat4(1.0f);
glm::mat4 view = glm::mat4(1.0f);
glm::mat4 projection = glm::mat4(1.0f);

// General const variables
const double PI = 3.14159;
const glm::vec3 RED = glm::vec3(1.0f, 0.0f, 0.0f);
const glm::vec3 GREEN = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec3 BLUE = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 ORANGE = glm::vec3(1.0f, 0.5f, 0.0f);
const glm::vec3 WHITE = glm::vec3(1.0f, 1.0f, 1.0f);
const glm::vec3 YELLOW = glm::vec3(1.0f, 1.0f, 0.0f);

// General functions
float deg(float num) { // warning posible loss of data
  return (num * PI / 180);
}

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

// Main object that control game

// Thing of camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 500.0f;
float lastY = 500.0f;
bool first_time_mouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;
enum class Move {
  L, LP,
  R, RP,
  U, UP,
  D, DP,
  F, FP,
  B, BP
};

// Const variables of rubick_cube
const float distance_b_cubes = 0.4f;
const float kRadioLarge = distance_b_cubes * sqrt(2);
const float kRadioNormal = distance_b_cubes;

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

const int kAroundXLeft = 1;
const int kAroundXRight = -1;
const int kAroundYLeft = -2;
const int kAroundYRight = 2;
const int kAroundZLeft = 3;
const int kAroundZRight = -3;

#endif // CUBITO_SETTING_HPP
