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
	void Draw(Rendered&, glm::mat4&, glm::mat4&, glm::mat4&);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Cubo::Cubo() {
	cubitos.resize(28);
}

void Cubo::Draw(Rendered& rendered, 
	glm::mat4& model, 
	glm::mat4& view, 
	glm::mat4& projection) {
	for (int i = 1; i <= 27; ++i)
		this->cubitos[i]->Draw(rendered, model, view, projection);
}

#endif // CUBITO_CUBO_HPP
