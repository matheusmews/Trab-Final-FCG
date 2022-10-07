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

// Variáveis que definem a câmera em coordenadas esféricas, controladas pelo
// usuário através do mouse (veja função CursorPosCallback()). A posição
// efetiva da câmera é calculada dentro da função main(), dentro do loop de
// renderização.
float g_CameraTheta = 0.0f; // Ângulo no plano ZX em relação ao eixo Z
float g_CameraPhi = 0.0f;   // Ângulo em relação ao eixo Y
float g_CameraDistance = 5.5f; // Distância da câmera para a origem

bool isCameraLookAt;

// Variáveis da câmera Free Camera
glm::vec4 camera_position_c = glm::vec4(0.0f,10.0f,0.0f,1.0f);
glm::vec4 camera_view_vector;
glm::vec4 camera_up_vector   = glm::vec4(0.0f,1.0f,0.0f,0.0f);

glm::vec4 camera_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

glm::vec4 camera_view_vector_shot;

glm::vec4 w;
glm::vec4 u;

glm::vec4 movement_vector;              //W  S  D  A HOFF
int camera_movement_keys[] = {0, 0, 0, 0};

GLfloat camera_time_now;
GLfloat camera_time_prev;
GLfloat camera_delta_time;

// Função que movimenta a câmera baseado nas teclas W, S, A, D e na movimentação do mouse
void MoveFreeCamera(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min,
                    glm::vec3 bbox_plane_max, glm::vec3 bbox_plane_min)
{
    // Computamos a posição da câmera utilizando coordenadas esféricas.  As
    // variáveis g_CameraDistance, g_CameraPhi, e g_CameraTheta são
    // controladas pelo mouse do usuário. Veja as funções CursorPosCallback()
    // e ScrollCallback().
    float y = sin(g_CameraPhi);
    float z = cos(g_CameraPhi)*cos(g_CameraTheta);
    float x = cos(g_CameraPhi)*sin(g_CameraTheta);

    // Abaixo definimos as varáveis que efetivamente definem a câmera virtual.
    // Veja slides 195-227 e 229-234 do documento Aula_08_Sistemas_de_Coordenadas.pdf.
    camera_view_vector = glm::vec4(x,y,z,0.0f); // Vetor "view", sentido para onde a câmera está virada
    camera_view_vector_shot = camera_view_vector;

    w = -camera_view_vector/norm(camera_view_vector);
    u = crossproduct(camera_up_vector, w)/norm(crossproduct(camera_up_vector, w));

    movement_vector = glm::normalize(glm::vec4(w.x, 0.0f , w.z, 0.0f));

    camera_time_now = glfwGetTime();
    camera_delta_time = camera_time_now-camera_time_prev;

    // Se a tecla W está sendo pressionada (camera_movement_keys[0] = true), movimentamos a câmera para frente.
    if (camera_movement_keys[0])
    {
        glm::vec4 aux_cam_pos = camera_position_c - (movement_vector * camera_delta_time) * 5.0f;
        glm::vec4 bbox_max_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
        glm::vec4 bbox_min_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

        if (!CheckCollisionCubeCube(bbox_max_pole1_collider, bbox_min_pole1_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&
            !CheckCollisionCubeCube(bbox_max_pole2_collider, bbox_min_pole2_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&

            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall1_collider, bbox_min_wall1_collider, wall1_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall2_collider, bbox_min_wall2_collider, wall2_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall3_collider, bbox_min_wall3_collider, wall3_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall4_collider, bbox_min_wall4_collider, wall4_normal))
        {
            camera_position_c -= (movement_vector * camera_delta_time) * 5.0f;
            g_PlayerIsMoving = true;
        }
    }
    // Se a tecla S está sendo pressionada (camera_movement_keys[1] = true), movimentamos a câmera para trás.
    else if (camera_movement_keys[1])
    {
        glm::vec4 aux_cam_pos = camera_position_c + (movement_vector * camera_delta_time) * 5.0f;
        glm::vec4 bbox_max_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
        glm::vec4 bbox_min_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

        if (!CheckCollisionCubeCube(bbox_max_pole1_collider, bbox_min_pole1_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&
            !CheckCollisionCubeCube(bbox_max_pole2_collider, bbox_min_pole2_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&

            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall1_collider, bbox_min_wall1_collider, wall1_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall2_collider, bbox_min_wall2_collider, wall2_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall3_collider, bbox_min_wall3_collider, wall3_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall4_collider, bbox_min_wall4_collider, wall4_normal))
        {
            camera_position_c += (movement_vector * camera_delta_time) * 5.0f;
            g_PlayerIsMoving = true;
        }
    }
    // Se a tecla D está sendo pressionada (camera_movement_keys[2] = true), movimentamos a câmera para a direita.
    if (camera_movement_keys[2])
    {
        glm::vec4 aux_cam_pos = camera_position_c + (u * camera_delta_time) * 5.0f;
        glm::vec4 bbox_max_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
        glm::vec4 bbox_min_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

        if (!CheckCollisionCubeCube(bbox_max_pole1_collider, bbox_min_pole1_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&
            !CheckCollisionCubeCube(bbox_max_pole2_collider, bbox_min_pole2_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&

            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall1_collider, bbox_min_wall1_collider, wall1_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall2_collider, bbox_min_wall2_collider, wall2_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall3_collider, bbox_min_wall3_collider, wall3_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall4_collider, bbox_min_wall4_collider, wall4_normal))
        {
            camera_position_c += (u * camera_delta_time) * 5.0f;
            g_PlayerIsMoving = true;
        }
    }
    // Se a tecla A está sendo pressionada (camera_movement_keys[3] = true), movimentamos a câmera para a esquerda.
    else if (camera_movement_keys[3])
    {
        glm::vec4 aux_cam_pos = camera_position_c - (u * camera_delta_time) * 5.0f;
        glm::vec4 bbox_max_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
        glm::vec4 bbox_min_player_collider = Matrix_Translate(aux_cam_pos.x, aux_cam_pos.y, aux_cam_pos.z)
                                           * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

        if (!CheckCollisionCubeCube(bbox_max_pole1_collider, bbox_min_pole1_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&
            !CheckCollisionCubeCube(bbox_max_pole2_collider, bbox_min_pole2_collider,
                                    bbox_max_player_collider, bbox_min_player_collider) &&

            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall1_collider, bbox_min_wall1_collider, wall1_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall2_collider, bbox_min_wall2_collider, wall2_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall3_collider, bbox_min_wall3_collider, wall3_normal) &&
            !CheckCollisionCubePlane(bbox_max_player_collider, bbox_min_player_collider,
                                     bbox_max_wall4_collider, bbox_min_wall4_collider, wall4_normal))
        {
            camera_position_c -= (u * camera_delta_time) * 5.0f;
            g_PlayerIsMoving = true;
        }
    }

    if (!g_PlayerIsJumping)
    {
        camera_position_c.y = 1.80f;
    }

    camera_time_prev = camera_time_now;
    camera_position = camera_position_c;

    if (isCameraLookAt)
    {
        camera_position = glm::vec4(g_CameraDistance*x, std::max(g_CameraDistance*y, 0.5f), g_CameraDistance*z, 1.0f);

        // O view vector de uma câmera look-at é igual ao ponto look-at menos a posição atual da câmera

                             // ponto look-at (câmera vai estar sempre olhando para o player)
        camera_view_vector = glm::vec4(camera_position_c.x, camera_position_c.y-2.0f, camera_position_c.z, 1.0f) + (movement_vector * 0.15f) -
                             // posição da câmera é formada pelos pontos x,y,z definidos acima multiplicados pela distância da câmera
                             camera_position;
    }
}
