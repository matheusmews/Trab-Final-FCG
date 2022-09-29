#include "ball.h"

#define SPHERE     0
#define BUNNY      1
#define PLANE      2
#define COURT      3
#define BACKBOARD  4
#define BACKGROUND 5
#define GLASS      6
#define CUBE       7
#define HAND       8

// Variáveis da bola
glm::vec4 ball_position_c = glm::vec4(0.0f,2.5f,0.6f,1.0f);
GLfloat ball_t;
GLfloat ball_time_now;
GLfloat ball_time_prev;
GLfloat ball_delta_time;

// Pontos de controle da parábola da bola
glm::vec4 p1 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
glm::vec4 p2 = glm::vec4(0.0f,2.85f,0.0f,1.0f);
glm::vec4 p3 = glm::vec4(0.0f,4.0f,0.0f,1.0f);
glm::vec4 p4 = glm::vec4(0.0f,0.0f,0.0f,1.0f);

// Flags que controlam a animação da bola
bool g_BallWasShot = false;

// Função que desenha a bola de basquete quando ela é arremessada
glm::mat4 TransformBall()
{
    glm::mat4 model = Matrix_Identity();

    if (g_BallWasShot)
    {
        //printf("%f\n", ball_t);
        ball_time_now = glfwGetTime();
        ball_delta_time = ball_time_now - ball_time_prev;

        // Verifica o c(t) atual
        glm::vec4 c = powf(1-ball_t,3)*p1 +
                      3*ball_t*powf(1-ball_t,2)*p2 +
                      3*ball_t*ball_t*(1-ball_t)*p3 +
                      powf(ball_t,3)*p4;
        ball_t += 0.5*ball_delta_time;

        model = Matrix_Translate(c.x,c.y,c.z) * Matrix_Scale(0.2f, 0.2f, 0.2f);

        if (ball_t >= 1.0f)
        {
            g_BallWasShot = false;
            ball_t = 0.0f;
        }

        ball_time_prev = ball_time_now;
    }
    else
    {
        model = Matrix_Translate(ball_position_c.x,ball_position_c.y,ball_position_c.z) * Matrix_Scale(0.2f, 0.2f, 0.2f);
    }

    return model;
    //RenderObject("sphere",model,SPHERE);
}




