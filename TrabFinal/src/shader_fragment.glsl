#version 330 core

// Atributos de fragmentos recebidos como entrada ("in") pelo Fragment Shader.
// Neste exemplo, este atributo foi gerado pelo rasterizador como a
// interpolação da posição global e a normal de cada vértice, definidas em
// "shader_vertex.glsl" e "main.cpp".
in vec4 position_world;
in vec4 normal;

// Posição do vértice atual no sistema de coordenadas local do modelo.
in vec4 position_model;

// Coordenadas de textura obtidas do arquivo OBJ (se existirem!)
in vec2 texcoords;

// Matrizes computadas no código C++ e enviadas para a GPU
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Identificador que define qual objeto está sendo desenhado no momento
#define SPHERE              0
#define BUNNY               1
#define PLANE               2
#define COURT               3
#define BACKBOARD           4
#define SKYBOX              5
#define GLASS               6
#define CUBE                7
#define HAND                8
#define HOOP                9
#define POWERBAR           10
#define SCOREBOARD         11
#define TIME               12
#define POINTS             13
#define PERIOD             14
#define BBOX               15
#define BBOX_COLLIDE       16

uniform int object_id;

// Parâmetros da axis-aligned bounding box (AABB) do modelo
uniform vec4 bbox_min;
uniform vec4 bbox_max;

// Variáveis para acesso das imagens de textura
uniform sampler2D TextureImageBall;
uniform sampler2D TextureImageHoop;
uniform sampler2D TextureImageScoreboard;
uniform sampler2D TextureImageCourtWarriors;
uniform sampler2D TextureImageSkyboxWarriors;
uniform sampler2D TextureImageCourtBeach;
uniform sampler2D TextureImageSkyboxBeach;
uniform sampler2D TextureImageBallBeach;

in vec4 color_ball_gourad_shading;

uniform bool CourtIsInTheBeach;
uniform bool GouradShading;

// O valor de saída ("out") de um Fragment Shader é a cor final do fragmento.
out vec4 color;

// Constantes
#define M_PI   3.14159265358979323846
#define M_PI_2 1.57079632679489661923

void main()
{
    // Obtemos a posição da câmera utilizando a inversa da matriz que define o
    // sistema de coordenadas da câmera.
    vec4 origin = vec4(0.0, 0.0, 0.0, 2.0);
    vec4 camera_position = inverse(view) * origin;

    // O fragmento atual é coberto por um ponto que percente à superfície de um
    // dos objetos virtuais da cena. Este ponto, p, possui uma posição no
    // sistema de coordenadas global (World coordinates). Esta posição é obtida
    // através da interpolação, feita pelo rasterizador, da posição de cada
    // vértice.
    vec4 p = position_world;

    // Normal do fragmento atual, interpolada pelo rasterizador a partir das
    // normais de cada vértice.
    vec4 n = normalize(normal);

    // Vetor que define o sentido da fonte de luz em relação ao ponto atual.
    vec4 l = normalize(vec4(3.0,30.0,0.0,0.0));

    // Vetor que define o sentido da câmera em relação ao ponto atual.
    vec4 v = normalize(camera_position - p);

    // Vetor que define o sentido da reflexão especular ideal.
    vec4 r = -l + 2*n*(dot(n,l));

    // Coordenadas de textura U e V
    float U = 0.0;
    float V = 0.0;

    // Parâmetros que definem as propriedades espectrais da superfície
    vec3 Kd; // Refletância difusa
    vec3 Ks; // Refletância especular
    vec3 Ka; // Refletância ambiente
    float q; // Expoente especular para o modelo de iluminação de Phong

    if ( object_id == SPHERE )
    {
        vec4 bbox_center = (bbox_min + bbox_max) / 2.0;

        float radius = 5.0f;

        vec4 p_line = bbox_center + radius*((position_model - bbox_center)/length(position_model - bbox_center));

        vec4 p_vector = p_line - bbox_center;

        float theta = atan(p_vector.x, p_vector.z);
        float phi = asin(p_vector.y/radius);

        U = (theta + M_PI)/(2*M_PI);
        V = (phi + M_PI_2)/M_PI;

        // Propriedades espectrais da esfera
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.01,0.01,0.01);
        q = 1.0;
    }
    else if ( object_id == COURT)
    {
        float minx = bbox_min.x;
        float maxx = bbox_max.x;

        float miny = bbox_min.y;
        float maxy = bbox_max.y;

        float minz = bbox_min.z;
        float maxz = bbox_max.z;

        U = (position_model.z - minz)/(maxz - minz);
        V = (position_model.x - minx)/(maxx - minx);

        // Propriedades espectrais da quadra
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.01,0.01,0.01);
        q = 1.0;
    }
    else if ( object_id == SKYBOX )
    {
        // Coordenadas de textura da skybox, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Propriedades espectrais da skybox
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(1.0,1.0,1.0);
        Ka = vec3(1.0,1.0,1.0);
        q = 1.0;
    }
    else if (object_id == CUBE)
    {
        // Propriedades espectrais da quadra
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(0.01,0.01,0.01);
        q = 1.0;
    }
    else if (object_id == HOOP)
    {
        // Coordenadas de textura do plano, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Propriedades espectrais das tabelas
        Kd = vec3(0.690196, 0.690196, 0.690196);
        Ks = vec3(0.009961,0.009961,0.009961);
        Ka = vec3(1.0,1.0,1.0);
        q = 96.078431;
    }
    else
    {
        // Coordenadas de textura do scoreboard, obtidas do arquivo OBJ.
        U = texcoords.x;
        V = texcoords.y;

        // Propriedades espectrais do scoreboard
        Kd = vec3(1.0,1.0,1.0);
        Ks = vec3(0.0,0.0,0.0);
        Ka = vec3(1.0,1.0,1.0);
        q = 1.0;
    }

    // Obtemos a refletância difusa a partir da leitura da imagem TextureImage0
    vec3 Kd0 = texture(TextureImageBall, vec2(U,V)).rgb;
    vec3 Kd1 = texture(TextureImageHoop, vec2(U,V)).rgb;
    vec3 Kd2 = texture(TextureImageScoreboard, vec2(U,V)).rgb;
    vec3 Kd3 = texture(TextureImageCourtWarriors, vec2(U,V)).rgb;
    vec3 Kd4 = texture(TextureImageSkyboxWarriors, vec2(U,V)).rgb;
    vec3 Kd5 = texture(TextureImageCourtBeach, vec2(U,V)).rgb;
    vec3 Kd6 = texture(TextureImageSkyboxBeach, vec2(U,V)).rgb;
    vec3 Kd7 = texture(TextureImageBallBeach, vec2(U,V)).rgb;

    // Termo difuso utilizando a lei dos cossenos de Lambert
    vec3 lambert_diffuse_term = Kd*max(0,dot(n,l));

    // Termo ambiente
    vec3 ambient_term = Ka;

    // Half-vector (meio do caminho entre v e l)
    vec4 h = normalize(l + v);
    // Termo especular utilizando o modelo de iluminação de Blinn-Phong
    vec3 blinn_phong_specular_term  = Ks*pow(max(0,dot(n,h)),q);

    color.rgb = lambert_diffuse_term + ambient_term + blinn_phong_specular_term;
    if (object_id == SPHERE)
    {
        if (GouradShading)
            color.rgb = color_ball_gourad_shading.rgb;
        else if (CourtIsInTheBeach)
            color.rgb *= Kd7;
        else
            color.rgb *= Kd0;
    }
    else if (object_id == COURT)
    {
        if (CourtIsInTheBeach)
            color.rgb *= Kd5;
        else
            color.rgb *= Kd3;
    }
    else if (object_id == CUBE)
        color.rgb *= vec3(0.5f, 0.5f, 0.5f);
    else if (object_id == SKYBOX)
    {
        if (CourtIsInTheBeach)
            color.rgb *= Kd6;
        else
            color.rgb *= Kd4;
    }
    else if (object_id == HOOP)
        color.rgb *= Kd1;
    else if (object_id == SCOREBOARD)
        color.rgb *= Kd2;
    else if (object_id == TIME)
        color.rgb *= vec3(1.0f, 0.0f, 0.0f);
    else if (object_id == POINTS)
        color.rgb *= vec3(0.965f, 0.635f, 0.094f);
    else if (object_id == PERIOD)
        color.rgb *= vec3(0.435f, 0.700f, 0.15f);
    else if (object_id == BBOX)
        color.rgb *= vec3(1.0f, 0.5f, 0.5f);
    else
        color.rgb *= vec3(1.0f, 0.0f, 0.0f);

    // NOTE: Se você quiser fazer o rendering de objetos transparentes, é
    // necessário:
    // 1) Habilitar a operação de "blending" de OpenGL logo antes de realizar o
    //    desenho dos objetos transparentes, com os comandos abaixo no código C++:
    //      glEnable(GL_BLEND);
    //      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 2) Realizar o desenho de todos objetos transparentes *após* ter desenhado
    //    todos os objetos opacos; e
    // 3) Realizar o desenho de objetos transparentes ordenados de acordo com
    //    suas distâncias para a câmera (desenhando primeiro objetos
    //    transparentes que estão mais longe da câmera).
    // Alpha default = 1 = 100% opaco = 0% transparente
    if (object_id != GLASS)
        color.a = 1;
    else
        color.a = 0.1;

    // Cor final com correção gamma, considerando monitor sRGB.
    // Veja https://en.wikipedia.org/w/index.php?title=Gamma_correction&oldid=751281772#Windows.2C_Mac.2C_sRGB_and_TV.2Fvideo_standard_gammas
    color.rgb = pow(color.rgb, vec3(1.0,1.0,1.0)/2.2);
}
