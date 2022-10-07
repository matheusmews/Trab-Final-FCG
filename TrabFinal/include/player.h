#ifndef _PLAYER_H
#define _PLAYER_H

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
#include "ball.h"

// Variáveis externas
extern GLfloat player_time_prev;
extern GLfloat player_jump_time_prev;

extern float g_TorsoPositionX;
extern float g_TorsoPositionY;
extern float g_TorsoPositionZ;

extern float g_RightArmAngleX;
extern float g_RightArmAngleY;
extern float g_RightArmAngleZ;
extern float g_LeftArmAngleX;
extern float g_LeftArmAngleY;
extern float g_LeftArmAngleZ;
extern float g_RightForearmAngleX;
extern float g_RightForearmAngleY;
extern float g_RightForearmAngleZ;
extern float g_LeftForearmAngleX;
extern float g_LeftForearmAngleY;
extern float g_LeftForearmAngleZ;
extern float g_RightHandAngleX;
extern float g_RightHandAngleY;
extern float g_RightHandAngleZ;
extern float g_RightLegAngleX;
extern float g_RightLegAngleY;
extern float g_RightLegAngleZ;
extern float g_LeftLegAngleX;
extern float g_LeftLegAngleY;
extern float g_LeftLegAngleZ;
extern float g_RightThighAngleX;
extern float g_RightThighAngleY;
extern float g_RightThighAngleZ;
extern float g_LeftThighAngleX;
extern float g_LeftThighAngleY;
extern float g_LeftThighAngleZ;

extern bool g_PlayerIsMoving;
extern bool g_PlayerStartedShot;
extern bool g_PlayerIsShooting;
extern bool g_PlayerIsJumping;

extern bool g_MeasuringStrength;
extern GLfloat measure_time_prev;
extern GLfloat measure_time_now;
extern GLfloat measure_delta_time;

void MeasureShotStrength();

// Matriz que guarda as transformações que chegam na mão direita do player,
// para fazer a animação de arremesso
extern glm::mat4 right_hand_model;

// Função que pega a matriz M e guarda a mesma no topo da pilha
void PushMatrix(glm::mat4 M);
// Função que remove a matriz atualmente no topo da pilha e armazena a mesma na variável M
void PopMatrix(glm::mat4& M);

// Função que desenha o jogador através da modelagem de várias instâncias de um cubo
std::vector<glm::mat4> TransformPlayer();

// Função que transforma o collider do player
glm::mat4 TransformPlayerCollider();

// Função que anima a movimentação do jogador
void AnimatePlayerMovement();

// Função que anima o pulo do jogador
void AnimatePlayerJump();

// Função que anima o arremesso do jogador
void AnimatePlayerShot();

// Função que controla todas as animaçõe do player
void AnimatePlayer();

#endif // _PLAYER_H

