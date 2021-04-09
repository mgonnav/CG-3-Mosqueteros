#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buildShaders.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const int N = 6; // number of figures
const int MV = 30; // maximum number of vertexs in one figure

unsigned int VBO, VAO, EBO[N];

const float vertices[] = {
  -.1f, 0.72f, 0.0f,
    0.0f, 0.78f, 0.0f,
    0.01f, 0.7f, 0.0f,
    0.1f, 0.78f, 0.0f,
    0.12f, 0.65f, 0.0f,
    0.2f, 0.76f, 0.0f,
    0.2f, 0.6f, 0.0f,
    0.28f, 0.7f, 0.0f,
    0.28f, 0.5f, 0.0f,
    0.32f, 0.62f, 0.0f,
    0.33f, 0.43f, 0.0f,
    0.38f, 0.53f, 0.0f,
    0.36f, 0.37f, 0.0f,
    0.41f, 0.48f, 0.0f,
    0.40f, 0.31f, 0.0f,
    0.44f, 0.38f, 0.0f,
    0.41f, 0.28f, 0.0f,
    0.45f, 0.3f, 0.0f,
    0.47f, 0.12f, 0.0f,

    -0.16f, 0.67f, 0.0f,
    -.1f, 0.65f, 0.0f,
    0.0f, 0.6f, 0.0f,
    0.1f, 0.51f, 0.0f,
    0.15f, 0.45f, 0.0f,
    0.19f, 0.36f, 0.0f,
    0.26f, 0.2f, 0.0f,
    0.3f, 0.05f, 0.0f,
    0.32f, -0.14f, 0.0f,
    0.5f, -0.05f, 0.0f,
    0.33f, -0.24f, 0.0f,
    0.54f, -0.2f, 0.0f,
    0.31f, -0.32f, 0.0f,
    0.56f, -0.32f, 0.0f,
    0.3f, -0.52f, 0.0f,
    0.55f, -0.55f, 0.0f,
    0.24f, -1.f, 0.0f,
    0.42f, -0.9f, 0.0f,

    0.07f, 0.48f, 0.0f,
    0.1f, 0.36f, 0.0f,
    0.14f, 0.22f, 0.0f,
    0.17f, 0.15f, 0.0f,
    0.18f, -0.06f, 0.0f,
    0.22f, -0.12f, 0.0f,
    0.23f, -0.21f, 0.0f,
    0.22f, -0.29f, 0.0f,
    0.135f, -0.4f, 0.0f,
    0.16f, -0.59f, 0.0f,
    0.29f, -0.6f, 0.0f,
    0.27f, -0.79f, 0.0f,
    0.16f, -0.72f, 0.0f,
    0.25f, -0.9f, 0.0f,
    0.1f, -0.9f, 0.0f,
    0.16f, -1.f, 0.0f,
    0.01f, -0.99f, 0.0f,

    -0.19f, 0.64f, 0.0f,
    -0.21f, 0.58f, 0.0f,
    -0.14f, 0.53f, 0.0f,
    -0.04f, 0.48f, 0.0f,
    0.05f, 0.42f, 0.0f,

    -0.21f, 0.46f, 0.0f, 
    -0.15f, 0.34f, 0.0f,
    -0.14f, 0.25f, 0.0f,
    -0.12f, 0.245f, 0.0f,
    -0.07f, 0.19f, 0.0f,
    -0.02f, 0.16f, 0.0f,
    0.04f, 0.16f, 0.0f,
    0.04f, 0.11f, 0.0f,

    0.0f, 0.03f, 0.0f,
  };
const unsigned int figures[N][MV] = {
  {
    0, 1, 2,
    3, 4, 5,
    6, 7, 8,
    9, 10, 11,
    12, 13, 14,
    15, 16, 17,
    18
  }, // Veil Outter
  {
    19, 0, 20,
    2, 21, 4,
    22, 6, 23,
    8, 24, 12,
    25, 16, 26,
    18, 27,
    28, 29, 30,
    31, 32, 33,
    34, 35, 36
  }, // Veil Middle
  {
    21, 37, 22,
    38, 23, 39,
    24, 40, 25,
    41, 26, 42,
    27, 43, 29,
    44, 31, 45,
    33, 46, 47,
    49, 48, 51,
    50, 53, 52
  }, // Veil Inner
  {
    54, 19, 55,
    20, 56, 21,
    57, 37, 58,
    38
  }, // Hair
  {
    55, 59, 56,
    60, 57, 61,
    58, 62, 38,
    63, 39, 64,
    39, 65, 40,
    66
  }, // Face
  {
    66, 40, 67,
    41
  }, // Chest
};

void drawWithEBO(int EBOindex, int vertexNumber,
                 GLenum primitive_type=GL_TRIANGLES) {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[EBOindex]);
  glDrawElements(primitive_type, vertexNumber, GL_UNSIGNED_INT, 0);
}

void startVertexInput() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(N, EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  for (int i = 0; i < N; ++i) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[i]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(figures[i]), figures[i],
                 GL_STATIC_DRAW);
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
                                        NULL, NULL);

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

  unsigned int defaultProgram = glCreateProgram();
  BuildShaders(defaultProgram, "shaders/default.vs", "shaders/beige.fs");

  unsigned int blueishProgram = glCreateProgram();
  BuildShaders(blueishProgram, "shaders/default.vs", "shaders/blueish.fs");

  unsigned int brownProgram = glCreateProgram();
  BuildShaders(brownProgram, "shaders/default.vs", "shaders/brown.fs");

  unsigned int skinProgram = glCreateProgram();
  BuildShaders(skinProgram, "shaders/default.vs", "shaders/skin.fs");

  startVertexInput();

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);

    glUseProgram(defaultProgram);
    drawWithEBO(0, 19, GL_TRIANGLE_STRIP);
    drawWithEBO(2, 27, GL_TRIANGLE_STRIP);
    drawWithEBO(5, 4, GL_TRIANGLE_STRIP);

    glUseProgram(blueishProgram);
    drawWithEBO(1, 26, GL_TRIANGLE_STRIP);

    glUseProgram(brownProgram);
    drawWithEBO(3, 10, GL_TRIANGLE_STRIP);

    glUseProgram(skinProgram);
    drawWithEBO(4, 16, GL_TRIANGLE_STRIP);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(N, EBO);

  glDeleteProgram(defaultProgram);
  glDeleteProgram(blueishProgram);
  glDeleteProgram(brownProgram);
  glDeleteProgram(skinProgram);

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
