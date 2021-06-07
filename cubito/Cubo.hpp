#ifndef CUBO_H
#define CUBO_H

#include "Cubito.hpp"
#include "Shader.h"

#include <vector>
#include <memory>

class Cubo {
 public:
	Cubo();
	std::vector<std::shared_ptr<Cubito>> cubitos;
	void Draw(glm::mat4&, glm::mat4&, glm::mat4&);
	void Move(int);
};

// =========================================================
// =========================================================
// =========================================================

Cubo::Cubo() {
	cubitos.resize(28);
}
void Cubo::Draw(glm::mat4& model, glm::mat4& view, glm::mat4& projection) {
	std::cout << "debug 2" << std::endl;
	for (auto &cubito : cubitos) {
		std::cout << "debug 3" << std::endl;
		cubito->DrawSprite(model, view, projection);
	}
}

void Cubo::Move (int move) {
	switch (move)	{
	case 1: {std::cout << "MOVE VERTICAL LEFT - UP" << std::endl; break; }
	case 2: {std::cout << "MOVE VERTICAL LEFT - DOWN" << std::endl; break; }
	case 3: {std::cout << "MOVE VERTICAL MID - DOWN" << std::endl; break; }
	case 4: {std::cout << "MOVE VERTICAL MID - UP" << std::endl; break; }
	case 5: {std::cout << "MOVE VERTICAL RIGHT - UP" << std::endl; break; }
	case 6: {std::cout << "MOVE VERTICAL RIGHT - DOWN" << std::endl; break; }
	case 7: {std::cout << "MOVE HORIZONTAL UP- LEFT" << std::endl; break; }
	case 8: {std::cout << "MOVE HORIZONTAL UP - RIGHT" << std::endl; break; }
	case 9: {std::cout << "MOVE HORIZONTAL MID - LEFT" << std::endl; break; }
	case 10: {std::cout << "MOVE HORIZONTAL MID - RIGHT" << std::endl; break; }
	case 11: {std::cout << "MOVE HORIZONTAL DOWN - LEFT" << std::endl; break; }
	case 12: {std::cout << "MOVE HORIZONTAL DOWN - RIGHT" << std::endl; break; }
	default: {	std::cout << "THIS DOESNT PRINT" << std::endl; break; }
	}
};

#endif // CUBO_H
