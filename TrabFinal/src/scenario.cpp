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

GLfloat time_game = 0.0f;
GLint points_p1 = 0;
GLint points_p2 = 0;
GLint period = 0;

int CourtIsInTheBeach;

// Função que transforma a matriz de modelo do chão da quadra
glm::mat4 TransformCourt()
{
    glm::mat4 model = Matrix_Identity();
    return model;
}

// Função que transforma a matriz de modelo das tabelas na quadra
std::vector<glm::mat4> TransformHoop()
{
    std::vector<glm::mat4> hoop_models;

    glm::mat4 model = Matrix_Identity();

    // Desenhamos o modelo da tabela de basquete de um lado da quadra
    model = Matrix_Translate(0.0f,0.0f,-13.5f);
    hoop_models.push_back(model);

    // Desenhamos o modelo da tabela de basquete do outro lado da quadra
    model = Matrix_Translate(0.0f,0.0f,13.5f) * Matrix_Rotate_Y(3.141592f);
    hoop_models.push_back(model);

    return hoop_models;
}

// Função que transforma a matriz de modelo do plano de fundo do cenário
glm::mat4 TransformSkybox()
{
    glm::mat4 model = Matrix_Identity();

    model = Matrix_Scale(11.5f, 10.0f, 18.0f)
          * Matrix_Translate(0.0f, 0.18f, 0.0f)
          * Matrix_Rotate_Y(3.1415f*3/2);
    return model;
}

// Função que transforma a matriz de modelo da power bar que mede a força do arremesso
glm::mat4 TransformPowerbar()
{
    glm::mat4 model = Matrix_Identity();

    // Desenhamos o modelo da power bar que mede a força do arremesso
    model = Matrix_Translate(-10.0f,0.0f,-2.5f) * Matrix_Scale(3.0f,3.0f,3.0f);//camera_view_vector.z

    return model;
}

// Função que transforma a matriz de modelo do scoreboard
std::vector<glm::mat4> TransformScoreboard()
{
    std::vector<glm::mat4> score_model;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(0.0f,8.0f,-18.0f) * Matrix_Scale(2.5f,2.5f,2.5f);
    score_model.push_back(model);

    // Outro lado ==================================================================

    model = Matrix_Translate(0.0f,8.0f,18.0f) * Matrix_Scale(2.5f,2.5f,2.5f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back(model);

    return score_model;
}

// Função que transforma a matriz de modelo do tempo contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardTime()
{
    GLint delta_time_game = glfwGetTime()-time_game;

    GLint clock_seconds_u = (((GLint)delta_time_game)%60)%10;
    GLint clock_seconds_d = (((GLint)delta_time_game)%60)/10;
    GLint clock_minutes_u = (((GLint)delta_time_game)/60)%10;
    GLint clock_minutes_d = (((GLint)delta_time_game)/60)/10;

    if (clock_minutes_d == 1 and clock_minutes_u == 2)
    {
        time_game += 720.0f;
        period = (period+1)%4;
    }

    std::vector<std::pair<glm::mat4,std::string>> score_model;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(0.8f,8.8f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(clock_seconds_u)});
    model = Matrix_Translate(0.1f,8.8f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(clock_seconds_d)});
    model = Matrix_Translate(-0.8f,8.8f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(clock_minutes_u)});
    model = Matrix_Translate(-1.5f,8.8f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(clock_minutes_d)});

    model = Matrix_Translate(-0.1f,8.8f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,"two_points"});

    // Outro lado ==================================================================

    model = Matrix_Translate(-0.8f,8.8f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(clock_seconds_u)});
    model = Matrix_Translate(-0.1f,8.8f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(clock_seconds_d)});
    model = Matrix_Translate(0.8f,8.8f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(clock_minutes_u)});
    model = Matrix_Translate(1.5f,8.8f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(clock_minutes_d)});

    model = Matrix_Translate(-0.1f,8.8f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,"two_points"});

    return score_model;
}

// Função que transforma a matriz de modelo dos pontos contabilizados no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPoints()
{
    //points_p1 = 74;
    GLint points_p1_u = points_p1%10;
    GLint points_p1_d = points_p1/10;

    //points_p2 = 69;
    GLint points_p2_u = points_p2%10;
    GLint points_p2_d = points_p2/10;

    std::vector<std::pair<glm::mat4,std::string>> score_model;

    glm::mat4 model = Matrix_Identity();

    // Pontos
    model = Matrix_Translate(-2.17f,6.6f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(points_p1_u)});
    model = Matrix_Translate(-2.87f,6.6f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(points_p1_d)});

    model = Matrix_Translate(2.17f,6.6f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(points_p2_u)});
    model = Matrix_Translate(1.47f,6.6f,-17.8f) * Matrix_Scale(1.0f,1.2f,1.0f);
    score_model.push_back({model,std::to_string(points_p2_d)});

    // Outro lado ==================================================================

    // Pontos
    model = Matrix_Translate(2.17f,6.6f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(points_p1_u)});
    model = Matrix_Translate(2.87f,6.6f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(points_p1_d)});

    model = Matrix_Translate(-2.17f,6.6f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(points_p2_u)});
    model = Matrix_Translate(-1.47f,6.6f,17.8f) * Matrix_Scale(1.0f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model,std::to_string(points_p2_d)});

    return score_model;
}

// Função que transforma a matriz de modelo do período contabilizado no scoreboard
std::vector<std::pair<glm::mat4,std::string>> TransformScoreboardPeriod()
{
    std::vector<std::pair<glm::mat4,std::string>> score_model;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(-0.1f,6.9f,-17.8f) * Matrix_Scale(0.5f,1.2f,1.0f);
    score_model.push_back({model, std::to_string(period+1)});

    // Outro lado ==================================================================

    model = Matrix_Translate(0.1f,6.9f,17.8f) * Matrix_Scale(0.5f,1.2f,1.0f) * Matrix_Rotate_Y(3.141592);
    score_model.push_back({model, std::to_string(period+1)});

    return score_model;
}

// COLLIDERS TRANSFORM ======================================================

// Função que transforma o collider de parede
std::vector<glm::mat4> TransformWallCollider()
{
    std::vector<glm::mat4> wall_models;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(-11.5f,3.0f,0.0f)
          * Matrix_Rotate_Z(3.1415/2)
          * Matrix_Scale(10.0f, 1.0f, 18.0f);
    wall_models.push_back(model);

    model = Matrix_Translate(11.5f,3.0f,0.0f)
          * Matrix_Rotate_Z(3.1415/2)
          * Matrix_Scale(10.0f, 1.0f, 18.0f);
    wall_models.push_back(model);

    model = Matrix_Translate(0.0f,3.0f,18.0f)
          * Matrix_Rotate_Y(3.1415/2)
          * Matrix_Rotate_Z(3.1415/2)
          * Matrix_Scale(10.0f, 1.0f, 11.5f);
    wall_models.push_back(model);

    model = Matrix_Translate(0.0f,3.0f,-18.0f)
          * Matrix_Rotate_Y(3.1415/2)
          * Matrix_Rotate_Z(3.1415/2)
          * Matrix_Scale(10.0f, 1.0f, 11.5f);
    wall_models.push_back(model);

    return wall_models;
}

// Função que transforma o collider do poste
std::vector<glm::mat4> TransformPoleCollider()
{
    std::vector<glm::mat4> pole_models;

    glm::mat4 model = Matrix_Identity();

    // Transformamos o modelo do poste da cesta de basquete de um lado da quadra
    model = Matrix_Translate(0.0f,3.0f,-13.5f) * Matrix_Scale(0.35f,3.0f,0.35f);
    pole_models.push_back(model);

    // Transformamos o modelo do poste da cesta de basquete do outro lado da quadra
    model = Matrix_Translate(0.0f,3.0f,13.5f) * Matrix_Scale(0.35f,3.0f,0.35f);
    pole_models.push_back(model);

    return pole_models;
}

// Função que transforma o collider da tabela
std::vector<glm::mat4> TransformBackboardCollider()
{
    std::vector<glm::mat4> backboard_models;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(0.0f,3.9187f,12.845f) * Matrix_Scale(1.700f,0.900f,0.03);
    backboard_models.push_back(model);

    model = Matrix_Translate(0.0f,3.9187f,-12.845f) * Matrix_Scale(1.700f,0.900f,0.03);
    backboard_models.push_back(model);

    return backboard_models;
}

// Função que transforma os colliders dos aros das tabelas
std::vector<glm::mat4> TransformRimCollider()
{
    std::vector<glm::mat4> rim_models;

    glm::mat4 model = Matrix_Identity();

    // Transformamos o modelo do aro de basquete de um lado da quadra
    model = Matrix_Translate(0.0f,3.08f,-12.57f) * Matrix_Scale(0.1f,0.1f,0.1f);
    rim_models.push_back(model);

    // Transformamos o modelo do aro de basquete do outro lado da quadra
    model = Matrix_Translate(0.0f,3.08f,12.57f) * Matrix_Scale(0.1f,0.1f,0.1f);
    rim_models.push_back(model);

    return rim_models;
}

// Função que transforma o collider do aro quando o player erra
std::vector<glm::mat4> TransformMissRimCollider()
{
    std::vector<glm::mat4> missrim_models;

    glm::mat4 model = Matrix_Identity();

    model = Matrix_Translate(0.0f,3.1962f,12.5945f) * Matrix_Scale(0.395f,0.001f,0.426f);
    missrim_models.push_back(model);

    model = Matrix_Translate(0.0f,3.1962f,-12.5945f) * Matrix_Scale(0.395f,0.001f,0.426f);
    missrim_models.push_back(model);

    return missrim_models;
}
