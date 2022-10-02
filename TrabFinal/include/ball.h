#ifndef _BALL_H
#define _BALL_H

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
#include "camera.h"
#include "player.h"

// Variáveis externas
extern glm::vec4 ball_position_c;

extern GLfloat ball_t;
extern GLfloat ball_time_prev;

extern glm::vec4 p1;
extern glm::vec4 p2;
extern glm::vec4 p3;
extern glm::vec4 p4;

extern bool g_BallWasShot;
extern bool g_MeasuringStrength;

extern GLfloat measure_time_prev;
extern GLfloat measure_time_now;
extern GLfloat measure_delta_time;

void MeasureShotStrength();

// Função que desenha a bola de basquete quando ela é arremessada
glm::mat4 TransformBall();

#endif // _BALL_H
