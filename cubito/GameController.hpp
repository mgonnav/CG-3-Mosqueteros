#ifndef CUBITO_GAME_CONTROLLER_HPP
#define CUBITO_GAME_CONTROLLER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <algorithm>
#include <iostream>
#include <tuple>
#include <sstream>
#include <vector>

#include "Rendered.hpp"
#include "Resources.hpp"
#include "Setting.hpp"

class GameController {

 public:
  
  // COntructor and destructor
  GameController(unsigned int, unsigned int);
  ~GameController();
      
  // Things on game
  Rendered* Renderer = nullptr;
  Cubo rubick_cube;

  // General variables of game_controller
  unsigned int width = 0;
  unsigned int height = 0;
  glm::mat4 model = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  
  // Variables that control key press
  bool can_press = true;
  bool some_movement = false;
  bool keys_press[1024]{false};
  bool keys_already_press[1024]{false};

  // Variables to control rotations rubick_cube
  bool U_ANIM = false, U_ANIM_I = false;
  bool U_PRIME_ANIM = false, U_PRIME_ANIM_I = false;
  bool D_ANIM = false, D_ANIM_I = false;
  bool D_PRIME_ANIM = false, D_PRIME_ANIM_I = false;
  bool L_PRIME_ANIM = false, L_PRIME_ANIM_I = false;
  bool L_ANIM = false, L_ANIM_I = false;
  bool R_ANIM = false, R_ANIM_I = false;
  bool R_PRIME_ANIM = false, R_PRIME_ANIM_I = false;
  bool F_ANIM = false, F_ANIM_I = false;
  bool F_PRIME_ANIM = false, F_PRIME_ANIM_I = false;
  bool B_ANIM = false, B_ANIM_I = false;
  bool B_PRIME_ANIM = false, B_PRIME_ANIM_I = false;
  float move_angles[9] = {
  135.0f,
  90.0f,
  45.0f,
  180.0f,
  0.0f,
  0.0f,
  225.0f,
  270.0f,
  315.0f,
    };
    
  // Functions of game
  void Init();
  void Render();
  void ResetAngles();
  void PlayAnimation();
  void UpdateGame(float);
  void ProcessInput(float);
  void UpdateMatrices(glm::mat4, glm::mat4, glm::mat4);
  glm::vec3 CalculateTranslatePosition(float, Move, const float&);

};

// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------

GameController::GameController(unsigned int width, unsigned int height)
  : keys_press(), 
  keys_already_press(), 
  width(width), 
  height(height) { 
}

GameController::~GameController() {
  delete Renderer;
}

void GameController::Init() {
  
  // Loading programs
  Resources::LoadShader("src/shaders/cubito.vs", "src/shaders/cubito.fs", nullptr, "cubito");
  
  // Loading textures
  Resources::LoadTexture("src/images/negro.png", true, "negro");
  Resources::LoadTexture("src/images/amarillo.png", true, "yellow");
  Resources::LoadTexture("src/images/red.png", true, "red");
  Resources::LoadTexture("src/images/white.png", true, "white");
  Resources::LoadTexture("src/images/blue.png", true, "blue");
  Resources::LoadTexture("src/images/naranja.png", true, "orange");
  Resources::LoadTexture("src/images/green.png", true, "green");
  
  Resources::LoadTexture("src/images/piksar1.png", true, "piksar1");
  Resources::LoadTexture("src/images/piksar2.png", true, "piksar2");
  Resources::LoadTexture("src/images/piksar3.png", true, "piksar3");
  Resources::LoadTexture("src/images/piksar4.png", true, "piksar4");
  Resources::LoadTexture("src/images/piksar5.png", true, "piksar5");
  Resources::LoadTexture("src/images/piksar6.png", true, "piksar6");
  Resources::LoadTexture("src/images/piksar7.png", true, "piksar7");
  Resources::LoadTexture("src/images/piksar8.png", true, "piksar8");
  Resources::LoadTexture("src/images/piksar9.png", true, "piksar9");

  Resources::LoadTexture("src/images/yi1.png", true, "yi1");
  Resources::LoadTexture("src/images/yi2.png", true, "yi2");
  Resources::LoadTexture("src/images/yi3.png", true, "yi3");
  Resources::LoadTexture("src/images/yi4.png", true, "yi4");
  Resources::LoadTexture("src/images/yi5.png", true, "yi5");
  Resources::LoadTexture("src/images/yi6.png", true, "yi6");
  Resources::LoadTexture("src/images/yi7.png", true, "yi7");
  Resources::LoadTexture("src/images/yi8.png", true, "yi8");
  Resources::LoadTexture("src/images/yi9.png", true, "yi9");
  
  Resources::LoadTexture("src/images/ucsp1.png", true, "ucsp1");
  Resources::LoadTexture("src/images/ucsp2.png", true, "ucsp2");
  Resources::LoadTexture("src/images/ucsp3.png", true, "ucsp3");
  Resources::LoadTexture("src/images/ucsp4.png", true, "ucsp4");
  Resources::LoadTexture("src/images/ucsp5.png", true, "ucsp5");
  Resources::LoadTexture("src/images/ucsp6.png", true, "ucsp6");
  Resources::LoadTexture("src/images/ucsp7.png", true, "ucsp7");
  Resources::LoadTexture("src/images/ucsp8.png", true, "ucsp8");
  Resources::LoadTexture("src/images/ucsp9.png", true, "ucsp9");

  Resources::LoadTexture("src/images/background.jpg", false, "background");

  // Assing textures integers
  Resources::GetShader("cubito").Use().SetInteger("main_image_texture", 0);
  Resources::GetShader("cubito").Use().SetInteger("background_texture", 1);

  // Create main Rendered
  this->Renderer = new Rendered(Resources::GetShader("cubito"));

  // RANDOM COLOR TO INIT RUBICK CUBE
  std::vector<glm::vec3> input_colors;
  fill_n(back_inserter(input_colors), 9, BLUE);

  for (int i = 0; i < 3; ++i) {
    fill_n(back_inserter(input_colors), 3, ORANGE);
    fill_n(back_inserter(input_colors), 3, WHITE);
    fill_n(back_inserter(input_colors), 3, RED);
    fill_n(back_inserter(input_colors), 3, YELLOW);
  }

  fill_n(back_inserter(input_colors), 9, GREEN);

  // Creating cubitos inside rubick_cube
  {
    this->rubick_cube.cubitos[3] = std::make_shared<Cubito>(
      Resources::GetTexture("red"),
      Resources::GetTexture("piksar1"),
      Resources::GetTexture("blue"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, distance_b_cubes, -distance_b_cubes), 3, 
      input_colors[20], input_colors[9], input_colors[0]);
    this->rubick_cube.cubitos[6] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("red"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, distance_b_cubes, -distance_b_cubes), 6, 
      input_colors[19], input_colors[1]);
    this->rubick_cube.cubitos[9] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("red"),
      Resources::GetTexture("yi3"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, distance_b_cubes, -distance_b_cubes), 9, 
      input_colors[18], input_colors[17], input_colors[2]);
    this->rubick_cube.cubitos[12] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("piksar4"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, 0.0f, -distance_b_cubes), 12, 
      input_colors[32], input_colors[21]);
    this->rubick_cube.cubitos[15] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, 0.0f, -distance_b_cubes), 15, 
      input_colors[31]);
    this->rubick_cube.cubitos[18] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("yi6"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, 0.0f, -distance_b_cubes), 18, 
      input_colors[30], input_colors[29]);
    this->rubick_cube.cubitos[21] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("piksar7"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, -distance_b_cubes, -distance_b_cubes), 21, 
      input_colors[44], input_colors[33], input_colors[51]);
    this->rubick_cube.cubitos[24] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, -distance_b_cubes, -distance_b_cubes), 24, 
      input_colors[43], input_colors[52]);
    this->rubick_cube.cubitos[27] = std::make_shared<Cubito>(
      Resources::GetTexture("blue"),
      Resources::GetTexture("yi9"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, -distance_b_cubes, -distance_b_cubes), 27, 
      input_colors[42], input_colors[41], input_colors[53]);

    this->rubick_cube.cubitos[2] = std::make_shared<Cubito>(
      Resources::GetTexture("red"),
      Resources::GetTexture("piksar2"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, distance_b_cubes, 0.0f), 2, 
      input_colors[10], input_colors[3]);
    this->rubick_cube.cubitos[5] = std::make_shared<Cubito>(
      Resources::GetTexture("red"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, distance_b_cubes, 0.0f), 5, 
      input_colors[4]);
    this->rubick_cube.cubitos[8] = std::make_shared<Cubito>(
      Resources::GetTexture("red"),
      Resources::GetTexture("yi2"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, distance_b_cubes, 0.0f), 8, 
      input_colors[16], input_colors[5]);
    this->rubick_cube.cubitos[11] = std::make_shared<Cubito>(
      Resources::GetTexture("piksar5"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, 0.0f, 0.0f), 11, 
      input_colors[22]);
    this->rubick_cube.cubitos[14] = std::make_shared<Cubito>(
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, 0.0f, 0.0f), 14);
    this->rubick_cube.cubitos[17] = std::make_shared<Cubito>(
      Resources::GetTexture("yi5"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, 0.0f, 0.0f), 17, 
      input_colors[28]);
    this->rubick_cube.cubitos[20] = std::make_shared<Cubito>(
      Resources::GetTexture("piksar8"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, -distance_b_cubes, 0.0f), 20, 
      input_colors[34], input_colors[48]);
    this->rubick_cube.cubitos[23] = std::make_shared<Cubito>(
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, -distance_b_cubes, 0.0f), 23, 
      input_colors[49]);
    this->rubick_cube.cubitos[26] = std::make_shared<Cubito>(
      Resources::GetTexture("yi8"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, -distance_b_cubes, 0.0f), 26, 
      input_colors[40], input_colors[50]);

    this->rubick_cube.cubitos[1] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp1"),
      Resources::GetTexture("piksar3"),
      Resources::GetTexture("red"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, distance_b_cubes, distance_b_cubes), 1, 
      input_colors[12], input_colors[11], input_colors[6]);
    this->rubick_cube.cubitos[4] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp2"),
      Resources::GetTexture("red"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, distance_b_cubes, distance_b_cubes), 4, 
      input_colors[13], input_colors[7]);
    this->rubick_cube.cubitos[7] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp3"),
      Resources::GetTexture("red"),
      Resources::GetTexture("yi1"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, distance_b_cubes, distance_b_cubes), 7, 
      input_colors[14], input_colors[15], input_colors[8]);
    this->rubick_cube.cubitos[10] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp4"),
      Resources::GetTexture("piksar6"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, 0.0f, distance_b_cubes), 10, 
      input_colors[24], input_colors[23]);
    this->rubick_cube.cubitos[13] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp5"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, 0.0f, distance_b_cubes), 13, 
      input_colors[25]);
    this->rubick_cube.cubitos[16] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp6"),
      Resources::GetTexture("yi4"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, 0.0f, distance_b_cubes), 16, 
      input_colors[26], input_colors[27]);
    this->rubick_cube.cubitos[19] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp7"),
      Resources::GetTexture("piksar9"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(-distance_b_cubes, -distance_b_cubes, distance_b_cubes), 19, 
      input_colors[36], input_colors[35], input_colors[45]);
    this->rubick_cube.cubitos[22] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp8"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(0.0f, -distance_b_cubes, distance_b_cubes), 22, 
      input_colors[37], input_colors[46]);
    this->rubick_cube.cubitos[25] = std::make_shared<Cubito>(
      Resources::GetTexture("ucsp9"),
      Resources::GetTexture("yi7"),
      Resources::GetTexture("orange"),
      Resources::GetTexture("negro"),
      Resources::GetShader("cubito"),
      glm::vec3(distance_b_cubes, -distance_b_cubes, distance_b_cubes), 25, 
      input_colors[38], input_colors[39], input_colors[47]);
  }
}

void GameController::ProcessInput(float delta_time) {
    if (( this->keys_press[GLFW_KEY_RIGHT_SHIFT] && !this->keys_already_press[GLFW_KEY_RIGHT_SHIFT]) ||
      (this->keys_press[GLFW_KEY_LEFT_SHIFT] && !this->keys_already_press[GLFW_KEY_LEFT_SHIFT])) {
      
        if (this->keys_press[GLFW_KEY_U] && !this->keys_already_press[GLFW_KEY_U])
        {
          U_PRIME_ANIM = true;
          U_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_U] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_D] && !this->keys_already_press[GLFW_KEY_D])
        {
          D_PRIME_ANIM = true;
          D_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_D] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_R] && !this->keys_already_press[GLFW_KEY_R])
        {
          R_ANIM = true;
          R_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_R] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
        
        if (this->keys_press[GLFW_KEY_L] && !this->keys_already_press[GLFW_KEY_L])
        {
          L_PRIME_ANIM = true;
          L_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_L] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }

        if (this->keys_press[GLFW_KEY_F] && !this->keys_already_press[GLFW_KEY_F])
        {
          F_PRIME_ANIM = true;
          F_PRIME_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_F] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
      
        if (this->keys_press[GLFW_KEY_B] && !this->keys_already_press[GLFW_KEY_B])
        {
          B_ANIM = true;
          B_ANIM_I = true;
          this->can_press = false;
          this->some_movement = true;
          this->keys_already_press[GLFW_KEY_B] = true;
          this->keys_already_press[GLFW_KEY_RIGHT_SHIFT] = true;
          this->keys_already_press[GLFW_KEY_LEFT_SHIFT] = true;
        }
    }
    else {
      if (this->keys_press[GLFW_KEY_U] && !this->keys_already_press[GLFW_KEY_U])
      {
        U_ANIM = true;
        U_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_U] = true;
      }

      if (this->keys_press[GLFW_KEY_D] && !this->keys_already_press[GLFW_KEY_D])
      {
        D_ANIM = true;
        D_ANIM_I = true;
        this->some_movement = true;
        this->can_press = false;
        this->keys_already_press[GLFW_KEY_D] = true;
      }

      if (this->keys_press[GLFW_KEY_R] && !this->keys_already_press[GLFW_KEY_R])
      {
        R_PRIME_ANIM = true;
        R_PRIME_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_R] = true;
      }
      
      if (this->keys_press[GLFW_KEY_L] && !this->keys_already_press[GLFW_KEY_L])
      {
        L_ANIM = true;
        L_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_L] = true;
      }
      
      if (this->keys_press[GLFW_KEY_F] && !this->keys_already_press[GLFW_KEY_F])
      {
        F_ANIM = true;
        F_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_F] = true;
      }
     
      if (this->keys_press[GLFW_KEY_B] && !this->keys_already_press[GLFW_KEY_B])
      {
        B_PRIME_ANIM = true;
        B_PRIME_ANIM_I = true;
        this->can_press = false;
        this->some_movement = true;
        this->keys_already_press[GLFW_KEY_B] = true;
      }
    }
}

void GameController::Render() {
  // Render rubick_cube
  rubick_cube.Draw(*Renderer, this->model, this->view, this->projection);

  // Here We render all things of game
}

void GameController::ResetAngles() {
  move_angles[0] = 135.0f;
  move_angles[1] = 90.0f;
  move_angles[2] = 45.0f;
  move_angles[3] = 180.0f;
  move_angles[4] = 0.0f;
  move_angles[5] = 0.0f;
  move_angles[6] = 225.0f;
  move_angles[7] = 270.0f;
  move_angles[8] = 315.0f;
}

void GameController::UpdateGame(float delta_time) {
  if (this->some_movement) this->PlayAnimation();
}

void GameController::PlayAnimation() {
  std::vector<std::reference_wrapper<std::shared_ptr<Cubito>>> cubitos;
  float* angles = move_angles;
  const float* angles_limit;
  float step;
  int clockwise;
  Move current_move;
  int normalMove;

  if (F_ANIM_I) {
    current_move = Move::F;
    clockwise = 1;
    normalMove = kAroundZLeft;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (F_PRIME_ANIM_I) {
    current_move = Move::FP;
    clockwise = -1;
    normalMove = kAroundZLeft;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 1; i <= 25; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_ANIM_I) {
    current_move = Move::B;
    clockwise = 1;
    normalMove = kAroundZLeft;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (B_PRIME_ANIM_I) {
    current_move = Move::BP;
    clockwise = -1;
    normalMove = kAroundZLeft;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 3; i <= 27; i += 3)
      cubitos.push_back(rubick_cube.cubitos[i]);
  }
  else if (L_ANIM_I) {
    current_move = Move::L;
    clockwise = 1;
    normalMove = kAroundXRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (L_PRIME_ANIM_I) {
    current_move = Move::LP;
    clockwise = -1;
    normalMove = kAroundXRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 3; i <= 21; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (R_ANIM_I) {
    current_move = Move::R;
    clockwise = 1;
    normalMove = kAroundXRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 9; i <= 27; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (R_PRIME_ANIM_I) {
    current_move = Move::RP;
    clockwise = -1;
    normalMove = kAroundXRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 9; i <= 27; i += 9) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i - 1]);
      cubitos.push_back(rubick_cube.cubitos[i - 2]);
    }
  }
  else if (U_ANIM) {
    current_move = Move::U;
    clockwise = -1;
    normalMove = kAroundYRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 1; i <= 9; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (U_PRIME_ANIM) {
    current_move = Move::UP;
    clockwise = 1;
    normalMove = kAroundYRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 1; i <= 9; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (D_PRIME_ANIM) {
    current_move = Move::DP;
    clockwise = -1;
    normalMove = kAroundYRight;
    angles_limit = angles_upper_limit;
    step = 1.0f;

    for (int i = 19; i <= 21; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }
  else if (D_ANIM) {
    current_move = Move::D;
    clockwise = 1;
    normalMove = kAroundYRight;
    angles_limit = angles_lower_limit;
    step = -1.0f;

    for (int i = 19; i <= 21; ++i) {
      cubitos.push_back(rubick_cube.cubitos[i]);
      cubitos.push_back(rubick_cube.cubitos[i + 3]);
      cubitos.push_back(rubick_cube.cubitos[i + 6]);
    }
  }

  for (int i = 1; i <= 7; i += 2) {
    if (std::abs(angles_limit[i] - angles[i]) > 0.4f) angles[i] += step;
    else {
      angles[i] = angles_limit[i];
      cubitos[i].get()->RotateAround(normalMove * clockwise);
    }
    cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i],
      current_move, kRadioNormal));

    cubitos[i].get()->RotateAround(normalMove * -1 * clockwise);
  }

  for (int i = 0; i < 8; i += 2) {
    if (i != 4) {
      if (std::abs(angles_limit[i] - angles[i]) > 0.4f) angles[i] += step;
      else {
        angles[i] = angles_limit[i];
        cubitos[i].get()->RotateAround(normalMove * clockwise);
      }

      cubitos[i].get()->SetPosition(CalculateTranslatePosition(angles[i],
        current_move, kRadioLarge));
    }

    cubitos[i].get()->RotateAround(normalMove * -1 * clockwise);
  }

  if (std::abs(angles_limit[8] - angles[8]) > 0.4f) angles[8] += step;
  else {
    angles[8] = angles_limit[8];
    cubitos[8].get()->RotateAround(normalMove * clockwise);
    cubitos[4].get()->RotateAround(normalMove * clockwise);
    F_ANIM_I = false;
    B_ANIM_I = false;
    F_PRIME_ANIM_I = false;
    B_PRIME_ANIM_I = false;
    L_ANIM_I = false;
    L_PRIME_ANIM_I = false;
    R_PRIME_ANIM_I = false;
    R_ANIM_I = false;
    U_ANIM_I = false;
    U_PRIME_ANIM_I = false;
    D_ANIM_I = false;
    D_PRIME_ANIM_I = false;
    this->some_movement = false;
    this->can_press = true;
  }

  cubitos[8].get()->SetPosition(CalculateTranslatePosition(angles[8],
    current_move, kRadioLarge));

  cubitos[8].get()->RotateAround(normalMove * -1 * clockwise);

  // REASIGN POINTER
  if (!this->some_movement) {
    if (clockwise > 0) {
      auto temp = cubitos[0].get();
      cubitos[0].get() = cubitos[6].get();
      cubitos[6].get() = cubitos[8].get();
      cubitos[8].get() = cubitos[2].get();
      cubitos[2].get() = temp;

      temp = cubitos[1].get();
      cubitos[1].get() = cubitos[3].get();
      cubitos[3].get() = cubitos[7].get();
      cubitos[7].get() = cubitos[5].get();
      cubitos[5].get() = temp;
    }
    else {
      auto temp = cubitos[0].get();
      cubitos[0].get() = cubitos[2].get();
      cubitos[2].get() = cubitos[8].get();
      cubitos[8].get() = cubitos[6].get();
      cubitos[6].get() = temp;

      temp = cubitos[1].get();
      cubitos[1].get() = cubitos[5].get();
      cubitos[5].get() = cubitos[7].get();
      cubitos[7].get() = cubitos[3].get();
      cubitos[3].get() = temp;
    }

    this->ResetAngles();

    B_ANIM = false;
    B_PRIME_ANIM = false;
    F_ANIM = false;
    F_PRIME_ANIM = false;
    L_PRIME_ANIM = false;
    L_ANIM = false;
    R_ANIM = false;
    R_PRIME_ANIM = false;
    U_ANIM = false;
    U_PRIME_ANIM = false;
    D_ANIM = false;
    D_PRIME_ANIM = false;
  }
}

void GameController::UpdateMatrices(glm::mat4 new_model, 
  glm::mat4 new_view, 
  glm::mat4 new_proyection) {
  this->model = new_model;
  this->view = new_view;
  this->projection = new_proyection;
}

glm::vec3 GameController::CalculateTranslatePosition(float angle, Move m, const float& radius) {
  switch (m) {
  case Move::F:
  case Move::FP:
    return glm::vec3(radius * cos(deg(angle)),
      radius * sin(deg(angle)),
      distance_b_cubes);
    break;

  case Move::B:
  case Move::BP:
    return glm::vec3(radius * cos(deg(angle)),
      radius * sin(deg(angle)),
      -distance_b_cubes);
    break;

  case Move::R:
  case Move::RP:
    return glm::vec3(distance_b_cubes,
      radius * sin(deg(angle)),
      radius * cos(deg(angle)));
    break;

  case Move::L:
  case Move::LP:
    return glm::vec3(-distance_b_cubes,
      radius * sin(deg(angle)),
      radius * cos(deg(angle)));
    break;

  case Move::U:
  case Move::UP:
    return glm::vec3(radius * cos(deg(angle)),
      distance_b_cubes,
      radius * sin(deg(angle)));
    break;

  case Move::D:
  case Move::DP:
    return glm::vec3(radius * cos(deg(angle)),
      -distance_b_cubes,
      radius * sin(deg(angle)));
  }
}

#endif // CUBITO_GAME_CONTROLLER_HPP