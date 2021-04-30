#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <queue>
#include <math.h>

#define PI 3.1415926
#define rad(deg) deg * PI / 180

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float angle[3] = {rad(90), rad(210), rad(330)};  // up, left, right

float vertices[5000];   // [9 per triangle] - 3 coords | (x, y, z)
float centers[2000];    // [3 per triangle] - 1 coord  | (x, y, z)
short int levels[1000];  // [1 per triangle] - 1 number |
short int parents[1000]; // [1 per triangle] - 1 number | 0 = up, 1 = left, 2 = rigth

unsigned int VBO, VAO;
int cnt = 0, last_idx = 0;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


// ========================== Sierpinski ==========================

struct Node{
  short int lvl, parent;
  float x, y, size;

  Node(){}
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
    centers[cnt*3] = x;
    centers[cnt*3+1] = y;
    centers[cnt*3+2] = 0.0f;
    // save depth
    levels[cnt] = lvl;
    // save parent
    parents[cnt] = parent;
    cnt++;
  }

  void gen_children(Node* children) {
    for (int i = 0; i < 3; ++i) {
      float newx = x + cos(angle[i]) * size/2;
      float newy = y + sin(angle[i]) * size/2;
      children[i] = Node(lvl-1, size/2, newx, newy, i);
    }
  }
};

// DFS
void create_triangle_dfs(Node cur) {  
  if (cur.lvl == 0) return;
  cur.save_state();
  // recursion
  Node children[3];
  cur.gen_children(children);
  for(int i = 0; i < 3; ++i)
    create_triangle_dfs(children[i]);
}

// BFS
void create_triangle_bfs(Node cur) {
  std::queue<Node> q;
  q.push(cur);
  while(!q.empty()) {
    Node cur = q.front();
    q.pop();
    cur.save_state();
    if(cur.lvl == 1) continue;
    Node children[3];
    cur.gen_children(children);
    for(int i = 0; i < 3; ++i)
      q.push(children[i]);
  }
}

// ========================== Main ==========================

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
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
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
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
    
    //create_triangle_bfs(Node(5, 0.9, 0.0f, 0.0f));
    create_triangle_dfs(Node(6, 0.9, 0.0f, 0.0f));
    std::cout << cnt << " " << last_idx << std::endl;

    // ====================================================================

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    
    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    // render loop
    // -----------
    float x = 0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3*x);
        x += 0.5;
        if (x > cnt) x = 0;
        // glBindVertexArray(0); // no need to unbind it every time 
 
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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
