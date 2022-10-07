#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include <cmath>
#include <cstdio>
#include <cstdlib>

// Headers abaixo s�o espec�ficos de C++
/*#include <map>
#include <stack>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>*/

// Headers das bibliotecas OpenGL
#include <glad/glad.h>   // Cria��o de contexto OpenGL 3.3
#include <GLFW/glfw3.h>  // Cria��o de janelas do sistema operacional

// Headers da biblioteca GLM: cria��o de matrizes e vetores.
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

// Headers locais, definidos na pasta "include/"
#include "matrices.h"
#include "scenario.h"

// Vari�veis externas

// Vari�veis para a colis�o das paredes
extern glm::vec4 walls_normal;
extern glm::vec4 bbox_max_wall1_collider;
extern glm::vec4 bbox_min_wall1_collider;
extern glm::vec4 wall1_normal;
extern glm::vec4 bbox_max_wall2_collider;
extern glm::vec4 bbox_min_wall2_collider;
extern glm::vec4 wall2_normal;
extern glm::vec4 bbox_max_wall3_collider;
extern glm::vec4 bbox_min_wall3_collider;
extern glm::vec4 wall3_normal;
extern glm::vec4 bbox_max_wall4_collider;
extern glm::vec4 bbox_min_wall4_collider;
extern glm::vec4 wall4_normal;

// Vari�veis para colis�o dos postes das hoops da quadra
extern glm::vec4 bbox_max_pole1_collider;
extern glm::vec4 bbox_min_pole1_collider;
extern glm::vec4 bbox_max_pole2_collider;
extern glm::vec4 bbox_min_pole2_collider;

// Vari�veis para colis�o das tabelas
extern glm::vec4 bbox_max_backboard1_collider;
extern glm::vec4 bbox_min_backboard1_collider;
extern glm::vec4 bbox_max_backboard2_collider;
extern glm::vec4 bbox_min_backboard2_collider;

// Vari�veis para a colis�o dos aros
extern glm::vec4 rim_1_collider_center;
extern glm::vec4 rim_2_collider_center;
extern GLfloat rim_colliders_radius;

// Vari�veis para colis�o dos aros do caso de quando o player erra o arremesso
extern glm::vec4 bbox_max_missrim1_collider;
extern glm::vec4 bbox_min_missrim1_collider;
extern glm::vec4 bbox_max_missrim2_collider;
extern glm::vec4 bbox_min_missrim2_collider;

// Vetor super hardcodado que a bola deve seguir caso colida com a tabela ou o aro
extern glm::vec4 collision_ball_handling_vector;

// Vari�veis para saber se objetos est�o colidindo (para mudar a cor do debug)
extern bool g_Wall1Colliding, g_Wall2Colliding, g_Wall3Colliding, g_Wall4Colliding;
extern bool g_Pole1Colliding, g_Pole2Colliding;
extern bool g_Backboard1Colliding, g_Backboard2Colliding;
extern bool g_RimColliding;
extern bool g_MissRim1Colliding, g_MissRim2Colliding;

// Fun��o que detecta colis�o entre duas esferas
bool CheckCollisionSphereSphere(glm::vec4 center_sphere1, GLfloat radius_sphere1,
                                glm::vec4 center_sphere2, GLfloat radius_sphere2);

// Fun��o que detecta colis�o entre esfera e ponto
bool CheckCollisionSpherePoint(glm::vec4 center_sphere1, GLfloat radius_sphere1, glm::vec4 point);

// Fun��o que detecta colis�o entre dois cubos
bool CheckCollisionCubeCube(glm::vec4 bbox_max_cube1, glm::vec4 bbox_min_cube1,
                            glm::vec4 bbox_max_cube2, glm::vec4 bbox_min_cube2);

// Fun��o que detecta colis�o entre um cubo e um plano
bool CheckCollisionCubePlane(glm::vec4 bbox_max_cube, glm::vec4 bbox_min_cube,
                             glm::vec4 bbox_max_plane, glm::vec4 bbox_min_plane, glm::vec4 normal);

// Fun��o que detecta colis�o entre uma esfera e um cubo
bool CheckCollisionSphereCube(glm::vec4 center_sphere, GLfloat radius_sphere,
                              glm::vec4 bbox_max_cube, glm::vec4 bbox_min_cube);

// Fun��o para setar os valores do vetor de colis�o
void SetCollisionVector(glm::vec4 c, glm::vec4 prev_c);

// BBOX SETTERS TRANSFORM ======================================================

// Fun��o que seta as bbox das paredes
void SetWallsBboxes(glm::vec3 bbox_plane_max, glm::vec3 bbox_plane_min);
// Fun��o que seta as bbox dos postes das hoops da quadra
void SetPoleBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min);
// Fun��o que seta as bbox das tabelas
void SetBackboardBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min);
// Fun��o que seta as bbox do aro do caso de quando o player erra o arremesso
void SetMissRimBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min);

#endif // _COLLISIONS_H

