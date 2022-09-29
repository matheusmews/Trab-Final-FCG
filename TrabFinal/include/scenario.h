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

// Função que desenha o chão da quadra
glm::mat4 TransformCourt();

// Função que desenha as tabelas na quadra
std::vector<glm::mat4> TransformBackboard();

// Função que desenha o plano de fundo do cenário
void DrawBackground();

// Função que desenha os vidros das tabelas na quadra
std::vector<glm::mat4> TransformGlass();

#endif // _SCENARIO_H
