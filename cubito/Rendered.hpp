#ifndef CUBITO_RENDERER_HPP
#define CUBITO_RENDERER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.h"
  
class Rendered {

 public:

  Rendered(const Shader &shader);
  ~Rendered();

  void DrawSprite(int, unsigned int, Texture&, Texture&, Texture&, Texture&, 
                    glm::vec3, glm::mat4, glm::mat4, glm::mat4, glm::mat4);

 private:

  Shader shader;
  unsigned int quadVAO = -1;
};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

Rendered::Rendered(const Shader &shader) {
    this->shader = shader;
}

Rendered::~Rendered() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void Rendered::DrawSprite(int cub_id, unsigned int nquadVAO,
  Texture &texture1,
  Texture &texture2,
  Texture &texture3,
  Texture &texture4,
  glm::vec3 position,
  glm::mat4 rotate,
  glm::mat4 model,
  glm::mat4 view,
  glm::mat4 projection) {

  this->shader.Use();

  glm::mat4 position_on_world = glm::translate(model, position);

  position_on_world = position_on_world * rotate;

  unsigned int model_location = glGetUniformLocation(this->shader.id, "model");
  glUniformMatrix4fv(model_location, 1, GL_FALSE, glm::value_ptr(position_on_world));

  unsigned int view_location = glGetUniformLocation(this->shader.id, "view");
  glUniformMatrix4fv(view_location, 1, GL_FALSE, glm::value_ptr(view));

  unsigned int projection_location = glGetUniformLocation(this->shader.id, "projection");
  glUniformMatrix4fv(projection_location, 1, GL_FALSE, glm::value_ptr(projection));

  glBindVertexArray(nquadVAO);
  
  switch (cub_id) {
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

#endif // CUBITO_RENDERER_HPP
