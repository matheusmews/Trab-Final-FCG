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
#include "collisions.h"
#include "scenario.h"

// Variáveis externas
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

// Função que desenha a bola de basquete quando ela é arremessada
glm::mat4 TransformBall();

// Função que desenha a bola de basquete quando ela é arremessada e vai acertar
glm::mat4 TransformBallMadeShot();

// Função que desenha a bola de basquete quando ela é arremessada e vai errar
glm::mat4 TransformBallNonMadeShot();

// Função que desenha a bola de basquete após ela colidir com algo
glm::mat4 TransformBallAfterCollide();

// Função que pré calcula a trajetória da bola e verifica se ela
// vai colidir com o aro, retornando 0 se não vai colidir ou 1 ou
// 2, respectivamente se vai colidir com o aro 1 e 2
short BallWillCollideWithRim();

GLfloat porcentagem();

#endif // _BALL_H
