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
std::vector<glm::mat4> TransformBackboard()
{
    std::vector<glm::mat4> player_models;

    glm::mat4 model = Matrix_Identity();

    // Desenhamos o modelo da tabela de basquete de um lado da quadra: PARTE BRANCA =======================================
    model = Matrix_Translate(-1.0f, 2.8f, 12.85f) * Matrix_Scale(1.0f, 4.5f, 1.0f);    // Direita
    player_models.push_back(model);

    model = Matrix_Translate(0.9f, 2.8f, 12.85f) * Matrix_Scale(1.0f, 4.5f, 1.0f);     // Esquerda
    player_models.push_back(model);

    model = Matrix_Translate(-0.9f, 3.95f, 12.85f) * Matrix_Scale(18.0f, 1.0f, 1.0f);   // Cima
    player_models.push_back(model);

    model = Matrix_Translate(-0.9f, 2.8f, 12.85f) * Matrix_Scale(18.0f, 1.0f, 1.0f);    // Baixo
    player_models.push_back(model);

    // Desenhamos o modelo da tabela de basquete do outro lado
    model = Matrix_Translate(-0.9f, 2.9f, -12.85f) * Matrix_Scale(1.0f, 10.5f, 1.0f);    // Esquerda
    player_models.push_back(model);

    model = Matrix_Translate(0.8f, 2.9f, -12.85f) * Matrix_Scale(1.0f, 10.5f, 1.0f);     // Direita
    player_models.push_back(model);

    model = Matrix_Translate(-0.8f, 3.85f, -12.85f) * Matrix_Scale(16.0f, 1.0f, 1.0f);   // Cima
    player_models.push_back(model);

    model = Matrix_Translate(-0.8f, 2.9f, -12.85f) * Matrix_Scale(16.0f, 1.0f, 1.0f);    // Baixo
    player_models.push_back(model);

    // Desenhamos o modelo da tabela de basquete de um lado da quadra: PARTE PRETA =======================================
    model = Matrix_Translate(-1.0f, 2.8f, 12.85f) * Matrix_Scale(1.0f, 4.5f, 1.0f);    // Direita
    player_models.push_back(model);

    model = Matrix_Translate(0.9f, 2.8f, 12.85f) * Matrix_Scale(1.0f, 4.5f, 1.0f);     // Esquerda
    player_models.push_back(model);

    model = Matrix_Translate(-0.9f, 3.95f, 12.85f) * Matrix_Scale(18.0f, 1.0f, 1.0f);   // Cima
    player_models.push_back(model);

    model = Matrix_Translate(-0.9f, 2.8f, 12.85f) * Matrix_Scale(18.0f, 1.0f, 1.0f);    // Baixo
    player_models.push_back(model);

    // Desenhamos o modelo da tabela de basquete do outro lado
    model = Matrix_Translate(-0.9f, 2.9f, -12.85f) * Matrix_Scale(1.0f, 10.5f, 1.0f);    // Esquerda
    player_models.push_back(model);

    model = Matrix_Translate(0.8f, 2.9f, -12.85f) * Matrix_Scale(1.0f, 10.5f, 1.0f);     // Direita
    player_models.push_back(model);

    model = Matrix_Translate(-0.8f, 3.85f, -12.85f) * Matrix_Scale(16.0f, 1.0f, 1.0f);   // Cima
    player_models.push_back(model);

    model = Matrix_Translate(-0.8f, 2.9f, -12.85f) * Matrix_Scale(16.0f, 1.0f, 1.0f);    // Baixo
    player_models.push_back(model);

    return player_models;
}

// Função que desenha o plano de fundo do cenário
void DrawBackground()
{
    /*
    glm::mat4 model = Matrix_Identity();
    glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(object_id_uniform, BACKGROUND);
    DrawVirtualObject("background");

    model = Matrix_Rotate_Y(3.141592);
    glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(object_id_uniform, BACKGROUND);
    DrawVirtualObject("background");

    model = Matrix_Translate(0.0f, 0.0f, 6.5f) * Matrix_Rotate_Y(3.141592/2.0f);
    glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(object_id_uniform, BACKGROUND);
    DrawVirtualObject("background");

    model = Matrix_Translate(0.0f, 0.0f, -6.5f) * Matrix_Rotate_Y((3.141592*3.0f)/2.0f);
    glUniformMatrix4fv(model_uniform, 1 , GL_FALSE , glm::value_ptr(model));
    glUniform1i(object_id_uniform, BACKGROUND);
    DrawVirtualObject("background");
    */
}

// Função que desenha os vidros das tabelas na quadra
std::vector<glm::mat4> TransformGlass()
{
    std::vector<glm::mat4> player_models;

    // Desenhamos o modelo do vidro de uma tabela de basquete
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 model = Matrix_Identity();
    player_models.push_back(model);

    model = Matrix_Translate(0.0f, 0.0f, 12.875f) * Matrix_Rotate_Y(3.141592) * Matrix_Translate(0.0f, 0.0f, -12.875f);
    player_models.push_back(model);

    // Desenhamos o modelo do vidro da outra tabela de basquete
    model = Matrix_Translate(0.0f, 0.0f, -25.7f);
    player_models.push_back(model);

    model = Matrix_Translate(0.0f, 0.0f, -12.825f) * Matrix_Rotate_Y(3.141592) * Matrix_Translate(0.0f, 0.0f, -12.875f);
    player_models.push_back(model);

    return player_models;
}
