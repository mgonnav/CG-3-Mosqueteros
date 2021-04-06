const char* vertexShaderSource =
  "#version 330 core\n"
  "layout (location = 0) in vec3 aPos;\n"
  "void main() {\n"
  " gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
  "}\0";

const char* fragmentShaderSource =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
  "}\n";

const char* fragmentShaderGreen =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(0.196f, 0.98f, 0.196f, 1.0f);\n"
  "}\n";

const char* fragmentShaderGreenDarker =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(0.146f, 0.55f, 0.146f, 1.0f);\n"
  "}\n";

const char* fragmentShaderRed =
  "#version 330 core\n"
  "out vec4 FragColor;\n"
  "void main() {\n"
  " FragColor = vec4(0.8f, 0.0f, 0.0f, 1.0f);\n"
  "}\n";

const char* fragmentShader1Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.4f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 1.0f, 0.0f, 0.5f);\n"
"}\n\0";
