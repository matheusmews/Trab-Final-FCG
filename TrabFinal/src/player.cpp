#include "player.h"

#define SPHERE     0
#define BUNNY      1
#define PLANE      2
#define COURT      3
#define BACKBOARD  4
#define BACKGROUND 5
#define GLASS      6
#define CUBE       7
#define HAND       8

// Váriaveis que controlam o player
// Variáveis que controlam as animações do player
GLfloat player_time_now;
GLfloat player_time_prev;
GLfloat player_delta_time;
// Variáveis que controlam as animações da movimentação do player
GLint right_arm_movement_animation_direction = 1;
GLint left_arm_movement_animation_direction = -1;
GLint right_thigh_movement_animation_direction = -1;
GLint left_thigh_movement_animation_direction = 1;
// Variáveis que controlam as animações do pulo do player
GLfloat player_jump_time_now;
GLfloat player_jump_time_prev;
GLfloat player_jump_delta_time;
GLint jump_direction = 1;
// Variáveis que controlam as animações do arremesso do player
GLint player_shooting_animation_part = 1;
// Variáveis que controlam translação do torso
float g_TorsoPositionX = 0.0f;
float g_TorsoPositionY = 0.32f;
float g_TorsoPositionZ = 0.0f;
// Variáveis que controlam rotação do braço direito
float g_RightArmAngleX = 0.0f;
float g_RightArmAngleY = 0.0f;
float g_RightArmAngleZ = 0.0f;
// Variáveis que controlam rotação do braço esquerdo
float g_LeftArmAngleX = 0.0f;
float g_LeftArmAngleY = 0.0f;
float g_LeftArmAngleZ = 0.0f;
// Variáveis que controlam rotação do antebraço direito
float g_RightForearmAngleX = 0.0f;
float g_RightForearmAngleY = 0.0f;
float g_RightForearmAngleZ = 0.0f;
// Variáveis que controlam rotação do antebraço esquerdo
float g_LeftForearmAngleX = 0.0f;
float g_LeftForearmAngleY = 0.0f;
float g_LeftForearmAngleZ = 0.0f;
// Variáveis que controlam rotação da mão direita (do arremesso)
float g_RightHandAngleX = 0.0f;
float g_RightHandAngleY = 0.0f;
float g_RightHandAngleZ = 0.0f;
// Variáveis que controlam rotação da perna direita
float g_RightLegAngleX = 0.0f;
float g_RightLegAngleY = 0.0f;
float g_RightLegAngleZ = 0.0f;
// Variáveis que controlam rotação da perna esquerda
float g_LeftLegAngleX = 0.0f;
float g_LeftLegAngleY = 0.0f;
float g_LeftLegAngleZ = 0.0f;
// Variáveis que controlam rotação da coxa direita
float g_RightThighAngleX = 0.0f;
float g_RightThighAngleY = 0.0f;
float g_RightThighAngleZ = 0.0f;
// Variáveis que controlam rotação da coxa esquerda
float g_LeftThighAngleX = 0.0f;
float g_LeftThighAngleY = 0.0f;
float g_LeftThighAngleZ = 0.0f;

// Flags que controlam o player
bool g_PlayerIsMoving = false;
bool g_PlayerStartedShot = false;
bool g_PlayerIsShooting = false;
bool g_PlayerIsJumping = false;

// Variáveis que controlam o arremesso
bool g_MeasuringStrength = false;
GLfloat measure_time_prev;
GLfloat measure_time_now;
GLfloat measure_delta_time;

// Matriz que guarda as transformações que chegam na mão direita do player,
// para fazer a animação de arremesso
glm::mat4 right_hand_model;

// Pilha que guardará as matrizes de modelagem.
std::stack<glm::mat4>  g_MatrixStack;

// Função que pega a matriz M e guarda a mesma no topo da pilha
void PushMatrix(glm::mat4 M)
{
    g_MatrixStack.push(M);
}

// Função que remove a matriz atualmente no topo da pilha e armazena a mesma na variável M
void PopMatrix(glm::mat4& M)
{
    if ( g_MatrixStack.empty() )
    {
        M = Matrix_Identity();
    }
    else
    {
        M = g_MatrixStack.top();
        g_MatrixStack.pop();
    }
}

// Função que desenha o jogador através da modelagem de várias instâncias de um cubo
std::vector<glm::mat4> TransformPlayer()
{
    std::vector<glm::mat4> player_models;

    float ALPHA = 5.0;
    // Cada cópia do cubo possui uma matriz de modelagem independente,
    // já que cada cópia estará em uma posição (rotação, escala, ...)
    // diferente em relação ao espaço global (World Coordinates). Veja
    // slides 2-14 e 184-190 do documento Aula_08_Sistemas_de_Coordenadas.pdf.
    //
    // Entretanto, neste laboratório as matrizes de modelagem dos cubos
    // serão construídas de maneira hierárquica, tal que operações em
    // alguns objetos influenciem outros objetos. Por exemplo: ao
    // transladar o torso, a cabeça deve se movimentar junto.
    // Veja slides 243-273 do documento Aula_08_Sistemas_de_Coordenadas.pdf

    g_TorsoPositionX = camera_position_c.x;
    g_TorsoPositionY = camera_position_c.y - 0.2f;
    g_TorsoPositionZ = camera_position_c.z;

    glm::vec4 cu = glm::vec4(g_TorsoPositionX, g_TorsoPositionY, g_TorsoPositionZ, 0.0f) + (movement_vector * 0.15f);

    /*
    Para desenhar o corpo e guardar as matrizes, os comentários abaixo consideram a
    seguinte estrutura simplificada do corpo humano
                              - torso (não tem cabeça porque o jogo é em 1º pessoa)
                             |
                             v
         braço esquerdo -> / | \ <- braço direito
    antebraço esquerdo -> |  |  | <- antebraço direito
          mão esquerda -> .  |  . <- mão direita
                             |
           coxa esquerda -> / \ <- coxa direita
                           /   \
        perna esquerda -> |     | <- perna direita
          pé esquerdo -> -       - pé direito
    Será possível ver pelo código abaixo que os antebraços e as mãos estão ligadas
    aos braços, e as mãos estão ligadas aos antebraços. Ou seja, se um braço é
    rotacionado, o antebraço e a mão também são, mas se um antebraço é rotacioado,
    apenas a mão é rotacionado. O mesmo ocorre com os membros inferiores, onde as
    pernas e os pés estão ligados às coxas, e os pés estão ligados às pernas.
    */

    glm::mat4 model = Matrix_Identity(); // Transformação inicial = identidade.
    // Translação e rotação inicial do torso
    model = model * Matrix_Translate(cu.x, cu.y, cu.z)
                  * Matrix_Rotate_Y(g_CameraTheta);
    // Guardamos matriz model atual na pilha
    PushMatrix(model);
        // Atualizamos a matriz model (multiplicação à direita) para fazer um escalamento do torso
        model = model * Matrix_Scale(0.1f*ALPHA, 0.125f*ALPHA, 0.025f*ALPHA);
        player_models.push_back(model); // #### TORSO
    // Tiramos da pilha a matriz model guardada anteriormente
    PopMatrix(model);

    //cabeça
    PushMatrix(model);
        model = model * Matrix_Translate(0.0f, 0.05f, 0.0f);
            model = model * Matrix_Scale(-0.150f, -0.15f, 0.15f);
        player_models.push_back(model); // #### CABEÇA // Desenhamos o cabeça
    PopMatrix(model);

    //braço direito
    PushMatrix(model); // Guardamos matriz model atual na pilha
        model = model * Matrix_Translate(-0.06875f*ALPHA, 0.0f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com uma translação para o braço direito
        PushMatrix(model); // Guardamos matriz model atual na pilha
            model = model // Atualizamos matriz model (multiplicação à direita) com a rotação do braço direito
                  * Matrix_Rotate_Z(g_RightArmAngleZ)  // TERCEIRO rotação Z de Euler
                  * Matrix_Rotate_Y(g_RightArmAngleY)  // SEGUNDO rotação Y de Euler
                  * Matrix_Rotate_X(g_RightArmAngleX); // PRIMEIRO rotação X de Euler
            right_hand_model = model;
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Scale(0.025f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento do braço direito
                player_models.push_back(model); // #### BRAÇO DIREITO // Desenhamos o braço direito
            PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Translate(0.0f*ALPHA, -0.08125f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com a translação do antebraço direito
                model = model // Atualizamos matriz model (multiplicação à direita) com a rotação do antebraço direito
                      * Matrix_Rotate_Z(g_RightForearmAngleZ)  // TERCEIRO rotação Z de Euler
                      * Matrix_Rotate_Y(g_RightForearmAngleY)  // SEGUNDO rotação Y de Euler
                      * Matrix_Rotate_X(g_RightForearmAngleX); // PRIMEIRO rotação X de Euler
                right_hand_model = right_hand_model
                                 * Matrix_Translate(0.0f*ALPHA, -0.08125f*ALPHA, 0.0f*ALPHA)
                                 * Matrix_Rotate_Z(g_RightForearmAngleZ)
                                 * Matrix_Rotate_Y(g_RightForearmAngleY)
                                 * Matrix_Rotate_X(g_RightForearmAngleX);
                PushMatrix(model); // Guardamos matriz model atual na pilha
                    model = model * Matrix_Scale(0.025f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento do antebraço direito
                    player_models.push_back(model); // #### ANTEBRAÇO DIREITO // Desenhamos o antebraço direito
                    PushMatrix(model);
                        model = model * Matrix_Translate(0.0f, -1.06f, 0.0f);
                        model = model * Matrix_Scale(1.0f, 0.15f, 1.0f);
                        player_models.push_back(model); // #### MÃO DIREITA // Desenhamos a mão direita
                        right_hand_model = right_hand_model * Matrix_Translate(0.15f, -0.52f, -0.1f);
                    PopMatrix(model);
                PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
        PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
    PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente

    //braço esquerdo
    PushMatrix(model); // Guardamos matriz model atual na pilha
        model = model * Matrix_Translate(0.06875f*ALPHA, 0.0f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplica�ão à direita) com uma translação para o braço esquerdo
        PushMatrix(model); // Guardamos matriz model atual na pilha
            model = model // Atualizamos matriz model (multiplicação à direita) com a rotação do braço esquerdo
                  * Matrix_Rotate_Z(g_LeftArmAngleZ)  // TERCEIRO rotação Z de Euler
                  * Matrix_Rotate_Y(g_LeftArmAngleY)  // SEGUNDO rotação Y de Euler
                  * Matrix_Rotate_X(g_LeftArmAngleX); // PRIMEIRO rotação X de Euler
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Scale(0.025f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento do braço esquerdo
                player_models.push_back(model); // #### BRAÇO ESQUERDO // Desenhamos o braço esquerdo
            PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Translate(0.0f*ALPHA, -0.08125f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com a translação do antebraço esquerdo
                model = model // Atualizamos matriz model (multiplicação à direita) com a rotação do antebraço esquerdo
                      * Matrix_Rotate_Z(g_LeftForearmAngleZ)  // TERCEIRO rotação Z de Euler
                      * Matrix_Rotate_Y(g_LeftForearmAngleY)  // SEGUNDO rotação Y de Euler
                      * Matrix_Rotate_X(g_LeftForearmAngleX); // PRIMEIRO rotação X de Euler
                PushMatrix(model); // Guardamos matriz model atual na pilha
                    model = model * Matrix_Scale(0.025f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento do antebraço esquerdo
                    player_models.push_back(model); // #### ANTEBRAÇO ESQUERDO // Desenhamos o antebraço esquerdo
                    PushMatrix(model);
                        model = model * Matrix_Translate(0.0f, -1.06f, 0.0f);
                        model = model * Matrix_Scale(1.0f, 0.15f, 1.0f);
                        player_models.push_back(model); // #### MÃO ESQUERDA // Desenhamos a mão esquerda
                    PopMatrix(model);
                PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
        PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
    PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente

    //coxa direita
    PushMatrix(model); // Guardamos matriz model atual na pilha
        model = model * Matrix_Translate(-0.02625f*ALPHA, -0.13125f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com uma translação para coxa direita
        PushMatrix(model); // Guardamos matriz model atual na pilha
            model = model // Atualizamos matriz model (multiplicação à direita) com a rotação da coxa direita
                  * Matrix_Rotate_Z(g_RightThighAngleZ)  // TERCEIRO rotação Z de Euler
                  * Matrix_Rotate_Y(g_RightThighAngleY)  // SEGUNDO rotação Y de Euler
                  * Matrix_Rotate_X(g_RightThighAngleX); // PRIMEIRO rotação X de Euler
            PushMatrix(model); // Guardamos a matriz model atual na pilha
                model = model * Matrix_Scale(0.0375f*ALPHA, 0.08125f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento da coxa direita
                player_models.push_back(model); // #### COXA DIREITA // Desenhamos a coxa direita
            PopMatrix(model);
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Translate(0.0f*ALPHA, -0.0875f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com a translação da perna direita
                PushMatrix(model); // Guardamos matriz model atual na pilha
                    model = model * Matrix_Scale(0.03125f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento da perna direita
                    player_models.push_back(model); // #### PERNA DIREITA // Desenhamos a perna direita
                    PushMatrix(model);
                        model = model * Matrix_Translate(0.0f, -1.06f, 0.4f);
                        model = model * Matrix_Scale(0.85f, 0.2f, 2.0f);
                        player_models.push_back(model); // #### PÉ DIREITO // Desenhamos o pé direito
                    PopMatrix(model);
                PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PopMatrix(model);
        PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
    PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente

    //coxa esquerda
    PushMatrix(model); // Guardamos matriz model atual na pilha
        model = model * Matrix_Translate(0.02625f*ALPHA, -0.13125f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com uma translação para a coxa esquerda
        PushMatrix(model); // Guardamos matriz model atual na pilha
            model = model // Atualizamos matriz model (multiplicação à direita) com a rotação da coxa esquerda
                  * Matrix_Rotate_Z(g_LeftThighAngleZ)  // TERCEIRO rotação Z de Euler
                  * Matrix_Rotate_Y(g_LeftThighAngleY)  // SEGUNDO rotação Y de Euler
                  * Matrix_Rotate_X(g_LeftThighAngleX); // PRIMEIRO rotação X de Euler
            PushMatrix(model); // Guardamos a matriz model atual na pilha
                model = model * Matrix_Scale(0.0375f*ALPHA, 0.08125f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento da coxa esquerda
                player_models.push_back(model); // #### COXA ESQUERDA // Desenhamos a coxa esquerda
            PopMatrix(model);
            PushMatrix(model); // Guardamos matriz model atual na pilha
                model = model * Matrix_Translate(0.0f*ALPHA, -0.0875f*ALPHA, 0.0f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com a translação da perna esquerda
                PushMatrix(model); // Guardamos matriz model atual na pilha
                    model = model * Matrix_Scale(0.03125f*ALPHA, 0.075f*ALPHA, 0.025f*ALPHA); // Atualizamos matriz model (multiplicação à direita) com um escalamento da perna esquerda
                    player_models.push_back(model); // #### PERNA ESQUERDA // Desenhamos a perna direita
                    PushMatrix(model);
                        model = model * Matrix_Translate(0.0f, -1.06f, 0.4f);
                        model = model * Matrix_Scale(0.85f, 0.2f, 2.0f);
                        player_models.push_back(model); // #### PÉ ESQUERDO // Desenhamos o pé direito
                    PopMatrix(model);
                PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
            PopMatrix(model);
        PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente
    PopMatrix(model); // Tiramos da pilha a matriz model guardada anteriormente

    return player_models;
}

// Função que transforma o collider do player
glm::mat4 TransformPlayerCollider()
{
    glm::mat4 model = Matrix_Translate(g_TorsoPositionX, g_TorsoPositionY, g_TorsoPositionZ)
                    * Matrix_Scale(0.6f, 1.80f, 0.4f);

    return model;
}

// Função que anima a movimentação do jogador
void AnimatePlayerMovement()
{
    float delta_arm = 3.141592 * 1.5;
    float max_arm_angle = 1.0f;
    float delta_thigh = 3.141592 * 0.75;
    float max_thigh_angle = 0.5f;

    player_time_now = glfwGetTime();
    player_delta_time = player_time_now - player_time_prev;
    player_time_prev = player_time_now;

    g_RightArmAngleX += delta_arm * player_delta_time * right_arm_movement_animation_direction;
    g_LeftArmAngleX += delta_arm * player_delta_time * left_arm_movement_animation_direction;

    g_RightThighAngleX += delta_thigh * player_delta_time * right_thigh_movement_animation_direction;
    g_LeftThighAngleX += delta_thigh * player_delta_time * left_thigh_movement_animation_direction;

    if (g_RightArmAngleX > max_arm_angle)
    {
        g_RightArmAngleX = max_arm_angle;
        right_arm_movement_animation_direction = -1;
    }
    else if (g_RightArmAngleX < -max_arm_angle)
    {
        g_RightArmAngleX = -max_arm_angle;
        right_arm_movement_animation_direction = 1;
    }

    if (g_LeftArmAngleX > max_arm_angle)
    {
        g_LeftArmAngleX = max_arm_angle;
        left_arm_movement_animation_direction = -1;
    }
    else if (g_LeftArmAngleX < -max_arm_angle)
    {
        g_LeftArmAngleX = -max_arm_angle;
        left_arm_movement_animation_direction = 1;
    }

    if (g_RightThighAngleX > max_thigh_angle)
    {
        g_RightThighAngleX = max_thigh_angle;
        right_thigh_movement_animation_direction = -1;
    }
    else if (g_RightThighAngleX < -max_thigh_angle)
    {
        g_RightThighAngleX = -max_thigh_angle;
        right_thigh_movement_animation_direction = 1;
    }

    if (g_LeftThighAngleX > max_thigh_angle)
    {
        g_LeftThighAngleX = max_thigh_angle;
        left_thigh_movement_animation_direction = -1;
    }
    else if (g_LeftThighAngleX < -max_thigh_angle)
    {
        g_LeftThighAngleX = -max_thigh_angle;
        left_thigh_movement_animation_direction = 1;
    }
}

// Função que anima o pulo do jogador
void AnimatePlayerJump()
{
    float delta_jump = 3.0f;
    float max_jump_height = 3.3f;

    player_jump_time_now = glfwGetTime();
    player_jump_delta_time = player_jump_time_now - player_jump_time_prev;
    player_jump_time_prev = player_jump_time_now;

    camera_position_c.y += delta_jump * jump_direction * player_jump_delta_time;

    if (camera_position_c.y > max_jump_height)
    {
        camera_position_c.y = max_jump_height;
        jump_direction = -1;
    }
    else if (camera_position_c.y < 1.80)
    {
        camera_position_c.y = 1.80;
        jump_direction = 1;
        g_PlayerIsJumping = false;
    }
}

// Função que mede a força do arremesso
void MeasureShotStrength()
{
    //printf("medindo\n");
    measure_time_now = glfwGetTime();
    measure_delta_time = measure_time_now-measure_time_prev;

    //printf("%f\n", measure_delta_time);

    if (measure_delta_time > 0.5f && !g_PlayerIsShooting)
    {
        player_time_prev = glfwGetTime();
        g_PlayerIsShooting = true;
        //printf("player pode chutar\n");
    }
    else if (measure_delta_time > 1.2f && g_PlayerIsShooting)
    {
        g_MeasuringStrength = false;
        //printf("tah na hora de soltar\n");
    }
}

// Função que anima o arremesso do jogador
void AnimatePlayerShot()
{
    float delta_arm = 4.5f / 1;
    float max_arm_angle = -1.0f;

    float delta_forearm = 4.5f / 1;
    float max_left_arm_angle_x = -0.5;
    float max_right_forearm_angle_x = -1.8f;
    float max_right_forearm_angle_z = 0.0f;
    float max_left_forearm_angle_x = -0.4f;
    float max_left_forearm_angle_z = -1.0f;

    player_time_now = glfwGetTime();
    player_delta_time = player_time_now - player_time_prev;
    player_time_prev = player_time_now;

    switch(player_shooting_animation_part)
    {
        case 1:
            if (g_RightForearmAngleX > max_right_forearm_angle_x)
                g_RightForearmAngleX -= player_delta_time * delta_forearm;
            if (g_RightForearmAngleZ < max_right_forearm_angle_z)
                g_RightForearmAngleZ += player_delta_time * delta_forearm;
            if (g_LeftForearmAngleX > max_left_forearm_angle_x)
                g_LeftForearmAngleX -= player_delta_time * delta_forearm;
            if (g_LeftForearmAngleZ > max_left_forearm_angle_z)
                g_LeftForearmAngleZ -= player_delta_time * delta_forearm;
            if (g_LeftArmAngleX > max_left_arm_angle_x)
                g_LeftArmAngleX -= player_delta_time * delta_forearm;

            if (g_RightForearmAngleX <= max_right_forearm_angle_x &&
                g_RightForearmAngleZ >= max_right_forearm_angle_z &&
                g_LeftForearmAngleX  <= max_left_forearm_angle_x  &&
                g_LeftForearmAngleZ  <= max_left_forearm_angle_z)
            {
                g_RightForearmAngleX = max_right_forearm_angle_x;
                g_RightForearmAngleZ = max_right_forearm_angle_z;
                g_LeftForearmAngleX  = max_left_forearm_angle_x;
                g_LeftForearmAngleZ  = max_left_forearm_angle_z;

                player_shooting_animation_part += 1;
            }
            break;

        case 2:
            g_RightArmAngleX -= player_delta_time * delta_arm;
            g_LeftArmAngleX  -= player_delta_time * delta_arm;

            if (g_RightArmAngleX <= max_arm_angle)
            {
                g_RightArmAngleX = max_arm_angle;

                player_shooting_animation_part += 1;
            }
            break;

        case 3:
            if (!g_MeasuringStrength)
            {
                g_RightArmAngleX -= player_delta_time * delta_arm;
                g_RightForearmAngleX += player_delta_time * delta_forearm;

                if (g_RightArmAngleX <=  -2.0f)
                {
                    g_BallWasShot = true;
                    ball_time_prev = glfwGetTime();
                    ball_t = 0.0f;

                    GLfloat distance_shot = porcentagem();

                    glm::vec4 norm_cvv = glm::normalize(glm::vec4(camera_view_vector_shot.x,0.0f,camera_view_vector_shot.z,0.0f));

                    p1.x = ball_position_c.x + 0.0f*norm_cvv.x;
                    p2.x = ball_position_c.x + (distance_shot/3.0f)*norm_cvv.x;
                    p3.x = ball_position_c.x + (2*distance_shot/3.0f)*norm_cvv.x;
                    p4.x = ball_position_c.x + (distance_shot)*norm_cvv.x;

                    p1.y = ball_position_c.y + 0.7f;
                    p2.y = ball_position_c.y + std::max(3.5f,(distance_shot*0.55f));
                    p3.y = ball_position_c.y + std::max(3.5f,(distance_shot*0.55f));
                    p4.y = 3.0f;

                    p1.z = ball_position_c.z + 0.0f*norm_cvv.z;
                    p2.z = ball_position_c.z + (distance_shot/3.0f)*norm_cvv.z;
                    p3.z = ball_position_c.z + (2*distance_shot/3.0f)*norm_cvv.z;
                    p4.z = ball_position_c.z + (distance_shot)*norm_cvv.z;

                    BALL_SPEED = 0.3f;
                    if (distance_shot < 3.5f)
                        BALL_SPEED = 0.55f;

                    whichRimWillBallCollide = BallWillCollideWithRim();
                    if (whichRimWillBallCollide != 1 && whichRimWillBallCollide != 2)
                    {
                        g_BucketShot = false;
                        MAX_T = 1.25f;
                    }
                    else
                    {
                        g_BucketShot = true;
                        g_BallOnRim = false;
                        MAX_T = 1.0f;
                    }

                    player_shooting_animation_part += 1;
                }
            }
            break;

        case 4:
            if (g_RightArmAngleX < 0.0f)
                g_RightArmAngleX += player_delta_time * delta_arm/5;
            if (g_LeftArmAngleX < 0.0f)
                g_LeftArmAngleX += player_delta_time * delta_arm/5;
            if (g_RightForearmAngleX < 0.0f)
                g_RightForearmAngleX += player_delta_time * delta_forearm/5;
            if (g_RightForearmAngleZ > 0.0f)
                g_RightForearmAngleZ -= player_delta_time * delta_forearm/5;
            if (g_LeftForearmAngleX < 0.0f)
                g_LeftForearmAngleX += player_delta_time * delta_forearm/5;
            if (g_LeftForearmAngleZ < 0.0f)
                g_LeftForearmAngleZ += player_delta_time * delta_forearm/5;

            if (g_RightArmAngleX >= 0.0f && g_LeftArmAngleX >= 0.0f &&
                g_RightForearmAngleX >= 0.0f && g_RightForearmAngleZ <= 0.0f &&
                g_LeftForearmAngleX >= 0.0f && g_LeftForearmAngleZ >= 0.0f)
            {
                g_RightArmAngleX = 0.0f;
                g_LeftArmAngleX = 0.0f;
                g_RightForearmAngleX = 0.0f;
                g_RightForearmAngleZ = 0.0f;
                g_LeftForearmAngleX = 0.0f;
                g_LeftForearmAngleZ = 0.0f;

                g_PlayerIsShooting = false;
                player_shooting_animation_part = 1;
            }
            break;
    }
}

// Função que controla todas as animações do player
void AnimatePlayer()
{
    if (g_MeasuringStrength)
        MeasureShotStrength();

    // Animação de movimentação e arremesso não podem acontecer ao mesmo tempo
    if (g_PlayerStartedShot)
    {
        g_RightArmAngleX = 0.0f;
        g_LeftArmAngleX = 0.0f;
        g_RightThighAngleX = 0.0f;
        g_LeftThighAngleX = 0.0f;

        g_PlayerStartedShot = false;
        g_MeasuringStrength = true;
        measure_time_prev = glfwGetTime();
    }
    else if (g_PlayerIsShooting)
    {
        AnimatePlayerShot();
    }
    else if (g_PlayerIsMoving)
    {
        AnimatePlayerMovement();
    }
    else
    {
        g_RightArmAngleX = 0.0f;
        g_LeftArmAngleX = 0.0f;
        g_RightThighAngleX = 0.0f;
        g_LeftThighAngleX = 0.0f;
    }

    // Pulo independe do arremessa ou da movimentação
    if (g_PlayerIsJumping)
    {
        AnimatePlayerJump();
    }
}

