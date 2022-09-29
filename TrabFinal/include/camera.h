#ifndef _CAMERA_H
#define _CAMERA_H

#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers abaixo s�o espec�ficos de C++
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
#include <glad/glad.h>   // Cria��o de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Cria��o de janelas do sistema operacional

// Headers da biblioteca GLM: cria��o de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers locais, definidos na pasta "include/"
#include "utils.h"
#include "matrices.h"
#include "player.h"

// Vari�veis externas
extern float g_CameraTheta;
extern float g_CameraPhi;
extern float g_CameraDistance;

extern glm::vec4 camera_position_c;
extern glm::vec4 camera_view_vector;
extern glm::vec4 camera_up_vector;

extern glm::vec4 movement_vector;

extern int camera_movement_keys[];

extern GLfloat camera_time_prev;

// Fun��o que movimenta a c�mera baseado nas teclas W, S, A, D e na movimenta��o do mouse
void MoveFreeCamera();

#endif // _CAMERA_H
