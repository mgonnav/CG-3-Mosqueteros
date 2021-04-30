/*
 * Integrantes:
 *    Gonzales Navarrete, Mateo
 *    Nieto, Miguel
 *    Palma Ugarte, Joaquin
 *
 * Keyboard callbacks:
 *    Press down C: Reload colors array
 */

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <queue>
#include <math.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/epsilon.hpp>

#define PI 3.1415926
#define rad(deg) deg * PI / 180
#define EPSILON 0.0001f
#define ANIMATION_ACTIVATION_TIME 20
#define MAX_DEPTH 7
#define TRANSLATION_SPEED 0.005f
#define OFFSET 1.2f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float angle[3] = { rad(90), rad(210), rad(330) };  // up, left, right

float vertices[10000];   // [9 per triangle] - 3 coords | (x, y, z)
float centers[4000];    // [3 per triangle] - 1 coord  | (x, y, z)
short int levels[1500];  // [1 per triangle] - 1 number |
short int parents[1500]; // [1 per triangle] - 1 number | 0 = up, 1 = left, 2 = rigth
bool reload_colors = false;

unsigned int VBO, VAO;
int cnt = 0, last_idx = 0;

const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "uniform mat4 transform;\n"
  "void main() {\n"
  "  gl_Position = transform * vec4(aPos, 1.0f);\n"
  "}\0";
const char* fragmentShaderSource =
  "#version 330 core\n"
  "uniform vec4 vColor;\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  "  FragColor = vColor;\n"
  "}\0";


// ========================== Sierpinski ==========================

struct Node {
  short int lvl, parent;
  float x, y, size;

  Node() {}
  Node(short int a, float b, float c, float d, short int e = -1)
    : lvl(a), size(b), x(c), y(d), parent(e) {}

  void save_state() {
    // save vertices
    for (int i = 0; i < 3; ++i) {
      vertices[last_idx++] = x + cos(angle[i]) * size;
      vertices[last_idx++] = y + sin(angle[i]) * size;
      vertices[last_idx++] = 0.0f;
    }

    // save center
    centers[cnt * 3] = x;
    centers[cnt * 3 + 1] = y;
    centers[cnt * 3 + 2] = 0.0f;
    // save depth
    levels[cnt] = lvl;
    // save parent
    parents[cnt] = parent;
    cnt++;
  }

  void gen_children(Node* children) {
    for (int i = 0; i < 3; ++i) {
      float newx = x + cos(angle[i]) * size / 2;
      float newy = y + sin(angle[i]) * size / 2;
      children[i] = Node(lvl - 1, size / 2, newx, newy, i);
    }
  }
};

void create_triangle_dfs(Node cur) {
  if (cur.lvl == 0) return;

  cur.save_state();
  // recursion
  Node children[3];
  cur.gen_children(children);

  for (int i = 0; i < 3; ++i)
    create_triangle_dfs(children[i]);
}

void create_triangle_bfs(Node cur) {
  std::queue<Node> q;
  q.push(cur);

  while (!q.empty()) {
    Node cur = q.front();
    q.pop();
    cur.save_state();

    if (cur.lvl == 1) continue;

    Node children[3];
    cur.gen_children(children);

    for (int i = 0; i < 3; ++i)
      q.push(children[i]);
  }
}

// ========================== Main ==========================

int main() {
  std::cout << "Integrantes:\n" <<
            "   Gonzales Navarrete, Mateo\n" <<
            "   Nieto, Miguel\n" <<
            "   Palma Ugarte, Joaquin\n" <<
            "\n" <<
            "Keyboard callbacks:\n" <<
            "   Press down C: Reload colors array\n" << std::endl;

  srand(time(NULL));

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  // glfw window creation
  // --------------------
  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL",
                                        NULL, NULL);

  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // glad: load all OpenGL function pointers
  // ---------------------------------------
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  // check for shader compile errors
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog <<
              std::endl;
  }

  // fragment shader
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  // check for shader compile errors
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog <<
              std::endl;
  }

  // link shaders
  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  // check for linking errors
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // ========================== Make triangles ==========================

  create_triangle_bfs(Node(MAX_DEPTH, 0.9f, 0.0f, 0.0f));
  // create_triangle_dfs(Node(6, 0.9, 0.0f, 0.0f));
  // std::cout << cnt << " " << last_idx << std::endl;

  // ====================================================================

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // uncomment this call to draw in wireframe polygons.
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  // render loop
  // -----------
  int depth = 1;
  int timer = 0;
  int static_cnt = 1;
  glm::vec3 translation_vec[3] = {
    glm::vec3(0.0f, OFFSET, 0.0f),
    glm::vec3(-OFFSET, -OFFSET, 0.0f),
    glm::vec3(OFFSET, -OFFSET, 0.0f)
  };
  bool animating = false;
  int elems_in_level = 1;
  float rotate_degree = 3.0f;

  glm::vec4 colors[MAX_DEPTH]; // 1 color per level in the tree

  for (int i = 0; i < MAX_DEPTH; ++i)
    colors[i] = glm::vec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX,
                          (float)rand() / RAND_MAX, 1.0f);

  glUseProgram(shaderProgram);
  unsigned int color_loc = glGetUniformLocation(shaderProgram, "vColor");
  unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");

  glfwSetKeyCallback(window, key_callback);

  while (!glfwWindowShouldClose(window)) {
    if (reload_colors) {
      for (int i = 0; i < MAX_DEPTH; ++i)
        colors[i] = glm::vec4((float)rand() / RAND_MAX, (float)rand() / RAND_MAX,
                              (float)rand() / RAND_MAX, 1.0f);

      reload_colors = false;
    }

    // input
    // -----
    processInput(window);

    // render
    // ------
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 no_transform = glm::mat4(1.0f);
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(no_transform));

    int drawn_cnt = 0;
    int max_static_color_idx = int(log(static_cnt) / log(3)) + 1;

    // Draw static triangles
    for (int i = 0; i < max_static_color_idx; ++i) {
      glUniform4fv(color_loc, 1, glm::value_ptr(colors[i]));
      glDrawArrays(GL_TRIANGLES, drawn_cnt, 3 * pow(3, i));
      drawn_cnt += 3 * pow(3, i);
    }

    if (animating) {
      glUniform4fv(color_loc, 1, glm::value_ptr(colors[max_static_color_idx]));

      glm::mat4 transform_top = glm::mat4(1.0f);
      transform_top = glm::translate(transform_top, translation_vec[0]);
      transform_top = glm::rotate(transform_top, glm::radians(rotate_degree),
                                  glm::vec3(0.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_top));

      glDrawArrays(GL_TRIANGLES, 3 * static_cnt, elems_in_level);

      glm::mat4 transform_left = glm::mat4(1.0f);
      transform_left = glm::translate(transform_left, translation_vec[1]);
      transform_left = glm::rotate(transform_left, glm::radians(rotate_degree),
                                   glm::vec3(0.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_left));

      glDrawArrays(GL_TRIANGLES, 3 * static_cnt + elems_in_level,
                   elems_in_level);

      glm::mat4 transform_right = glm::mat4(1.0f);
      transform_right = glm::translate(transform_right, translation_vec[2]);
      transform_right = glm::rotate(transform_right, glm::radians(rotate_degree),
                                    glm::vec3(0.0f, 0.0f, 1.0f));
      glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform_right));

      glDrawArrays(GL_TRIANGLES, 3 * static_cnt + 2 * elems_in_level,
                   elems_in_level);

      if (glm::all(glm::lessThan(glm::abs(translation_vec[0]), glm::vec3(EPSILON)))) {
        translation_vec[0] = glm::vec3(0.0f, 1.2f, 0.0f);
        translation_vec[1] = glm::vec3(-1.2f, -1.2f, 0.0f);
        translation_vec[2] = glm::vec3(1.2f, -1.2f, 0.0f);
        animating = false;
        static_cnt += pow(3, depth - 1);
        rotate_degree = 3.0f;
        continue;
      }

      translation_vec[0] += glm::vec3(0.0f, -TRANSLATION_SPEED, 0.0f);
      translation_vec[1] += glm::vec3(TRANSLATION_SPEED, TRANSLATION_SPEED, 0.0f);
      translation_vec[2] += glm::vec3(-TRANSLATION_SPEED, TRANSLATION_SPEED, 0.0f);

      // std::cout << "rotate: " << rotate_degree << std::endl;
      rotate_degree += 3.0;
    }
    else {
      ++timer;

      if (timer == ANIMATION_ACTIVATION_TIME && depth < MAX_DEPTH) {
        timer = 0;
        elems_in_level = pow(3, depth);
        ++depth;
        animating = true;
      }
    }

    // std::cout << translation_vec[0].x << " " << translation_vec[0].y << "\n";
    // std::cout << translation_vec[1].x << " " << translation_vec[1].y << "\n";
    // std::cout << translation_vec[2].x << " " << translation_vec[2].y << "\n" <<
    // std::endl;

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // optional: de-allocate all resources once they've outlived their purpose:
  // ------------------------------------------------------------------------
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  // glfw: terminate, clearing all previously allocated GLFW resources.
  // ------------------------------------------------------------------
  glfwTerminate();
  return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_C && action == GLFW_PRESS)
    reload_colors = true;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  // make sure the viewport matches the new window dimensions; note that width and
  // height will be significantly larger than specified on retina displays.
  glViewport(0, 0, width, height);
}
