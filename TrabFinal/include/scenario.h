#ifndef _SCENARIO_H
#define _SCENARIO_H

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

// Vari�veis externas
extern GLfloat time_game;
extern GLint points_p1;
extern GLint points_p2;

extern int CourtIsInTheBeach;

// Fun��o que desenha o ch�o da quadra
glm::mat4 TransformCourt();

// Fun��o que desenha as tabelas na quadra
std::vector<glm::mat4> TransformHoop();

// Fun��o que desenha o plano de fundo do cen�rio
glm::mat4 TransformSkybox();

// Fun��o que desenha a power bar que mede a for�a do arremesso
glm::mat4 TransformPowerbar();

// Fun��o que transforma a matriz de modelo do scoreboard
std::vector<glm::mat4> TransformScoreboard();
// Fun��o que transforma a matriz de modelo do tempo contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardTime();
// Fun��o que transforma a matriz de modelo dos pontos contabilizados no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPoints();
// Fun��o que transforma a matriz de modelo do per�odo contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPeriod();

// COLLIDERS TRANSFORM ======================================================

// Fun��o que transforma o collider de parede
std::vector<glm::mat4> TransformWallCollider();

// Fun��o que transforma o collider do poste
std::vector<glm::mat4> TransformPoleCollider();

// Fun��o que transforma o collider da tabela
std::vector<glm::mat4> TransformBackboardCollider();

// Fun��o que transforma o collider do aro
std::vector<glm::mat4> TransformRimCollider();

// Fun��o que transforma o collider do aro quando o player erra
std::vector<glm::mat4> TransformMissRimCollider();

#endif // _SCENARIO_H
