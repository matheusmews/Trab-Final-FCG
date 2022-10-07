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
float ball_radius = 0.2f;
short whichRimWillBallCollide;

GLfloat ball_t;
GLfloat ball_time_now;
GLfloat ball_time_prev;
GLfloat ball_delta_time;

bool GouradShading = false;

GLfloat BALL_SPEED;
GLfloat MAX_T;

// Pontos de controle da parábola da bola
glm::vec4 p1 = glm::vec4(0.0f,1.0f,0.0f,1.0f);
glm::vec4 p2 = glm::vec4(0.0f,2.85f,0.0f,1.0f);
glm::vec4 p3 = glm::vec4(0.0f,4.0f,0.0f,1.0f);
glm::vec4 p4 = glm::vec4(0.0f,0.0f,0.0f,1.0f);

glm::vec4 prev_c;
glm::vec4 final_c;

GLfloat distance_shot;

// Flags que controlam a animação da bola
bool g_BallWasShot = false;
bool g_BallOnRim = false;
bool g_BucketShot = false;
bool g_BallCollided = false;

glm::vec4 original_vec;

// Função que desenha a bola de basquete quando ela é arremessada
glm::mat4 TransformBall()
{
    glm::mat4 model = Matrix_Identity();

    if (g_PlayerIsShooting && !g_BallWasShot)
    {
        model = right_hand_model * Matrix_Scale(0.2f, 0.2f, 0.2f);
        //0.015625
        //0.02109375
        //0.015625
        //printf("a\n");
    }
    else if (g_BallCollided)
    {
        model = TransformBallAfterCollide();
    }
    else if (g_BallWasShot and g_BucketShot)
    {
        model = TransformBallMadeShot();
    }
    else if (g_BallWasShot and !g_BucketShot)
    {
        model = TransformBallNonMadeShot();
    }
    else
    {
        ball_position_c.x = camera_position_c.x+camera_view_vector_shot.x;
        ball_position_c.y = camera_position_c.y+camera_view_vector_shot.y - 0.2f;
        ball_position_c.z = camera_position_c.z+camera_view_vector_shot.z;

        model = Matrix_Translate(ball_position_c.x,ball_position_c.y,ball_position_c.z) * Matrix_Scale(0.15f, 0.15f, 0.15f);
    }

    return model;
}

// Função que desenha a bola de basquete quando ela é arremessada e vai acertar
glm::mat4 TransformBallMadeShot()
{
    glm::mat4 model = Matrix_Identity();

    ball_time_now = glfwGetTime();
    ball_delta_time = ball_time_now - ball_time_prev;

    if (!g_BallOnRim)
    {
        // Verifica o c(t) atual
        glm::vec4 c = powf(1-ball_t,3)*p1 + 3*ball_t*powf(1-ball_t,2)*p2 + 3*ball_t*ball_t*(1-ball_t)*p3 + powf(ball_t,3)*p4;
        ball_t += BALL_SPEED*ball_delta_time;

        SetCollisionVector(c,prev_c);

        // Verifica se a bola colidiu com a tabela
        if ((CheckCollisionSphereCube(c,ball_radius,bbox_max_backboard1_collider,bbox_min_backboard1_collider) ||
             CheckCollisionSphereCube(c,ball_radius,bbox_max_backboard2_collider,bbox_min_backboard2_collider))
             && ball_t <= MAX_T/10.0f)
        {
            g_BallCollided = true;
            ball_t = 0.0f;
            ball_time_prev = ball_time_now;
        }

        model = Matrix_Translate(c.x,c.y,c.z) * Matrix_Scale(0.15f, 0.15f, 0.15f);

        if (ball_t >= MAX_T)
        {
            if (whichRimWillBallCollide == 1)
                points_p1 += 2 + (distance_shot>=6.4f);
            else
                points_p2 += 2 + (distance_shot>=6.4f);

            final_c = c;
            g_BallOnRim = true;
        }

        prev_c = c;
    }
    else
    {
        model = Matrix_Translate(final_c.x,final_c.y,final_c.z) * Matrix_Scale(0.15f, 0.15f, 0.15f);

        if (final_c.x > 0.0f)
            final_c.x -= 1.2f*ball_delta_time;
        else if (final_c.x < 0.0f)
            final_c.x += 1.2f*ball_delta_time;

        if (final_c.z > 12.56f)
            final_c.z -= 1.2f*ball_delta_time;
        else if (final_c.x < 12.56f)
            final_c.z += 1.2f*ball_delta_time;

        if (final_c.y > 2.8f)
            final_c.y -= 1.2f*ball_delta_time;
        else
            final_c.y -= 3.0f*ball_delta_time;

        if (final_c.y <= 0.0f)
            g_BallWasShot = false;
    }

    ball_time_prev = ball_time_now;

    return model;
}

// Função que desenha a bola de basquete quando ela é arremessada e vai errar
glm::mat4 TransformBallNonMadeShot()
{
    glm::mat4 model = Matrix_Identity();

    //printf("%f\n", ball_t);
    ball_time_now = glfwGetTime();
    ball_delta_time = ball_time_now - ball_time_prev;

    // Verifica o c(t) atual
    glm::vec4 c = powf(1-ball_t,3)*p1 + 3*ball_t*powf(1-ball_t,2)*p2 + 3*ball_t*ball_t*(1-ball_t)*p3 + powf(ball_t,3)*p4;
    ball_t += BALL_SPEED*ball_delta_time;

    SetCollisionVector(c,prev_c);

    // Verifica se a bola colidiu com a tabela ou o aro
    if (CheckCollisionSphereCube(c,ball_radius,bbox_max_backboard1_collider,bbox_min_backboard1_collider) or
        CheckCollisionSphereCube(c,ball_radius,bbox_max_backboard2_collider,bbox_min_backboard2_collider) or
        CheckCollisionSphereCube(c,ball_radius,bbox_max_missrim1_collider,bbox_min_missrim1_collider) or
        CheckCollisionSphereCube(c,ball_radius,bbox_max_missrim2_collider,bbox_min_missrim2_collider))
    {
        g_BallCollided = true;
        ball_t = 0.0f;
        ball_time_prev = ball_time_now;
    }

    // Se não colidiu "move" a bola e salva esse ponto c(t) como prev_c
    model = Matrix_Translate(c.x,c.y,c.z) * Matrix_Scale(0.15f, 0.15f, 0.15f);

    if (ball_t >= MAX_T)
        g_BallWasShot = false;

    ball_time_prev = ball_time_now;
    prev_c = c;

    return model;
}

// Função que desenha a bola de basquete após ela colidir com algo
glm::mat4 TransformBallAfterCollide()
{
    glm::mat4 model = Matrix_Identity();

    ball_time_now = glfwGetTime();
    ball_delta_time = ball_time_now - ball_time_prev;

    prev_c += BALL_SPEED*0.015f*collision_ball_handling_vector;
    ball_t += BALL_SPEED*ball_delta_time;

    if (CheckCollisionSphereCube(prev_c,ball_radius,bbox_max_backboard1_collider,bbox_min_backboard1_collider) or
        CheckCollisionSphereCube(prev_c,ball_radius,bbox_max_backboard2_collider,bbox_min_backboard2_collider) or
        CheckCollisionSphereCube(prev_c,ball_radius,bbox_max_missrim1_collider,bbox_min_missrim1_collider) or
        CheckCollisionSphereCube(prev_c,ball_radius,bbox_max_missrim2_collider,bbox_min_missrim2_collider))
    {
        g_BallCollided = true;
        ball_t = 0.0f;
    }

    model = Matrix_Translate(prev_c.x,prev_c.y,prev_c.z) * Matrix_Scale(0.15f, 0.15f, 0.15f);

    if (ball_t >= 0.5f)
    {
        g_BallWasShot = false;
        g_BallCollided = false;
    }

    ball_time_prev = ball_time_now;

    return model;
}

// Função que pré calcula a trajetória da bola e verifica se ela
// vai colidir com o aro, retornando 0 se não vai colidir ou 1 ou
// 2, respectivamente se vai colidir com o aro 1 e 2
short BallWillCollideWithRim()
{
    glm::vec4 c;
    ball_t = 0.0f;

    for (ball_t; ball_t <= 1.0f; ball_t += 0.005)
    {
        c = powf(1-ball_t,3)*p1 +
            3*ball_t*powf(1-ball_t,2)*p2 +
            3*ball_t*ball_t*(1-ball_t)*p3 +
            powf(ball_t,3)*p4;

        if (CheckCollisionSpherePoint(rim_1_collider_center, rim_colliders_radius, c))
        {
            ball_t = 0.0f;
            return 1;
        }
        else if (CheckCollisionSpherePoint(rim_2_collider_center, rim_colliders_radius, c))
        {
            ball_t = 0.0f;
            return 2;
        }

        //printf("rim 1 center = %f %f %f\n", rim_1_collider_center.x, rim_1_collider_center.y, rim_1_collider_center.z);
        //printf("rim 2 center = %f %f %f\n", rim_2_collider_center.x, rim_2_collider_center.y, rim_2_collider_center.z);
        //printf("bola         = %f %f %f\n\n", c.x, c.y, c.z);
    }

    ball_t = 0.0f;
    return 0;
}

GLfloat porcentagem()
{
    glm::vec4 backboard1_vector = glm::normalize(glm::vec4(0.0f,3.05f,12.56f,1.0f)-camera_position_c);
    glm::vec4 backboard2_vector = glm::normalize(glm::vec4(0.0f,3.05f,-12.56f,1.0f)-camera_position_c);
    GLfloat angle_diff_backboard1 = dotproduct(camera_view_vector_shot,backboard1_vector);
    GLfloat angle_diff_backboard2 = dotproduct(camera_view_vector_shot,backboard2_vector);

    printf("%f x %f ===================\n", angle_diff_backboard1, angle_diff_backboard2);

    if (fabs(1.0f-measure_delta_time) <= 0.0999f)
    {
        measure_delta_time = 1.0f;
    }

    //measure_delta_time = 1.0f;
    printf("%f\n", measure_delta_time);

    distance_shot;
    if (angle_diff_backboard1 >= angle_diff_backboard2)
    {
        distance_shot = measure_delta_time * sqrt( powf(ball_position_c.x-(0.0f+camera_view_vector_shot.x*0.14),2) + powf(ball_position_c.z-(12.56+camera_view_vector_shot.z*0.14),2) );
    }
    else
    {
        distance_shot = measure_delta_time * sqrt( powf(ball_position_c.x-(0.0f+camera_view_vector_shot.x*0.14),2) + powf(ball_position_c.z-(-12.56+camera_view_vector_shot.z*0.14),2) );
    }

    return distance_shot;
}


