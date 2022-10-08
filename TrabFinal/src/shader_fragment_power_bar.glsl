#version 330 core

layout(location = 0) out vec4 FragColor;

in vec2 texcoords;

uniform sampler2D TextureImagePowerBar;
uniform sampler2D TextureImagePowerBarInside;

uniform float power;

float smoothstep (float edge0, float edge1, float x)
{
   if (x < edge0)
      return 0;

   if (x >= edge1)
      return 1;

   // Scale/bias into [0..1] range
   x = (x - edge0) / (edge1 - edge0);

   return x * x * (3 - 2 * x);
}

vec4 lerp(vec4 a, vec4 b, float alpha){

    return ((b - a) * alpha) + a;
}

vec3 lerp(vec3 a, vec3 b, float alpha){

    return ((b - a) * alpha) + a;
}

float lerp(float a, float b, float alpha){

    return ((b - a) * alpha) + a;
}

void main()
{
    float t = 0.2;

    float img1 = texture(TextureImagePowerBar, texcoords).r;


    float grad = texture(TextureImagePowerBar, texcoords).g;

    float img3 = texture(TextureImagePowerBar, vec2(texcoords.x, 1.0-texcoords.y)).b;

    float rim1 = smoothstep(0.7, 0.7, img1);
    float rim2 = smoothstep(0.3, 0.3, img1);
    float inside = smoothstep(0.9, 0.9, img1);
    float rim = rim2 - rim1;

    img3 = smoothstep(1.05-power, 1.05-power, img3);

    vec3 outlineColor = vec3(1.0, 1.0, 0.0);
    vec3 insideColor = texture(TextureImagePowerBarInside, vec2(grad,0.0)).rgb;
    //insideColor = texture(TextureImagePowerBarInside, texcoords).rgb;

    FragColor = vec4(lerp(insideColor, outlineColor, rim), rim + inside * img3);
}
