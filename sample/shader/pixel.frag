#version 450

layout(binding = 1, std140) uniform ColorBuffers
{
    vec4 color;
} _color;

uniform sampler2D _sampler;
uniform vec3 lightDirection;
uniform vec4 lightColor;
uniform vec3 cameraPosition;
uniform float ambientStrength;
uniform float specularStrength;

layout(location = 0) in vec2 uv;
layout(location = 3) in vec3 worldPos;
layout(location = 2) in vec3 normal;

layout(location = 0) out vec4 pixel_color;

void main()
{
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightDirection);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 viewDir = normalize(cameraPosition - worldPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    
    vec4 ambient = lightColor * ambientStrength;
    vec4 diffuse = lightColor * diff;
    vec4 specular = lightColor * spec * specularStrength;
    vec4 result = _color.color * (ambient);
    pixel_color =  _color.color;
}

