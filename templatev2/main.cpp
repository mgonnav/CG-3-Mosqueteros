/*****
 Computacion Grafica: CCOMP 7-1
 * Gonzales Navarrete Mateo
 * Nieto Rosas Miguel
 * Palma Ugarte Joaquin
 *****/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "buildShaders.h"
#include "vertices_colors.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 700;
const unsigned int SCR_HEIGHT = 700;

const int N = 500; // number of figures
const int MV = 500; // maximum number of vertexs in one figure 

unsigned int VBO, VAO, EBO[N];

unsigned int figures[N][MV] = {

	/*
	*** MATEO FIGURES
	*/

	{30290,30310,34310,}, // FIGURE 0
	{},// FIGURE 1
	{},// FIGURE 2
	{},// FIGURE 3
	{},// FIGURE 4
	{},// FIGURE 5
	{},// FIGURE 6
	{},// FIGURE 7
	{},// FIGURE 8
	{},// FIGURE 9
	{},// FIGURE 10
	{},// FIGURE 11
	{},// FIGURE 12
	{},// FIGURE 13
	{},// FIGURE 14
	{},// FIGURE 15
	{},// FIGURE 16
	{},// FIGURE 17
	{},// FIGURE 18
	{},// FIGURE 19
	{},// FIGURE 20
	{},// FIGURE 21
	{},// FIGURE 22
	{},// FIGURE 23
	{},// FIGURE 24
	{},// FIGURE 25
	{},// FIGURE 26
	{},// FIGURE 27
	{},// FIGURE 28
	{},// FIGURE 29
	{},// FIGURE 30
	{},// FIGURE 31
	{},// FIGURE 32
	{},// FIGURE 33
	{},// FIGURE 34
	{},// FIGURE 35
	{},// FIGURE 36
	{},// FIGURE 37
	{},// FIGURE 38
	{},// FIGURE 39
	{},// FIGURE 40
	{},// FIGURE 41
	{},// FIGURE 42
	{},// FIGURE 43
	{},// FIGURE 44
	{},// FIGURE 45
	{},// FIGURE 46
	{},// FIGURE 47
	{},// FIGURE 48
	{},// FIGURE 49
	{},// FIGURE 50

	/*
	*** JOAQUIN FIGURES
	*/

	{},// FIGURE 51
	{},// FIGURE 52
	{},// FIGURE 53
	{},// FIGURE 54
	{},// FIGURE 55
	{},// FIGURE 56
	{},// FIGURE 57
	{},// FIGURE 58
	{},// FIGURE 59
	{},// FIGURE 60
	{},// FIGURE 61
	{},// FIGURE 62
	{},// FIGURE 63
	{},// FIGURE 64
	{},// FIGURE 65
	{},// FIGURE 66
	{},// FIGURE 67
	{},// FIGURE 68
	{},// FIGURE 69
	{},// FIGURE 70
	{},// FIGURE 71
	{},// FIGURE 72
	{},// FIGURE 73
	{},// FIGURE 74
	{},// FIGURE 75
	{},// FIGURE 76
	{},// FIGURE 77
	{},// FIGURE 78
	{},// FIGURE 79
	{},// FIGURE 80
	{},// FIGURE 81
	{},// FIGURE 82
	{},// FIGURE 83
	{},// FIGURE 84
	{},// FIGURE 85
	{},// FIGURE 86
	{},// FIGURE 87
	{},// FIGURE 88
	{},// FIGURE 89
	{},// FIGURE 90
	{},// FIGURE 91
	{},// FIGURE 92
	{},// FIGURE 93
	{},// FIGURE 94
	{},// FIGURE 95
	{},// FIGURE 96
	{},// FIGURE 97
	{},// FIGURE 98
	{},// FIGURE 99
	{},// FIGURE 100

	/*
	*** MIGUEL FIGURES
	*/

	{},// FIGURE 101
	{},// FIGURE 102
	{},// FIGURE 103
	{},// FIGURE 104
	{},// FIGURE 105
	{},// FIGURE 106
	{},// FIGURE 107
	{},// FIGURE 108
	{},// FIGURE 109
	{},// FIGURE 110
	{},// FIGURE 111
	{},// FIGURE 112
	{},// FIGURE 113
	{},// FIGURE 114
	{},// FIGURE 115
	{},// FIGURE 116
	{},// FIGURE 117
	{},// FIGURE 118
	{},// FIGURE 119
	{},// FIGURE 120
	{},// FIGURE 121
	{},// FIGURE 122
	{},// FIGURE 123
	{},// FIGURE 124
	{},// FIGURE 125
	{},// FIGURE 126
	{},// FIGURE 127
	{},// FIGURE 128
	{},// FIGURE 129
	{},// FIGURE 130
	{},// FIGURE 131
	{},// FIGURE 132
	{},// FIGURE 133
	{},// FIGURE 134
	{},// FIGURE 135
	{},// FIGURE 136
	{},// FIGURE 137
	{},// FIGURE 138
	{},// FIGURE 139
	{},// FIGURE 140
	{},// FIGURE 141
	{},// FIGURE 142
	{},// FIGURE 143
	{},// FIGURE 144
	{},// FIGURE 145
	{},// FIGURE 146
	{},// FIGURE 147
	{},// FIGURE 148
	{},// FIGURE 149
	{},// FIGURE 150

	/*
	*** EXTRA FIGURES, PLEASE CONTINUE THE STANDARD
	*/

	{},// FIGURE 151
	{},// FIGURE 152
	{},// FIGURE 153
	{},// FIGURE 154
	{},// FIGURE 155
	{},// FIGURE 156
	{},// FIGURE 157
	{},// FIGURE 158
	{},// FIGURE 159
	{},// FIGURE 160
};

void drawWithEBO(int EBOindex, int vertexNumber,
	GLenum primitive_type = GL_TRIANGLES) {
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

	buildingShaders();

	startVertexInput();

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);

		// code to draw from here
		glUseProgram(coloryellow3);
		drawWithEBO(0, MV);

		// code to draw until here
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(N, EBO);

	glDeleteProgram(colorred1);
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
