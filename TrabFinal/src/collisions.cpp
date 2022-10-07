#include "collisions.h"

// Variáveis para a colisão das paredes
glm::vec4 walls_normal = crossproduct(glm::vec4(1.0f,0.0f,1.0f,1.0f)-glm::vec4(-1.0f,0.0f,1.0f,1.0f),
                                      glm::vec4(1.0f,0.0f,-1.0f,1.0f)-glm::vec4(-1.0f,0.0f,1.0f,1.0f));
glm::vec4 bbox_max_wall1_collider;
glm::vec4 bbox_min_wall1_collider;
glm::vec4 wall1_normal;
glm::vec4 bbox_max_wall2_collider;
glm::vec4 bbox_min_wall2_collider;
glm::vec4 wall2_normal;
glm::vec4 bbox_max_wall3_collider;
glm::vec4 bbox_min_wall3_collider;
glm::vec4 wall3_normal;
glm::vec4 bbox_max_wall4_collider;
glm::vec4 bbox_min_wall4_collider;
glm::vec4 wall4_normal;

// Variáveis para colisão dos postes das hoops da quadra
glm::vec4 bbox_max_pole1_collider;
glm::vec4 bbox_min_pole1_collider;
glm::vec4 bbox_max_pole2_collider;
glm::vec4 bbox_min_pole2_collider;

// Variáveis para colisão das tabelas
glm::vec4 bbox_max_backboard1_collider;
glm::vec4 bbox_min_backboard1_collider;
glm::vec4 bbox_max_backboard2_collider;
glm::vec4 bbox_min_backboard2_collider;

// Variáveis para colisão dos aros
glm::vec4 rim_1_collider_center = glm::vec4(0.0f,3.08f,12.57f,1.0f);
glm::vec4 rim_2_collider_center = glm::vec4(0.0f,3.08f,-12.57f,1.0f);
GLfloat rim_colliders_radius = 0.1f;

// Variáveis para colisão dos aros do caso de quando o player erra o arremesso
glm::vec4 bbox_max_missrim1_collider;
glm::vec4 bbox_min_missrim1_collider;
glm::vec4 bbox_max_missrim2_collider;
glm::vec4 bbox_min_missrim2_collider;

// Vetor super hardcodado que a bola deve seguir caso colida com a tabela ou o aro
glm::vec4 collision_ball_handling_vector = glm::vec4(0.0f,0.0f,0.0f,0.0f);

// Variáveis para saber se objetos estão colidindo (para mudar a cor do debug)
bool g_Wall1Colliding = false, g_Wall2Colliding = false, g_Wall3Colliding = false, g_Wall4Colliding = false;
bool g_Pole1Colliding = false, g_Pole2Colliding = false;
bool g_Backboard1Colliding = false, g_Backboard2Colliding = false;
bool g_RimColliding = false;
bool g_MissRim1Colliding = false, g_MissRim2Colliding = false;

// Função que detecta colisão entre duas esferas
bool CheckCollisionSphereSphere(glm::vec4 center_sphere1, GLfloat radius_sphere1,
                                glm::vec4 center_sphere2, GLfloat radius_sphere2)
{
    float distance_centers = sqrt(pow((center_sphere1.x - center_sphere2.x),2) +
                                  pow((center_sphere1.y - center_sphere2.y),2) +
                                  pow((center_sphere1.z - center_sphere2.z),2));

    return (distance_centers < (radius_sphere1 + radius_sphere2));
}

// Função que detecta colisão entre esfera e ponto
bool CheckCollisionSpherePoint(glm::vec4 center_sphere, GLfloat radius_sphere, glm::vec4 point)
{
    float distance_center_point = sqrt(pow((center_sphere.x - point.x),2) +
                                       pow((center_sphere.y - point.y),2) +
                                       pow((center_sphere.z - point.z),2));

    return (distance_center_point <= radius_sphere);
}

// Função que detecta colisão entre dois cubos
bool CheckCollisionCubeCube(glm::vec4 bbox_max_cube1, glm::vec4 bbox_min_cube1,
                            glm::vec4 bbox_max_cube2, glm::vec4 bbox_min_cube2)
{
    return(bbox_max_cube1.x > bbox_min_cube2.x &&
           bbox_min_cube1.x < bbox_max_cube2.x &&
           bbox_max_cube1.y > bbox_min_cube2.y &&
           bbox_min_cube1.y < bbox_max_cube2.y &&
           bbox_max_cube1.z > bbox_min_cube2.z &&
           bbox_min_cube1.z < bbox_max_cube2.z);
}

// Função que detecta colisão entre um cubo e um plano
bool CheckCollisionCubePlane(glm::vec4 bbox_max_cube, glm::vec4 bbox_min_cube,
                             glm::vec4 bbox_max_plane, glm::vec4 bbox_min_plane, glm::vec4 n)
{
    /*glm::vec4 c = (bbox_max_cube + bbox_min_cube) / 2.0f;
    glm::vec4 e = bbox_max_cube - c;

    float r = e.x*abs(n.x) + e.y*abs(n.y) + e.z*abs(n.z);

    glm::vec4 c_plane = (bbox_max_plane + bbox_min_plane) / 2.0f;
    float s = sqrt(pow(c_plane.x - c.x, 2) + pow(c_plane.y - c.y, 2) + pow(c_plane.z - c.z, 2));

    return abs(s) <= r;*/

    glm::vec4 c = (bbox_max_plane + bbox_min_plane) / 2.0f;

    glm::vec4 v1 = glm::vec4(bbox_min_cube.x, bbox_min_cube.y, bbox_min_cube.z, 1.0f);
    glm::vec4 v2 = glm::vec4(bbox_max_cube.x, bbox_min_cube.y, bbox_min_cube.z, 1.0f);
    glm::vec4 v3 = glm::vec4(bbox_min_cube.x, bbox_max_cube.y, bbox_min_cube.z, 1.0f);
    glm::vec4 v4 = glm::vec4(bbox_min_cube.x, bbox_min_cube.y, bbox_max_cube.z, 1.0f);
    glm::vec4 v5 = glm::vec4(bbox_max_cube.x, bbox_max_cube.y, bbox_max_cube.z, 1.0f);
    glm::vec4 v6 = glm::vec4(bbox_min_cube.x, bbox_max_cube.y, bbox_max_cube.z, 1.0f);
    glm::vec4 v7 = glm::vec4(bbox_max_cube.x, bbox_min_cube.y, bbox_max_cube.z, 1.0f);
    glm::vec4 v8 = glm::vec4(bbox_max_cube.x, bbox_max_cube.y, bbox_min_cube.z, 1.0f);

    if ((dotproduct(n, (v1-c)) > 0 && dotproduct(n, (v2-c)) > 0 &&
         dotproduct(n, (v3-c)) > 0 && dotproduct(n, (v4-c)) > 0 &&
         dotproduct(n, (v5-c)) > 0 && dotproduct(n, (v6-c)) > 0 &&
         dotproduct(n, (v7-c)) > 0 && dotproduct(n, (v8-c)) > 0) ||

        (dotproduct(n, (v1-c)) < 0 && dotproduct(n, (v2-c)) < 0 &&
         dotproduct(n, (v3-c)) < 0 && dotproduct(n, (v4-c)) < 0 &&
         dotproduct(n, (v5-c)) < 0 && dotproduct(n, (v6-c)) < 0 &&
         dotproduct(n, (v7-c)) < 0 && dotproduct(n, (v8-c)) < 0))
        return false;

    return true;
}

// Função que detecta colisão entre uma esfera e um cubo
bool CheckCollisionSphereCube(glm::vec4 center_sphere, GLfloat radius_sphere,
                              glm::vec4 bbox_max_cube, glm::vec4 bbox_min_cube)
{
    // Find closest point in AABB to center of sphere
    GLfloat square_dist = 0.0f;
    glm::vec4 aux_collision_vector = collision_ball_handling_vector;

    if (center_sphere.x < bbox_min_cube.x)
    {
        aux_collision_vector.x = -1.0f;
        square_dist += (bbox_min_cube.x-center_sphere.x)*(bbox_min_cube.x-center_sphere.x);
    }
    else if (center_sphere.x > bbox_max_cube.x)
    {
        aux_collision_vector.x = 1.0f;
        square_dist += (center_sphere.x-bbox_max_cube.x)*(center_sphere.x-bbox_max_cube.x);
    }

    if (center_sphere.y < bbox_min_cube.y)
    {
        aux_collision_vector.y = -1.0f;
        square_dist += (bbox_min_cube.y-center_sphere.y)*(bbox_min_cube.y-center_sphere.y);
    }
    else if (center_sphere.y > bbox_max_cube.y)
    {
        aux_collision_vector.y = 1.0f;
        square_dist += (center_sphere.y-bbox_max_cube.y)*(center_sphere.y-bbox_max_cube.y);
    }

    if (center_sphere.z < bbox_min_cube.z)
    {
        aux_collision_vector.z = -1.0f;
        square_dist += (bbox_min_cube.z-center_sphere.z)*(bbox_min_cube.z-center_sphere.z);
    }
    else if (center_sphere.z > bbox_max_cube.z)
    {
        aux_collision_vector.z = 1.0f;
        square_dist += (center_sphere.z-bbox_max_cube.z)*(center_sphere.z-bbox_max_cube.z);
    }

    // If this closest point in AABB is smaller than radius, there is a collision
    if (square_dist <= radius_sphere*radius_sphere)
    {
        collision_ball_handling_vector = aux_collision_vector;
        return true;
    }

    return false;
}

// Função para setar os valores do vetor de colisão
void SetCollisionVector(glm::vec4 c, glm::vec4 prev_c)
{
    if (c.x-prev_c.x > 0.0001f) collision_ball_handling_vector.x = 1.0f;
    else if (c.x-prev_c.x < -0.0001f) collision_ball_handling_vector.x = -1.0f;
    else collision_ball_handling_vector.x = 0.0f;

    if (c.y-prev_c.y > 0.0001f) collision_ball_handling_vector.y = 1.0f;
    else if (c.y-prev_c.y < -0.0001f) collision_ball_handling_vector.y = -1.0f;
    else collision_ball_handling_vector.y = 0.0f;

    if (c.z-prev_c.z > 0.0001f) collision_ball_handling_vector.z = 1.0f;
    else if (c.z-prev_c.z < -0.0001f) collision_ball_handling_vector.z = -1.0f;
    else collision_ball_handling_vector.z = 0.0f;
}

// BBOX SETTERS TRANSFORM ======================================================

// Função que seta as bbox das paredes
void SetWallsBboxes(glm::vec3 bbox_plane_max, glm::vec3 bbox_plane_min)
{
    bbox_max_wall1_collider = TransformWallCollider()[0] * glm::vec4(bbox_plane_max.x, bbox_plane_max.y, bbox_plane_max.z, 1.0f);
    bbox_min_wall1_collider = TransformWallCollider()[0] * glm::vec4(bbox_plane_min.x, bbox_plane_min.y, bbox_plane_min.z, 1.0f);
    wall1_normal = TransformWallCollider()[0] * walls_normal;

    bbox_max_wall2_collider = TransformWallCollider()[1] * glm::vec4(bbox_plane_max.x, bbox_plane_max.y, bbox_plane_max.z, 1.0f);
    bbox_min_wall2_collider = TransformWallCollider()[1] * glm::vec4(bbox_plane_min.x, bbox_plane_min.y, bbox_plane_min.z, 1.0f);
    wall2_normal = TransformWallCollider()[1] * walls_normal;

    bbox_max_wall3_collider = TransformWallCollider()[2] * glm::vec4(bbox_plane_max.x, bbox_plane_max.y, bbox_plane_max.z, 1.0f);
    bbox_min_wall3_collider = TransformWallCollider()[2] * glm::vec4(bbox_plane_min.x, bbox_plane_min.y, bbox_plane_min.z, 1.0f);
    wall3_normal = TransformWallCollider()[2] * walls_normal;

    bbox_max_wall4_collider = TransformWallCollider()[3] * glm::vec4(bbox_plane_max.x, bbox_plane_max.y, bbox_plane_max.z, 1.0f);
    bbox_min_wall4_collider = TransformWallCollider()[3] * glm::vec4(bbox_plane_min.x, bbox_plane_min.y, bbox_plane_min.z, 1.0f);
    wall4_normal = TransformWallCollider()[3] * walls_normal;
}

// Função que seta as bbox dos postes das hoops da quadra
void SetPoleBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min)
{
    bbox_max_pole1_collider = TransformPoleCollider()[0] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_pole1_collider = TransformPoleCollider()[0] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

    bbox_max_pole2_collider = TransformPoleCollider()[1] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_pole2_collider = TransformPoleCollider()[1] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);
}

// Função que seta as bbox das tabelas
void SetBackboardBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min)
{
    bbox_max_backboard1_collider = TransformBackboardCollider()[0] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_backboard1_collider = TransformBackboardCollider()[0] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

    bbox_max_backboard2_collider = TransformBackboardCollider()[1] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_backboard2_collider = TransformBackboardCollider()[1] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);
}

// Função que seta as bbox do aro do caso de quando o player erra o arremesso
void SetMissRimBboxes(glm::vec3 bbox_cube_max, glm::vec3 bbox_cube_min)
{
    bbox_max_missrim1_collider = TransformMissRimCollider()[0] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_missrim1_collider = TransformMissRimCollider()[0] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);

    bbox_max_missrim2_collider = TransformMissRimCollider()[1] * glm::vec4(bbox_cube_max.x, bbox_cube_max.y, bbox_cube_max.z, 1.0f);
    bbox_min_missrim2_collider = TransformMissRimCollider()[1] * glm::vec4(bbox_cube_min.x, bbox_cube_min.y, bbox_cube_min.z, 1.0f);
}
