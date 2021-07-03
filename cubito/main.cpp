/*
* Copyright: Mosqueteros UCSP
* Trabajo final Computación gráfica
* 
*  Gonzales Navarrete Mateo
*  Palma Ugarte Joaquin
*  Nieto Miguel
*/

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
#include "solver/Rubik.hpp"
#include "Setting.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInputMouse(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void AutomaticCamera();

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
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    // Camera automatic
    if (auto_camera) {
      projection = glm::perspective(glm::radians(camera.Zoom),
        (float)SCR_WIDTH / (float)SCR_HEIGHT,
        0.1f,
        100.0f);

      AutomaticCamera();
    } else {
      ProcessInputMouse(window);

      projection = glm::perspective(glm::radians(camera.Zoom),
        (float)SCR_WIDTH / (float)SCR_HEIGHT,
        0.1f,
        100.0f);
      view = camera.GetViewMatrix();
    }

    // God actions
    game_controller.ProcessInput(deltaTime);
    
    game_controller.UpdateMatrices(model,view,projection);

    game_controller.UpdateGame(deltaTime);

    // Render All
    glClearColor(0.0f, 0.9f, 0.6f, 1.0f);
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

  if (game_controller.can_press) {
    if (key >= 0 && key < 1024)
      if (action == GLFW_PRESS)
        game_controller.keys_press[key] = true;
  }
  else {}

  if (action == GLFW_RELEASE) {
    game_controller.keys_press[key] = false;
    game_controller.keys_already_press[key] = false;
  }

  // Solver
  if (!game_controller.solution_anim && !game_controller.shuffle_anim
      && !game_controller.some_movement) {
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
      std::string new_str_scramble = game_controller.GenScramble(10);
      game_controller.scramble = game_controller.ParseOutput(new_str_scramble);
      game_controller.str_scramble += new_str_scramble;
      game_controller.shuffle_anim = true;
    }

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
      if (!game_controller.str_scramble.empty()) {
       game_controller.str_solution = rubik::solve(game_controller.str_scramble);
       game_controller.solution = game_controller.ParseOutput(game_controller.str_solution);
       game_controller.solution_anim = true;
      }
    }

    // Standard rubik's cube movements
    if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
      if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        game_controller.U_PRIME_ANIM = true;
        game_controller.U_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "U' ";
      }

      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        game_controller.D_PRIME_ANIM = true;
        game_controller.D_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "D' ";
      }

      if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        game_controller.R_ANIM = true;
        game_controller.R_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "R' ";
      }

      if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        game_controller.L_PRIME_ANIM = true;
        game_controller.L_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "L' ";
      }

      if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        game_controller.F_PRIME_ANIM = true;
        game_controller.F_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "F' ";
      }

      if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        game_controller.B_ANIM = true;
        game_controller.B_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "B' ";
      }
    
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        auto_camera = false;
      }

      if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        game_controller.expand_contract_efect = false;
      }
    }
    else {
      if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        game_controller.U_ANIM = true;
        game_controller.U_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "U ";
      }

      if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        game_controller.D_ANIM = true;
        game_controller.D_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "D ";
      }

      if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        game_controller.R_PRIME_ANIM = true;
        game_controller.R_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "R ";
      }

      if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        game_controller.L_ANIM = true;
        game_controller.L_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "L ";
      }

      if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        game_controller.F_ANIM = true;
        game_controller.F_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "F ";
      }

      if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        game_controller.B_PRIME_ANIM = true;
        game_controller.B_PRIME_ANIM_I = true;
        game_controller.some_movement = true;
        game_controller.str_scramble += "B ";
      }
    
      if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        auto_camera = true;
      }
      
      if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        game_controller.expand_contract_efect = true;
      }
    }
  }
}

void ProcessInputMouse(GLFWwindow* window) {
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
    lastX = static_cast<float>(xpos);
    lastY = static_cast<float>(ypos);
    first_time_mouse = false;
  }

  float xoffset = static_cast<float>(xpos - lastX);
  float yoffset = static_cast<float>(lastY - ypos);
  lastX = static_cast<float>(xpos);
  lastY = static_cast<float>(ypos);

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void AutomaticCamera() {
  const float distance_f_object = 6.0f;
  float cam_x = sin(glfwGetTime()) * distance_f_object;
  float cam_z = cos(glfwGetTime()) * distance_f_object;
  float cam_y = cos(glfwGetTime()) * distance_f_object;
  
  
  view = glm::lookAt( glm::vec3(cam_x, cam_y, cam_z),
                      glm::vec3(0.0f, 0.0f, 0.0f),
                      glm::vec3(0.0f, 1.0f, 0.0f));
}