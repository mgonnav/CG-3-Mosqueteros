#ifndef CUBITO_CUBO_HPP
#define CUBITO_CUBO_HPP

#include <vector>
#include <memory>

#include "Cubito.hpp"
#include "Shader.h"
#include "Rendered.hpp"

class Cubo {

 public:
	
	Cubo();

	std::vector<std::shared_ptr<Cubito>> cubitos;
	void Draw(const Rendered&, const glm::mat4&, const glm::mat4&, const glm::mat4&, 
		glm::vec3, const unsigned int&, const unsigned int&, bool);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Cubo::Cubo() {
	cubitos.resize(28);
}

void Cubo::Draw(const Rendered& rendered, 
	const glm::mat4& model,
	const glm::mat4& view,
	const glm::mat4& projection,
	glm::vec3 camera_position,
	const unsigned int &cube_map_night,
	const unsigned int &cube_map_ocean,
	bool background) {
	for (int i = 1; i <= 27; ++i)
		this->cubitos[i]->Draw(rendered, model, view, projection, 
			camera_position, cube_map_night, cube_map_ocean, background);
}

#endif // CUBITO_CUBO_HPP
