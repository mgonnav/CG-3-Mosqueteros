#ifndef CUBITO_CUBITO_HPP
#define CUBITO_CUBITO_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include "Shader.h"
#include "Rendered.hpp"

class Cubito {

private:

	int id = -1;
  Shader shader;
  Shader shader2;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Texture texture4;
	unsigned int quadVAO = -1;
	glm::vec3 color1 = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 color2 = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::vec3 color3 = glm::vec3(0.1f, 0.1f, 0.1f);
	glm::mat4 rotation = glm::mat4(1.0f);
	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
	
	glm::mat4 GetPositionOnWorld(glm::mat4&);

public:

	Cubito(Texture, Texture, Texture, Texture, const Shader&, const Shader&,
				 glm::vec3, int, glm::vec3, glm::vec3, glm::vec3);
	Cubito() {}
  ~Cubito();

  bool change_fragment = false;
	void AllData();
	void InitialRender();
	void RotateAround(int around_axis, float angle);
	void CorrectRotate();
	void SetPosition(glm::vec3);
	void Draw(const Rendered&, const glm::mat4&, const glm::mat4&, const glm::mat4&, 
    glm::vec3, const unsigned int&, const unsigned int&, bool);
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Cubito::Cubito (
	Texture new_texture1,
	Texture new_texture2,
	Texture new_texture3,
	Texture new_texture4,
  const Shader& shader,
  const Shader& shader2,
	glm::vec3 first_position,
	int new_id,
	glm::vec3 color1n = glm::vec3(0.1f, 0.1f, 0.1f),
	glm::vec3 color2n = glm::vec3(0.1f, 0.1f, 0.1f),
	glm::vec3 color3n = glm::vec3(0.1f, 0.1f, 0.1f)) :
	texture1(new_texture1),
	texture2(new_texture2),
	texture3(new_texture3),
	texture4(new_texture4),
	id(new_id),
  shader(shader),
  shader2(shader2),
	position(first_position),
	color1(color1n),
	color2(color2n),
	color3(color3n) {
	this->InitialRender();
}

Cubito::~Cubito() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void Cubito::Draw(const Rendered &rendered,
  const glm::mat4& model,
  const glm::mat4& view,
  const glm::mat4& projection,
	glm::vec3 camera_position,
  const unsigned int &cube_map_night,
  const unsigned int &cube_map_ocean,
  bool background) {
	
  Shader shader_run = this->shader;

  if (this->change_fragment) shader_run = this->shader2;

  shader_run.Use();

  glm::mat4 position_on_world = glm::translate(model, position);

  position_on_world = position_on_world * rotation;
  
  unsigned int model_location = glGetUniformLocation(shader_run.id, "model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(position_on_world));

  unsigned int view_location = glGetUniformLocation(shader_run.id, "view");
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

  unsigned int projection_location = glGetUniformLocation(shader_run.id, "projection");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

  unsigned int camera_location = glGetUniformLocation(shader_run.id, "cameraPos");
  glUniform3f(camera_location, camera_position.x,camera_position.y,camera_position.z);
  // cubes
  glBindVertexArray(this->quadVAO);

  if (this->change_fragment) {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();

    glActiveTexture(GL_TEXTURE0);
    if (background) glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_night);
    else glBindTexture(GL_TEXTURE_CUBE_MAP, cube_map_ocean);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
    return;
  }
  
  switch (this->id) {
  case 3: {
    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 6: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 9: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 12: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 15: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 18: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 21: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 24: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 27: {
    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }

  case 2: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 5: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 8: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 11: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 17: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 20: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 23: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 26: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }

  case 1: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 4: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 7: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 10: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 13: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 16: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 19: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 22: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  case 25: {
    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glActiveTexture(GL_TEXTURE0);
    texture1.Bind();
    glDrawArrays(GL_TRIANGLES, 6, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 12, 6);

    glActiveTexture(GL_TEXTURE0);
    texture2.Bind();
    glDrawArrays(GL_TRIANGLES, 18, 6);

    glActiveTexture(GL_TEXTURE0);
    texture3.Bind();
    glDrawArrays(GL_TRIANGLES, 24, 6);

    glActiveTexture(GL_TEXTURE0);
    texture4.Bind();
    glDrawArrays(GL_TRIANGLES, 30, 6);
    break;
  }
  }
  
  
  glBindVertexArray(0);

}

glm::mat4 Cubito::GetPositionOnWorld(glm::mat4& model) {

	glm::mat4 position_on_world = glm::translate(model, position);
	
	position_on_world =  position_on_world * rotation;
	
	return  position_on_world;
}

void Cubito::SetPosition(glm::vec3 new_position) {
  this->position = new_position;
}

void Cubito::RotateAround(int around_axis, float angle) {
	switch (around_axis) {
		case 1: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(angle),
				glm::vec3(1.0f, 0.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -1: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-angle),
				glm::vec3(1.0f, 0.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case 2: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-angle),
				glm::vec3(0.0f, 1.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -2: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(angle),
				glm::vec3(0.0f, 1.0f, 0.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case 3: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(angle),
				glm::vec3(0.0f, 0.0f, 1.0f));

			this->rotation = temporal * rotation;

			break;
		}
		case -3: {
			glm::mat4 temporal = glm::mat4(1.0f);
			temporal = glm::rotate(temporal,
				glm::radians(-angle),
				glm::vec3(0.0f, 0.0f, 1.0f));

			this->rotation = temporal * rotation;

			break;
		}
	}
}

void Cubito::CorrectRotate() {
		this->rotation = glm::mat4(1.0f);
}

void Cubito::InitialRender() {
  unsigned int VBO;

	float vertices_1[396] = {
// position          // color          // texture  // normals
		// BACK
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

// FRONTAL
-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

// LATERAL LEFT
-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

// LATERAL RIGHT
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

 // DOWN
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
 0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
 0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
-0.2f, -0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
-0.2f, -0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

// UP
-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
 0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
 0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
-0.2f,  0.2f,  0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
-0.2f,  0.2f, -0.2f, 0.1f, 0.1f, 0.1f, 0.0f, 1.0f, 0.0f,  1.0f,  0.0f
	};

	glGenVertexArrays(1, &this->quadVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), &vertices_1, GL_STATIC_DRAW);
	glBindVertexArray(this->quadVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	// normal
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

}

void Cubito::AllData() {
	std::cout << " rotation: " << this->rotation << std::endl;
	std::cout << " position: " << this->position << std::endl;
}

#endif // CUBITO_CUBITO_HPP
