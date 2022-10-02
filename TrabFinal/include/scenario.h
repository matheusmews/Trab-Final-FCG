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

// Fun��o que desenha o ch�o da quadra
glm::mat4 TransformCourt();

// Fun��o que desenha as tabelas na quadra
std::vector<glm::mat4> TransformHoop();

// Fun��o que desenha o plano de fundo do cen�rio
glm::mat4 TransformSkybox();

#endif // _SCENARIO_H
