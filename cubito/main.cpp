//        ID CUBE RUBICK
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

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <random>
#include <map>

#include "Cubito.hpp"
#include "Cubo.hpp"
#include "Camera.hpp"
#include "stb_image.h"
#include "Shader.h"
#include "GameController.hpp"
#include "Setting.hpp"

// IF YOU WANT TO KNOW INFO AFTER ONE MOVEMENT
#define DEBUG 0

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInputMouse(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// Create main controller of game
GameController game_controller(SCR_WIDTH, SCR_HEIGHT);

int main(int argc, char *argv[]) {

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Cubito Mosquetero", NULL, NULL);

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

  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(window, key_callback);
  
  PrintCommands();

  // Init main controller of game
  game_controller.Init();

  game_controller.StartParser();

  if(argc == 2) {
    game_controller.str_scramble = std::string(argv[1]) + " ";
    game_controller.scramble = game_controller.ParseOutput(game_controller.str_scramble);
    game_controller.shuffle_anim = true;
  }

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Camera calculations
    ProcessInputMouse(window);

    projection = glm::perspective(glm::radians(camera.Zoom),
      (float)SCR_WIDTH / (float)SCR_HEIGHT, 
      0.1f, 
      100.0f);
    view = camera.GetViewMatrix();

    // God actions
    game_controller.ProcessInput();
    
    game_controller.UpdateMatrices(model,view,projection);

    game_controller.UpdateGame();

    // Render All
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    game_controller.Render();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mode) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  if (key == GLFW_KEY_LEFT_SHIFT ||
      key == GLFW_KEY_RIGHT_SHIFT) {
    game_controller.keys_press[key] = true;
  }

  if (game_controller.can_press && !game_controller.shuffle_anim
      && !game_controller.solution_anim) {
    if (key >= 0 && key < 1024)
      if (action == GLFW_PRESS)
        game_controller.keys_press[key] = true;
  }

  if (action == GLFW_RELEASE) {
    game_controller.keys_press[key] = false;
    game_controller.keys_already_press[key] = false;
  }
}

void ProcessInputMouse(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);

  float cameraSpeed = 2.5 * deltaTime;

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::FORWARD, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::BACKWARD, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::LEFT, deltaTime);

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera.ProcessKeyboard(CameraMovement::RIGHT, deltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
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
