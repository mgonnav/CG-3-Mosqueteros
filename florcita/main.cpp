/*****
 Computacion Grafica: CCOMP 7-1
 * Gonzales Navarrete Mateo
 * Nieto Rosas Miguel
 * Palma Ugarte Joaquin
 *****/

#include "glad/glad.h"
#include <glfw/glfw3.h>
#include "shaders.cpp"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
  // glfw: Initialize and configure
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,
                 GL_TRUE);
#endif

  // glfw window creation
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

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int fragmentGreen;
  fragmentGreen = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentGreen, 1, &fragmentShaderGreen, NULL);
  glCompileShader(fragmentGreen);

  unsigned int fragmentGreenDarker;
  fragmentGreenDarker = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentGreenDarker, 1, &fragmentShaderGreenDarker, NULL);
  glCompileShader(fragmentGreenDarker);

  unsigned int fragmentRed;
  fragmentRed = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentRed, 1, &fragmentShaderRed, NULL);
  glCompileShader(fragmentRed);

unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER); // the first fragment shader that outputs the color orange
    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER); // the second fragment shader that outputs the color yellow
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram(); // the second shader program
    
    glShaderSource(fragmentShaderOrange, 1, &fragmentShader1Source, NULL);
    glCompileShader(fragmentShaderOrange);
    glShaderSource(fragmentShaderYellow, 1, &fragmentShader2Source, NULL);
    glCompileShader(fragmentShaderYellow);
    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);
    glLinkProgram(shaderProgramOrange);
    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);
    glLinkProgram(shaderProgramYellow);

  // Shader Program
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  unsigned int shaderGreen;
  shaderGreen = glCreateProgram();
  glAttachShader(shaderGreen, vertexShader);
  glAttachShader(shaderGreen, fragmentGreen);
  glLinkProgram(shaderGreen);

  unsigned int shaderGreenDarker;
  shaderGreenDarker = glCreateProgram();
  glAttachShader(shaderGreenDarker, vertexShader);
  glAttachShader(shaderGreenDarker, fragmentGreenDarker);
  glLinkProgram(shaderGreenDarker);

  unsigned int shaderRed;
  shaderRed = glCreateProgram();
  glAttachShader(shaderRed, vertexShader);
  glAttachShader(shaderRed, fragmentRed);
  glLinkProgram(shaderRed);

  glUseProgram(shaderProgram);
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  float vertices_leafs[] = {
    -0.5f, 0.1f, 0.0f,
      -0.25f, 0.05f, 0.0f,
      -0.35f, -0.22f, 0.0f,
      -0.12f, -0.05f, 0.0f,
      -0.25f, -0.5f, 0.0f,
      0.0f, -0.2f, 0.0f,
      -0.14f, -0.63f, 0.0f,
      0.0f, -0.7f, 0.0f,

      0.14f, -0.63f, 0.0f,
      0.0f, -0.2f, 0.0f,
      0.25f, -0.5f, 0.0f,
      0.12f, -0.05f, 0.0f,
      0.35f, -0.22f, 0.0f,
      0.25f, 0.05f, 0.0f,
      0.5f, 0.1f, 0.0f
    };
  float vertices_grande[] = {
    -0.7f, 0.9f, 0.0f, // A
      0.7f, 0.9f, 0.0f, // B
      0.7f, -0.9f, 0.0f, // G

      -0.7f, 0.9f, 0.0f, // A
      -0.7f, -0.9f, 0.0f, // H
      0.7f, -0.9f, 0.0f, // G

    };
  float vertices_medio[] = {
    -0.5f, 0.7f, 0.0f, // C
      0.5f, 0.7f, 0.0f, // D
      0.5f, -0.7f, 0.0f, // F

      -0.5f, 0.7f, 0.0f, // C
      0.5f, -0.7f, 0.0f, // F
      -0.5f, -0.7f, 0.0f, // E
    };
  float vertices_mini1[] = {
    -0.7f, 0.9f, 0.0f, // A
      -0.5f, 0.9f, 0.0f, // AC
      -0.5f, 0.7f, 0.0f, // C

      -0.7f, 0.9f, 0.0f, // A
      -0.5f, 0.7f, 0.0f, // C
      -0.7f, 0.7f, 0.0f, // CA
    };
  float vertices_mini2[] = {
    -0.5f, -0.7f, 0.0f, // E
      -0.7f, -0.7f, 0.0f, // EH
      -0.7f, -0.9f, 0.0f, // H

      -0.5f, -0.7f, 0.0f, // E
      -0.7f, -0.9f, 0.0f, // H
      -0.5f, -0.9f, 0.0f, // HE
    };
  float vertices_mini3[] = {
    0.5f, -0.7f, 0.0f, // F
    0.5f, -0.9f, 0.0f, // FG
    0.7f, -0.9f, 0.0f, // G

    0.5f, -0.7f, 0.0f, // F
    0.7f, -0.9f, 0.0f, // G
    0.7f, -0.7f, 0.0f, // GF
  };
  float vertices_mini4[] = {
    0.7f, 0.9f, 0.0f, // B
    0.5f, 0.9f, 0.0f, // BD
    0.5f, 0.7f, 0.0f, // D

    0.7f, 0.9f, 0.0f, // B
    0.5f, 0.7f, 0.0f, // D
    0.7f, 0.7f, 0.0f, // DB

  };
  float vertices1[] = {
    0.0f, 0.1f, 0.0f,  //0
    0.1f, 0.12f, 0.0f, //1
    0.2f, 0.2f, 0.0f, //2
    0.28f, 0.3f, 0.0f, //3
    0.3f, 0.4f, 0.0f,//4
    0.2f, 0.4f, 0.0f,//5
    0.1f, 0.35f, 0.0f,//6
    0.05f, 0.45f, 0.0f,//7
    0.0f, 0.5f, 0.0f, //8
    -0.05f, 0.45f, 0.0f,//9
    -0.1f, 0.35f, 0.0f,//10
    -0.2f, 0.4f, 0.0f,//11
    -0.3f, 0.4f, 0.0f,//12
    -0.28f, 0.3f, 0.0f,//13
    -0.2f, 0.2f, 0.0f,//14
    -0.1f, 0.12f, 0.0f,//15
    0.0f, 0.1f, 0.0f,//16
    -0.02f, 0.18f, 0.0f,//17
    0.0f, 0.26, 0.0f,//18
    0.1f, 0.35f, 0.0f,//19
  };

  float vertices2[] = { 
    0.0f, 0.1f, 0.0f,  //0
    -0.02f, 0.18f, 0.0f,//17
    0.1f, 0.12f, 0.0f, //1
    0.0f, 0.26, 0.0f,//18
    0.2f, 0.2f, 0.0f, //2
    0.1f, 0.35f, 0.0f,//6
    0.28f, 0.3f, 0.0f, //3
    0.2f, 0.4f, 0.0f,//5
    0.3f, 0.4f, 0.0f,//4
  };

  float vertices3[] = {
    0.0f, 0.1f, 0.0f,  //0
    -0.1f, 0.12f, 0.0f,//15
    0.0f, 0.26, 0.0f,//18
    -0.2f, 0.2f, 0.0f,//14
    -0.1f, 0.35f, 0.0f,//10
    -0.28f, 0.3f, 0.0f,//13
    -0.2f, 0.4f, 0.0f,//11
    -0.3f, 0.4f, 0.0f,//12
  };
  float vertices4[] = {
    0.0f, 0.26, 0.0f,//18
    0.1f, 0.35f, 0.0f,//6
    -0.1f, 0.35f, 0.0f,//10
    0.05f, 0.45f, 0.0f,//7
    -0.05f, 0.45f, 0.0f,//9
    0.0f, 0.5f, 0.0f, //8
  };
  float tallo[] = {
    0.0f, 0.26, 0.0f,
    0.0f, -0.3, 0.0f
  };

  unsigned int VBOs[12], VAOs[12];
  glGenBuffers(12, VBOs);
  glGenVertexArrays(12, VAOs);

  glBindVertexArray(VAOs[0]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_leafs), vertices_leafs,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[1]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_grande,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[2]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_medio,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[3]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[3]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_mini1,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[4]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[4]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_mini2,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[5]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[5]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_mini3,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[6]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[6]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_grande), vertices_mini4,
               GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[7]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[7]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Vertex attributes stay the same
  // second triangle setup
  glEnableVertexAttribArray(0);
  // ---------------------
  glBindVertexArray(VAOs[8]);	// note that we bind to a different VAO now
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[8]);	// and a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
  // second triangle setup
  glEnableVertexAttribArray(0);
  // ---------------------
  glBindVertexArray(VAOs[9]);	// note that we bind to a different VAO now
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[9]);	// and a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3), vertices3, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
  // second triangle setup
  glEnableVertexAttribArray(0);
  // ---------------------
  glBindVertexArray(VAOs[10]);	// note that we bind to a different VAO now
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[10]);	// and a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices4), vertices4, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
  glEnableVertexAttribArray(0);

  glBindVertexArray(VAOs[11]);
  glBindBuffer(GL_ARRAY_BUFFER, VBOs[11]);	// and a different VBO
  glBufferData(GL_ARRAY_BUFFER, sizeof(tallo), tallo, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); // because the vertex data is tightly packed we can also specify 0 as the vertex attribute's stride to let OpenGL figure it out
  glEnableVertexAttribArray(0);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgramOrange);
    glBindVertexArray(VAOs[1]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[2]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[3]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[4]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[5]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramYellow);
    glBindVertexArray(VAOs[6]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glUseProgram(shaderProgramOrange);
    glBindVertexArray(VAOs[11]);
    glDrawArrays(GL_LINE_STRIP, 0, 2);

    glUseProgram(shaderGreen);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

    glUseProgram(shaderGreenDarker);
    glBindVertexArray(VAOs[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 7, 8);

    glUseProgram(shaderRed);
    glBindVertexArray(VAOs[7]);
    glDrawArrays(GL_LINE_STRIP, 0, 20);

    glBindVertexArray(VAOs[8]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 9);

    glBindVertexArray(VAOs[9]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 8);

    glBindVertexArray(VAOs[10]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Optional: Deallocate all resources once they've outlived their purpose
  glDeleteVertexArrays(12, VAOs);
  glDeleteBuffers(12, VBOs);
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
