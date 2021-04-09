#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "buildShaders.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

const int N = 20; // number of figures
const int MV = 175; // maximum number of vertexs in one figure

unsigned int VBO, VAO, EBO[N];

const float vertices[] = {

  ////// Fondo
  
  -0.7, 1.0, 0.0,//0
  -0.6, 0.7, 0.0,//1
  -0.7, 0.75, 0.0,//2
  -0.7, 0.55, 0.0,//3
  -0.5, 0.3, 0.0,//4
  -0.7, 0.15, 0.0,//5
  -0.7, 0.0, 0.0,//6
  -0.45, -0.05, 0.0,//7
  -0.7, -0.1, 0.0,//8
  -0.7, -0.4, 0.0,//9
  -0.4, -0.5, 0.0,//10
  -0.7, -0.7, 0.0,//11
  -0.7, -0.9, 0.0,//12
  -0.45, -0.95, 0.0,//13
  -0.7, -1.0, 0.0,//14
  -0.48, -1.0, 0.0,//15
  -0.45, 1.0, 0.0,//16
  -0.15, 0.95, 0.0,//17
  -0.25, 0.9, 0.0,//18
  -0.35, 0.8, 0.0,//19
  -0.4, 0.75, 0.0,//20
  -0.43, 0.65, 0.0,//21
  -0.45, 0.5, 0.0,//22
  -0.2, 0.6, 0.0,//23
  -0.4, 0.35, 0.0,//24
  0.0, 1.0, 0.0,//25
  -0.35, 0.25, 0.0,//26
  -0.3, 0.2, 0.0,//27
  -0.2, 0.15, 0.0,//28
  0.0, 0.1, 0.0,//29
  0.3, -0.7, 0.0,//30
  0.8, -0.3, 0.0,//31
  0.40, 0.1, 0.0,//32
  -0.05, -0.7, 0.0,//33
  -0.15, -1.0, 0.0,//34
  -0.3, -1.0, 0.0,//35
  0.6, -1.0, 0.0,//36
  0.8, -1.0, 0.0,//37
  0.7, -0.8, 0.0,//38
  0.55, -0.65, 0.0,//39
  0.8, 0.0, 0.0,//40
  0.8, 0.45, 0.0,//41
  0.75, 0.5, 0.0,//42
  0.8, 0.6, 0.0,//43
  0.6, 0.6, 0.0,//44
  0.8, 0.95, 0.0,//45
  0.7, 1.0, 0.0,//46
  0.6, 1.0, 0.0,//47
  0.35, 1.0, 0.0,//48
  0.15, 0.98, 0.0,//49
  0.25, 0.96, 0.0,//50
  0.34, 0.92, 0.0,//51
  0.45, 0.85, 0.0,//52
  0.55, 0.75, 0.0,//53
  0.0, 0.5, 0.0,//54
  0.58, 0.5, 0.0,//55
  0.52, 0.38, 0.0,//56
  0.45, 0.3, 0.0,//57
  0.3, 0.2, 0.0,//58
  0.8, 1.0, 0.0,//59

  ////// Virgencita

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

unsigned int figures[N][MV] = {

  ////// Fondo
  
  {// 1
    0, 1, 2,
    0, 1, 16,//
    42, 44, 55,
    55, 42, 56,
    42, 56, 32,
    32, 56, 57,//
    32, 31, 39,//
    32, 40, 31,//    
  },
  {// 2
    2, 1, 3,
    1, 3, 4,
    3, 4, 5,//
    1, 21, 4,
    21, 22, 4,
    22, 24, 4,//
  },
  {// 3
    4, 5, 8,
    4, 8, 7,//
    30, 39, 38,
    30, 38, 36,
    30, 36, 34,//
  },
  {// 4
    7, 8, 9,
    10, 9, 7,//
    39, 31, 38,//
  },
  {// 5
    9, 10, 12,
    10, 12, 13,
    13, 33, 34,
    13, 35, 34,
    13, 33, 10,//
    16, 17, 25,
    25, 48, 49,
    49, 48, 50,
    50, 48, 51,
    51, 48, 47,
    51, 52, 47,
    52, 53, 47,
    53, 44, 41,
    47, 53, 41,
    47, 41, 59,//
  },
  {// 6
    4, 24, 26,
    4, 26, 7,
    7, 26, 27,
    7, 27, 28,
    7, 28, 29,//
    7, 29, 10,
    20, 20, 33,//
    31, 32, 30,
    30, 39, 31,//
  },
  {// 7
    54, 17, 18,
    54, 18, 19,
    54, 19, 20,
    54, 20, 21,
    54, 21, 22,
    54, 22, 24,
    54, 24, 26,
    54, 26, 27,
    54, 27, 28,
    54, 28, 29,
    54, 29, 58,
    54, 58, 57,
    54, 57, 56,
    54, 56, 55,
    54, 55, 44,
    54, 44, 53,
    54, 53, 52,
    54, 52, 51,
    54, 51, 50,
    54, 50, 49,
    54, 49, 25,
    54, 25, 17,
  },
  {// 8
    16, 1, 21,
    16, 21, 20,
    16, 20, 19,
    16, 19, 18,
    16, 18, 17,//
    42, 40, 32,//
    12, 13, 14,
    14, 13, 15,
    13, 15, 35,//
    40, 41, 42,//
  },
  {// 9
    38, 36, 37,
    37, 38, 31,//
  },
  
  ////// Virgencita
  
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
  {
    0,1, 1,2, 1,3, 1,16, 1,4, 4,5, 4,7, 6,7, 8,7, 7,10, 9,10, 10,11, 10,13, 12,13,
    13,15, 13,35, 16,17, 17,18, 18,19, 19,20, 20,21, 21,22, 22,24, 24,23, 23,21,
    24,26, 26,27, 27,28, 28,29, 29,7, 17,25, 23,17, 36,38, 38,37, 38,39, 38,31,
    39,31, 40,42, 41,42, 42,43, 42,47, 46,45, 42,44, 57,56, 56,55, 55,44, 44,53,
    53,52, 52,51, 51,48, 50,51, 50,49, 25,49, 51,54, 31,32, 40,32, 42,32, 0,59,
    0,14, 14,37, 37,59
  },//Lines
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

int main()
{
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
  if (window == NULL)
  {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  // 1rojo, 2blue, 3lightblue, 4[blueish], 5gree, 6greenDarker, 7yellow, 8pink, 9purple
    
  unsigned int P01 = glCreateProgram();
  BuildShaders(P01, "shaders/default.vs", "shaders/red.fs");

  unsigned int P02 = glCreateProgram();
  BuildShaders(P02, "shaders/default.vs", "shaders/blue.fs");

  unsigned int P03 = glCreateProgram();
  BuildShaders(P03, "shaders/default.vs", "shaders/olive.fs");

  unsigned int P04 = glCreateProgram();
  BuildShaders(P04, "shaders/default.vs", "shaders/lilac.fs");

  unsigned int P05 = glCreateProgram();
  BuildShaders(P05, "shaders/default.vs", "shaders/orange.fs");

  unsigned int P06 = glCreateProgram();
  BuildShaders(P06, "shaders/default.vs", "shaders/lightblue.fs");

  unsigned int P07 = glCreateProgram();
  BuildShaders(P07, "shaders/default.vs", "shaders/yellow.fs");

  unsigned int P08 = glCreateProgram();
  BuildShaders(P08, "shaders/default.vs", "shaders/pink.fs");

  unsigned int P09 = glCreateProgram();
  BuildShaders(P09, "shaders/default.vs", "shaders/purple.fs");

  unsigned int defaultProgram = glCreateProgram();
  BuildShaders(defaultProgram, "shaders/default.vs", "shaders/beige.fs");

  unsigned int blueishProgram = glCreateProgram();
  BuildShaders(blueishProgram, "shaders/default.vs", "shaders/blueish.fs");

  unsigned int brownProgram = glCreateProgram();
  BuildShaders(brownProgram, "shaders/default.vs", "shaders/brown.fs");

  unsigned int skinProgram = glCreateProgram();
  BuildShaders(skinProgram, "shaders/default.vs", "shaders/skin.fs");

  unsigned int blackProgram = glCreateProgram();
  BuildShaders(blackProgram, "shaders/default.vs", "shaders/black.fs");

  for(int i = 9; i < 15; ++i){
    for(int j = 0; j < MV; j++) figures[i][j] += 60;
  }
  
  startVertexInput();
    
  while (!glfwWindowShouldClose(window))
  {
    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(VAO);

    // Fondo
    
    glUseProgram(P01);
    drawWithEBO(0, 24);

    glUseProgram(P02);
    drawWithEBO(1, MV);

    glUseProgram(P03);
    drawWithEBO(2, MV);
    
    glUseProgram(P04);
    drawWithEBO(3, MV);

    glUseProgram(P05);
    drawWithEBO(4, MV);

    glUseProgram(P06);
    drawWithEBO(5, MV);
    
    glUseProgram(P07);
    drawWithEBO(6, MV);

    glUseProgram(P08);
    drawWithEBO(7, MV);

    glUseProgram(P09);
    drawWithEBO(8, MV);

    // Lines
    glUseProgram(blackProgram);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_LINE_WIDTH);
    glLineWidth(100);
    drawWithEBO(15, MV, GL_LINES);

    // Virgencita

    glUseProgram(defaultProgram);
    drawWithEBO(9, 19, GL_TRIANGLE_STRIP);
    drawWithEBO(11, 27, GL_TRIANGLE_STRIP);
    drawWithEBO(14, 4, GL_TRIANGLE_STRIP);

    glUseProgram(blueishProgram);
    drawWithEBO(10, 26, GL_TRIANGLE_STRIP);

    glUseProgram(brownProgram);
    drawWithEBO(12, 10, GL_TRIANGLE_STRIP);

    glUseProgram(skinProgram);
    drawWithEBO(13, 16, GL_TRIANGLE_STRIP);

    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(N, EBO);
  glDeleteProgram(P01);
  glDeleteProgram(P02);
  glDeleteProgram(P03);
  glDeleteProgram(P04);
  glDeleteProgram(P05);
  glDeleteProgram(P06);
  glDeleteProgram(P07);
  glDeleteProgram(P08);
  glDeleteProgram(P09);
  glDeleteProgram(defaultProgram);
  glDeleteProgram(blueishProgram);
  glDeleteProgram(brownProgram);
  glDeleteProgram(skinProgram);
  glDeleteProgram(blackProgram);
  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow *window)
{
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}
