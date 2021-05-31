/*****
 Computacion Grafica : CCOMP 7-1
 *****/

#include "glad/glad.h"
#include <glfw/glfw3.h>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// =============================== Declarations ===============================

const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

unsigned int shaderProgram;

const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "uniform mat4 transform;\n"
  "void main() {\n"
  " gl_Position = transform * vec4(aPos, 1.0f);\n"
  "}\0";

const char* fragmentShaderSource =
  "#version 330 core\n"
  "uniform vec4 vColor;\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  "  FragColor = vColor;\n"
  "}\0";

struct Figure {
  unsigned int VAO, VBO, EBO;
  int triangles;
  glm::mat4 trans;
  glm::vec4 color;
  bool move;
  
  Figure() {
    move = false;
    trans = glm::mat4(1.0f);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
  }
  virtual ~Figure() {};
  virtual void animate() = 0;
  void draw() {
    if (move) {
      animate();
      move = false;
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Draw lines
    unsigned int color_loc = glGetUniformLocation(shaderProgram, "vColor");
    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniform4fv(color_loc, 1, glm::value_ptr(color));
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, 3 * triangles, GL_UNSIGNED_INT, 0);
  }
};

struct Cube : Figure {
  float vertexs[24];
  int figure[36];
  
  Cube() : Figure(), vertexs {
      -0.3, -0.3, -0.3,
      -0.3, 0.3, -0.3,
      0.3, 0.3, -0.3,
      0.3, -0.3, -0.3,
      -0.3, -0.3, 0.3,
      -0.3, 0.3, 0.3,
      0.3, 0.3, 0.3,
      0.3, -0.3, 0.3,
    }, figure {
      0, 1, 2,
      0, 2, 3,
      3, 4, 6,
      3, 6, 7,
      0, 1, 4,
      1, 4, 5,
      4, 5, 6,
      4, 6, 7,
      0, 4, 7,
      0, 7, 3,
      1, 5, 6,
      1, 6, 4,
    } {
    triangles = 12;
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(figure), figure, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
  }
  ~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
  }
  void animate() {
    trans = glm::rotate(trans, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  }
};


// =============================== Main ===============================

Cube *minicube;

int main() {
  srand (time(NULL));
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Examen Parcial", NULL, NULL);

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
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // =============================== Loop ===============================

  minicube = new Cube;
  
  glfwSetKeyCallback(window, key_callback);

  glUseProgram(shaderProgram);
  
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(100);
    
    minicube->draw();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  delete minicube;

  glDeleteProgram(shaderProgram);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// =============================== Key controls ===============================

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    minicube->move = true;
  }
}
