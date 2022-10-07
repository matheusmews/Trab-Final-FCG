#ifndef _SCENARIO_H
#define _SCENARIO_H

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

// Variáveis externas
extern GLfloat time_game;
extern GLint points_p1;
extern GLint points_p2;

extern int CourtIsInTheBeach;

// Função que desenha o chão da quadra
glm::mat4 TransformCourt();

// Função que desenha as tabelas na quadra
std::vector<glm::mat4> TransformHoop();

// Função que desenha o plano de fundo do cenário
glm::mat4 TransformSkybox();

// Função que desenha a power bar que mede a força do arremesso
glm::mat4 TransformPowerbar();

// Função que transforma a matriz de modelo do scoreboard
std::vector<glm::mat4> TransformScoreboard();
// Função que transforma a matriz de modelo do tempo contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardTime();
// Função que transforma a matriz de modelo dos pontos contabilizados no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPoints();
// Função que transforma a matriz de modelo do período contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPeriod();

// COLLIDERS TRANSFORM ======================================================

// Função que transforma o collider de parede
std::vector<glm::mat4> TransformWallCollider();

// Função que transforma o collider do poste
std::vector<glm::mat4> TransformPoleCollider();

// Função que transforma o collider da tabela
std::vector<glm::mat4> TransformBackboardCollider();

// Função que transforma o collider do aro
std::vector<glm::mat4> TransformRimCollider();

// Função que transforma o collider do aro quando o player erra
std::vector<glm::mat4> TransformMissRimCollider();

#endif // _SCENARIO_H
