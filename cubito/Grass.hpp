#ifndef CUBITO_GRASS_HPP
#define CUBITO_GRASS_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>
#include <vector>

#include "Shader.h"
#include "Rendered.hpp"

class Grass {

private:

	int id = -1;
	Shader shader;
	Texture texture1;
	unsigned int quadVAO = -1;
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glm::mat4 GetPositionOnWorld(glm::mat4&);

	std::vector<glm::vec3> vegetation {
		glm::vec3(2.0f, -1.5f, 0.5f),
		glm::vec3(2.5f, -1.5f, 1.51f),
		glm::vec3(1.0f, -1.5f, 1.7f),
		glm::vec3(-0.3f, -1.5f, -2.3f),
		glm::vec3(3.3f, -1.5f, -2.3f),
		glm::vec3(4.3f, -1.5f, 2.3f),
		glm::vec3(8.3f, -1.5f, 2.3f),
		glm::vec3(8.3f, -1.5f, 4.3f),
		glm::vec3(0.5f, -1.5f, -0.6f)
	};

public:

	Grass(Texture, const Shader&, int);
	Grass() {}
  ~Grass();

	void InitialRender();
	void Draw(glm::mat4&, glm::mat4&, glm::mat4&);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Grass::Grass(
	Texture new_texture1,
	const Shader& shader,
	int new_id) :
	texture1(new_texture1),
	shader(shader),
	id(new_id) {
	this->InitialRender();
}

Grass::~Grass() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Grass::Draw(
	glm::mat4& model, 
	glm::mat4& view, 
	glm::mat4& projection) {
	
	this->shader.Use();

	unsigned int view_location = glGetUniformLocation(this->shader.id, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

	unsigned int projection_location = glGetUniformLocation(this->shader.id, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(this->quadVAO);
	glActiveTexture(GL_TEXTURE0);
	texture1.Bind();

	for (unsigned int i = 0; i < this->vegetation.size(); i++) {
		glm::mat4 t_model = model;
		t_model = glm::translate(t_model, this->vegetation[i]);
		this->shader.SetMatrix4("model", t_model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
}

void Grass::InitialRender() {
  unsigned int VBO;

	float transparentVertices[] = {
		// positions         // texture Coords 
		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		0.0f, -0.5f,  0.0f,  0.0f,  1.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,

		0.0f,  0.5f,  0.0f,  0.0f,  0.0f,
		1.0f, -0.5f,  0.0f,  1.0f,  1.0f,
		1.0f,  0.5f,  0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(transparentVertices), transparentVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

}

#endif // CUBITO_GRASS_HPP
