#ifndef CUBITO_H
#define CUBITO_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "Shader.h"


class Cubito
{
private:
	Shader shader;
	unsigned int quadVAO;
	glm::vec3 my_position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 MyPositionOnWorld(glm::mat4&);
	glm::vec3 color1;
	glm::vec3 color2;
	glm::vec3 color3;
	int id;
	glm::mat4 my_rotation = glm::mat4(1.0f);

public:
	void InitialRender();
	Cubito(Shader&, glm::vec3, int, glm::vec3, glm::vec3, glm::vec3);
	Cubito() {}
	~Cubito();
	void DrawSprite(glm::mat4&, glm::mat4&, glm::mat4&);
	void Translate(glm::vec3);
	void Rotate(int);
	void MyData();
};

//==============================================================================================

Cubito::Cubito (Shader& shader,
								glm::vec3 first_position,
								int new_id,
								glm::vec3 color1n = glm::vec3(0.1f, 0.1f, 0.1f),
								glm::vec3 color2n = glm::vec3(0.1f, 0.1f, 0.1f),
								glm::vec3 color3n = glm::vec3(0.1f, 0.1f, 0.1f)) {
	this->id = new_id;
	this->shader = shader;
	my_position = first_position;
	this->color1 = color1n;
	this->color2 = color2n;
	this->color3 = color3n;
	this->InitialRender();
}

Cubito::~Cubito()
{
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Cubito::DrawSprite(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
	this->shader.use();

	glm::mat4 my_position_on_world = MyPositionOnWorld(model);
	
	unsigned int model_location = glGetUniformLocation(this->shader.ID, "model");
	glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(my_position_on_world));
	
	unsigned int view_location = glGetUniformLocation(this->shader.ID, "view");
	glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));
	
	unsigned int projection_location = glGetUniformLocation(this->shader.ID, "projection");
	glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

	glBindVertexArray(this->quadVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

glm::mat4 Cubito::MyPositionOnWorld(glm::mat4& model) {

	glm::mat4 my_position_on_world = glm::translate(model, my_position);
	
	my_position_on_world =  my_position_on_world * my_rotation;
	
	return  my_position_on_world;
}

void Cubito::Translate(glm::vec3 new_translate) {
	this->my_position = new_translate;
}

void Cubito::Rotate(int around_axis) {
	// kAroundXLeft = 1;
	// kAroundXRight = 2;
	// kAroundYLeft = 3;
	// kAroundYRight = 4;
	// kAroundZLeft = 5;
	// kAroundZRight = 6;
	switch (around_axis) {
		case 1: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(1.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
		case 2: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-1.0f),
				glm::vec3(1.0f, 0.0f, 0.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
		case 3: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-1.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
		case 4: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(1.0f),
				glm::vec3(0.0f, 1.0f, 0.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
		case 5: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
		case 6: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-1.0f),
				glm::vec3(0.0f, 0.0f, 1.0f));

			my_rotation = temporal * my_rotation;

			break;
		}
	}
}

void Cubito::InitialRender() {
  unsigned int VBO;


	float vertices_1[28][288] = {
	{
			// BACK
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

	// FRONTAL
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

	// LATERAL LEFT
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	// LATERAL RIGHT
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	 // DOWN
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

	// UP
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 0 NO USED
	{
			// BACK
			-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
			 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
			 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
			 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
			-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
			-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

			// FRONTAL *
			-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
			 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
			 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
			 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
			-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
			-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

			// LATERAL LEFT *
			-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
			-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
			-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
			-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
			-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
			-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

			// LATERAL RIGHT
			 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
			 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
			 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
			 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
			 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
			 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

			 // DOWN
			-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
			 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
			 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
			 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
			-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
			-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

			// UP *
			-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
			 0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
			 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
			 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
			-0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
			-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f
			}, // 1
	{
		// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f
	}, // 2
	{
	// BACK
	-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
	 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

	// FRONTAL
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

	// LATERAL LEFT
	-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

	// LATERAL RIGHT
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	 // DOWN
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

	// UP
	-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f
}, // 3
	{
		// BACK
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

	// FRONTAL
	-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

	// LATERAL LEFT
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	// LATERAL RIGHT
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	 // DOWN
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

	// UP
	-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f
	}, // 4
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f
		}, // 5
	{
			// BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f
		}, // 6
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f
		}, // 7
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f
		 }, // 8
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f
		 }, // 9
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		 }, // 10
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 11
	{
			// BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 12
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 13
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 14
	{
			// BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 15
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		 }, // 16
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		 }, // 17
	{
			 // BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		 }, // 18
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 19
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 20
	{
			// BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 21
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 22
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 23
	{
			// BACK
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 24
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 25
	{
			// BACK
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// FRONTAL
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

		// LATERAL LEFT
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

		// LATERAL RIGHT
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
		 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,

		 // DOWN
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
		 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
		-0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
		-0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,

		// UP
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
		 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
		-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
		-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
		}, // 26
	{
		// BACK
	-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,
	 0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 1.0f, 1.0f,
	-0.2f,  0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, color1.x, color1.y, color1.z, 0.0f, 0.0f,

	// FRONTAL
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,

	// LATERAL LEFT
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,

	// LATERAL RIGHT
	 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,
	 0.2f,  0.2f, -0.2f, color2.x, color2.y, color2.z, 1.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, color2.x, color2.y, color2.z, 0.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, color2.x, color2.y, color2.z, 0.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, color2.x, color2.y, color2.z, 1.0f, 0.0f,

	 // DOWN
	-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,
	 0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 1.0f, 1.0f,
	 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
	 0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 1.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, color3.x, color3.y, color3.z, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, color3.x, color3.y, color3.z, 0.0f, 1.0f,

	// UP
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f,
	 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f
	}, // 27
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 1152, vertices_1[this->id], GL_STATIC_DRAW);
	glBindVertexArray(this->quadVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

}

void Cubito::MyData() {
	std::cout << " My_rotation: " << this->my_rotation << std::endl;
	std::cout << " My_position: " << this->my_position << std::endl;
}
#endif // CUBITO_H