/*****
 Computacion Grafica : CCOMP 7-1
 * Gonzales Navarrete Mateo
 * Nieto Rosas Miguel
 * Palma Ugarte Joaquin

 Presionar tecla:
 * Z: Dibujar con POINTS
 * X: Dibujar con LINE_STRIP
 * C: Dibujar con TRIANGLES
 *****/

#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#define PI 3.14159265
#define MUL 0.3819660f // sin(18)/sin(54)

float deg(float num) {
  return (num * PI / 180);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);

enum primitives {POINTS, LINE_STRIP, TRIANGLES};
primitives PRIMITIVE_TYPE = primitives::TRIANGLES;

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "uniform mat4 transform;\n"
  "void main() {\n"
  " gl_Position = transform * vec4(aPos, 1.0f);\n"
  "}\0";

const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

glm::vec3 translationVector;
bool randomMove;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT,
                                        "Basic OpenGL Program", NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  int success;
  char infoLog[512];

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" <<
              infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" <<
              infoLog << std::endl;
  }

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" <<
              infoLog << std::endl;
  }

  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices_points[] = {
    cos(deg(18)), sin(deg(18)), 0.0f,
    MUL * cos(deg(54)), MUL * sin(deg(54)), 0.0f,
    cos(deg(90)), sin(deg(90)), 0.0f,
    MUL * cos(deg(126)), MUL * sin(deg(126)), 0.0f,
    cos(deg(162)), sin(deg(162)), 0.0f,
    MUL * cos(deg(198)), MUL * sin(deg(198)), 0.0f,
    cos(deg(234)), sin(deg(234)), 0.0f,
    MUL * cos(deg(270)), MUL * sin(deg(270)), 0.0f,
    cos(deg(306)), sin(deg(306)), 0.0f,
    MUL * cos(deg(342)), MUL * sin(deg(342)), 0.0f,
    cos(deg(18)), sin(deg(18)), 0.0f
  };

  float vertices_triangles[] = {
    cos(deg(18)), sin(deg(18)), 0.0f,
    cos(deg(162)), sin(deg(162)), 0.0f,
    MUL * cos(deg(270)), MUL * sin(deg(270)), 0.0f,

    cos(deg(90)), sin(deg(90)), 0.0f,
    cos(deg(234)), sin(deg(234)), 0.0f,
    MUL * cos(deg(342)), MUL * sin(deg(342)), 0.0f,

    cos(deg(162)), sin(deg(162)), 0.0f,
    cos(deg(306)), sin(deg(306)), 0.0f,
    MUL * cos(deg(54)), MUL * sin(deg(54)), 0.0f
  };

  unsigned int VAOs[2], VBOs[2];
  glGenBuffers(2, VBOs);
  glGenVertexArrays(2, VAOs);

  // Points
  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_points), vertices_points,
               GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Triangles
  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangles), vertices_triangles,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glEnable(GL_PROGRAM_POINT_SIZE);
  // glEnable(GL_POINT_SMOOTH);
  // glEnable(GL_LINE_SMOOTH);
  // glEnable(GL_BLEND);
  // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glPointSize(6);

  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    if (randomMove) {
      translationVector.x += ((rand()%2)*-0.02) + 0.01f;
      translationVector.y += ((rand()%2)*-0.02) + 0.01f;
    }
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, translationVector);
    // transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

    switch (PRIMITIVE_TYPE) {
      case primitives::POINTS:
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_POINTS, 0, 10);
        break;

      case primitives::LINE_STRIP:
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_LINE_STRIP, 0, 11);
        break;

      case primitives::TRIANGLES:
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 9);
        break;
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Optional: Deallocate all resources once they've outlived their purpose
  glDeleteVertexArrays(2, VAOs);
  glDeleteBuffers(2, VBOs);
  glDeleteProgram(shaderProgram);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  glfwTerminate();
  return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_Z && action == GLFW_PRESS)
    PRIMITIVE_TYPE = primitives::POINTS;

  if (key == GLFW_KEY_X && action == GLFW_PRESS)
    PRIMITIVE_TYPE = primitives::LINE_STRIP;

  if (key == GLFW_KEY_C && action == GLFW_PRESS)
    PRIMITIVE_TYPE = primitives::TRIANGLES;

  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    translationVector.x += 0.01f;

  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    translationVector.x += -0.01f;

  if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    translationVector.y += 0.01f;

  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
    translationVector.y += -0.01f;

  if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
    translationVector.x += -0.01f;
    translationVector.y += 0.01f;
  }

  if (key == GLFW_KEY_E && action == GLFW_PRESS) {
    translationVector.x += 0.01f;
    translationVector.y += 0.01f;
  }

  if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    translationVector.x += -0.01f;
    translationVector.y += -0.01f;
  }

  if (key == GLFW_KEY_D && action == GLFW_PRESS) {
    translationVector.x += 0.01f;
    translationVector.y += -0.01f;
  }

  if (key == GLFW_KEY_R && action == GLFW_PRESS) {
    randomMove ^= 1;
  }
}
