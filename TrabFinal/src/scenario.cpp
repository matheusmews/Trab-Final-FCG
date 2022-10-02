#include "scenario.h"

#define SPHERE     0
#define BUNNY      1
#define PLANE      2
#define COURT      3
#define BACKBOARD  4
#define BACKGROUND 5
#define GLASS      6
#define CUBE       7
#define HAND       8

// Função que desenha o chão da quadra
glm::mat4 TransformCourt()
{
    glm::mat4 model = Matrix_Identity();
    return model;
}

// Função que desenha as tabelas na quadra
// Função que desenha as tabelas na quadra
std::vector<glm::mat4> TransformHoop()
{
    std::vector<glm::mat4> player_models;

    glm::mat4 model = Matrix_Identity();

    // Desenhamos o modelo da tabela de basquete de um lado da quadra
    model = Matrix_Translate(0.0f,0.0f,-13.5f);
    player_models.push_back(model);

    // Desenhamos o modelo da tabela de basquete do outro lado da quadra
    model = Matrix_Translate(0.0f,0.0f,13.5f) * Matrix_Rotate_Y(3.141592f);
    player_models.push_back(model);

    return player_models;
}

// Função que desenha o plano de fundo do cenário
glm::mat4 TransformSkybox()
{
    glm::mat4 model = Matrix_Identity();

    model = Matrix_Scale(11.5f, 10.0f, 18.0f)
          * Matrix_Translate(0.0f, 0.1f, 0.0f)
          * Matrix_Rotate_Y(3.1415f/2);
    return model;
}
