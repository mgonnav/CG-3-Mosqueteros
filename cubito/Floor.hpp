#ifndef CUBITO_FLOOR_HPP
#define CUBITO_FLOOR_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "Shader.h"
#include "Rendered.hpp"

class Floor {

private:

	int id = -1;
	Shader shader;
	Texture texture1;
	unsigned int quadVAO = -1;
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glm::mat4 GetPositionOnWorld(glm::mat4&);

public:

	Floor(Texture, const Shader&, int);
	Floor() {}
  ~Floor();

	void InitialRender();
	void Draw(Rendered&, glm::mat4&, glm::mat4&, glm::mat4&);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Floor::Floor(
	Texture new_texture1,
	const Shader& shader,
	int new_id) :
	texture1(new_texture1),
	shader(shader),
	id(new_id) {
	this->InitialRender();
}

Floor::~Floor() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Floor::Draw(Rendered &rendered,
	glm::mat4& model, 
	glm::mat4& view, 
	glm::mat4& projection) {
	
	this->shader.Use();

	//this->shader.SetMatrix4("model", glm::mat4(1.0f));
	unsigned int model_location = glGetUniformLocation(this->shader.id, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(glm::mat4(1.0f)));

	unsigned int view_location = glGetUniformLocation(this->shader.id, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

	unsigned int projection_location = glGetUniformLocation(this->shader.id, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(this->quadVAO);

	glActiveTexture(GL_TEXTURE0);
	texture1.Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);

}

void Floor::InitialRender() {
  unsigned int VBO;

	float planeVertices[] = {
		// positions          // texture Coords
		 10.0f, -2.0f,  10.0f,  2.0f, 0.0f,
		-10.0f, -2.0f,  10.0f,  0.0f, 0.0f,
		-10.0f, -2.0f, -10.0f,  0.0f, 2.0f,

		 10.0f, -2.0f,  10.0f,  2.0f, 0.0f,
		-10.0f, -2.0f, -10.0f,  0.0f, 2.0f,
		 10.0f, -2.0f, -10.0f,  2.0f, 2.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->quadVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindVertexArray(0);

}

#endif // CUBITO_FLOOR_HPP
