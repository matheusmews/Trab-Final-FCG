#ifndef _BALL_H
#define _BALL_H

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
#include "camera.h"
#include "player.h"
#include "collisions.h"
#include "scenario.h"

// Vari�veis externas
extern glm::vec4 ball_position_c;
extern float ball_radius;
extern short whichRimWillBallCollide;

extern GLfloat ball_t;
extern GLfloat ball_time_prev;

extern GLfloat BALL_SPEED;
extern GLfloat MAX_T;

extern glm::vec4 p1;
extern glm::vec4 p2;
extern glm::vec4 p3;
extern glm::vec4 p4;

extern bool g_BallWasShot;
extern bool g_BallOnRim;
extern bool g_BucketShot;

extern bool GouradShading;

// Fun��o que desenha a bola de basquete quando ela � arremessada
glm::mat4 TransformBall();

// Fun��o que desenha a bola de basquete quando ela � arremessada e vai acertar
glm::mat4 TransformBallMadeShot();

// Fun��o que desenha a bola de basquete quando ela � arremessada e vai errar
glm::mat4 TransformBallNonMadeShot();

// Fun��o que desenha a bola de basquete ap�s ela colidir com algo
glm::mat4 TransformBallAfterCollide();

// Fun��o que pr� calcula a trajet�ria da bola e verifica se ela
// vai colidir com o aro, retornando 0 se n�o vai colidir ou 1 ou
// 2, respectivamente se vai colidir com o aro 1 e 2
short BallWillCollideWithRim();

GLfloat porcentagem();

#endif // _BALL_H
