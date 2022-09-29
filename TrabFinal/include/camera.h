#ifndef _CAMERA_H
#define _CAMERA_H

#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers abaixo são específicos de C++
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

// Headers das bibliotecas OpenGL
#include <glad/glad.h>   // Criação de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Criação de janelas do sistema operacional

// Headers da biblioteca GLM: criação de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers locais, definidos na pasta "include/"
#include "utils.h"
#include "matrices.h"
#include "player.h"

// Variáveis externas
extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

extern glm::vec4 camera_position_c;
extern glm::vec4 camera_view_vector;
extern glm::vec4 camera_up_vector;

extern glm::vec4 movement_vector;

extern int camera_movement_keys[];

extern GLfloat camera_time_prev;

// Função que movimenta a câmera baseado nas teclas W, S, A, D e na movimentação do mouse
void MoveFreeCamera();

#endif // _CAMERA_H
