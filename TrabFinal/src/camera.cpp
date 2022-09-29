#include "camera.h"

#define SPHERE     0
#define BUNNY      1
#define PLANE      2
#define COURT      3
#define BACKBOARD  4
#define BACKGROUND 5
#define GLASS      6
#define CUBE       7
#define HAND       8

// Vari�veis que definem a c�mera em coordenadas esf�ricas, controladas pelo
// usu�rio atrav�s do mouse (veja fun��o CursorPosCallback()). A posi��o
// efetiva da c�mera � calculada dentro da fun��o main(), dentro do loop de
// renderiza��o.
float g_CameraTheta = 0.0f; // �ngulo no plano ZX em rela��o ao eixo Z
float g_CameraPhi = 0.0f;   // �ngulo em rela��o ao eixo Y
float g_CameraDistance = 2.5f; // Dist�ncia da c�mera para a origem

// Vari�veis da c�mera Free Camera
glm::vec4 camera_position_c = glm::vec4(0.0f,0.0f,0.0f,1.0f);
glm::vec4 camera_view_vector;
glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f);

glm::vec4 w;
glm::vec4 u;

glm::vec4 movement_vector;              //W  S  D  A HOFF
int camera_movement_keys[] = {0, 0, 0, 0};

GLfloat camera_time_now;
GLfloat camera_time_prev;
GLfloat camera_delta_time;

// Fun��o que movimenta a c�mera baseado nas teclas W, S, A, D e na movimenta��o do mouse
void MoveFreeCamera()
{
    // Computamos a posi��o da c�mera utilizando coordenadas esf�ricas.  As
    // vari�veis g_CameraDistance, g_CameraPhi, e g_CameraTheta s�o
    // controladas pelo mouse do usu�rio. Veja as fun��es CursorPosCallback()
    // e ScrollCallback().
    float y = sin(g_CameraPhi);
    float z = cos(g_CameraPhi)*cos(g_CameraTheta);
    float x = cos(g_CameraPhi)*sin(g_CameraTheta);

    // Abaixo definimos as var�veis que efetivamente definem a c�mera virtual.
    // Veja slides 195-227 e 229-234 do documento Aula_08_Sistemas_de_Coordenadas.pdf.
    camera_view_vector = glm::vec4(x,y,z,0.0f); // Vetor "view", sentido para onde a c�mera est� virada

    //glm::vec4 teste = glm::normalize(camera_view_vector);
    //std::cout << teste.x << " " << teste.y << " " << teste.z << "\n";

    w = -camera_view_vector/norm(camera_view_vector);
    u = crossproduct(camera_up_vector, w)/norm(crossproduct(camera_up_vector, w));

    movement_vector = glm::normalize(glm::vec4(w.x, 0.0f , w.z, 0.0f));

    camera_time_now = glfwGetTime();
    camera_delta_time = camera_time_now-camera_time_prev;

    // Se a tecla W est� sendo pressionada (camera_movement_keys[0] = true), movimentamos a c�mera para frente.
    if (camera_movement_keys[0])
    {
        camera_position_c -= (movement_vector * camera_delta_time) * 5.0f;
        g_PlayerIsMoving = true;
    }
    // Se a tecla S est� sendo pressionada (camera_movement_keys[1] = true), movimentamos a c�mera para tr�s.
    else if (camera_movement_keys[1])
    {
        camera_position_c += (movement_vector * camera_delta_time) * 5.0f;
        g_PlayerIsMoving = true;
    }
    // Se a tecla D est� sendo pressionada (camera_movement_keys[2] = true), movimentamos a c�mera para a direita.
    if (camera_movement_keys[2])
    {
        camera_position_c += (u * camera_delta_time) * 5.0f;
        g_PlayerIsMoving = true;
    }
    // Se a tecla A est� sendo pressionada (camera_movement_keys[3] = true), movimentamos a c�mera para a esquerda.
    else if (camera_movement_keys[3])
    {
        camera_position_c -= (u * camera_delta_time) * 5.0f;
        g_PlayerIsMoving = true;
    }

    if (!g_PlayerIsJumping)
    {
        camera_position_c.y = 2.06f;
    }

    g_TorsoPositionX = camera_position_c.x;
    g_TorsoPositionY = camera_position_c.y - 0.2f;
    g_TorsoPositionZ = camera_position_c.z;

    ball_position_c.x = camera_position_c.x+camera_view_vector.x;
    ball_position_c.y = camera_position_c.y+camera_view_vector.y - 0.4f;
    ball_position_c.z = camera_position_c.z+camera_view_vector.z;

    camera_time_prev = camera_time_now;
}
