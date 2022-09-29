#ifndef TEXTRENDERING_H
#define TEXTRENDERING_H

#include <string>

#include <stddef.h>
#include <stdint.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>

// Headers locais, definidos na pasta "include/"
#include "utils.h"
#include "dejavufont.h"
#include "matrices.h"

// Vari�veis externas
extern bool g_ShowInfoText;

void TextRendering_LoadShader(const GLchar* const shader_string, GLuint shader_id);

void TextRendering_Init();

void TextRendering_PrintString(GLFWwindow* window, const std::string &str, float x, float y, float scale = 1.0f);

float TextRendering_LineHeight(GLFWwindow* window);

float TextRendering_CharWidth(GLFWwindow* window);

void TextRendering_PrintMatrix(GLFWwindow* window, glm::mat4 M, float x, float y, float scale = 1.0f);

void TextRendering_PrintVector(GLFWwindow* window, glm::vec4 v, float x, float y, float scale = 1.0f);

void TextRendering_PrintMatrixVectorProduct(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

void TextRendering_PrintMatrixVectorProductMoreDigits(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

void TextRendering_PrintMatrixVectorProductDivW(GLFWwindow* window, glm::mat4 M, glm::vec4 v, float x, float y, float scale = 1.0f);

void TextRendering_ShowModelViewProjection(GLFWwindow* window, glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec4 p_model);
void TextRendering_ShowProjection(GLFWwindow* window);
void TextRendering_ShowFramesPerSecond(GLFWwindow* window);

#endif // _TEXTRENDERING_H
