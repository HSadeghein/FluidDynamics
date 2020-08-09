#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif
layout(location = 0) in vec3 input_position;
layout(location = 1) in vec3 input_normal;
layout(location = 2) in vec3 input_tangent;
layout(location = 3) in vec2 input_uv;
layout(location = 4) in mat4 World;

out vec2 uv;
out vec3 worldPos;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform bool isInstancing;

void main()
{
    mat4 WVP;
    if(isInstancing)
    {
        WVP = projection * view * World;
    }
    else
    {
        WVP = projection * view * model;
    }
    gl_Position = WVP * vec4(input_position, 1.0);
    worldPos = isInstancing ? vec3(World * vec4(input_position, 1)) : vec3(model * vec4(input_position, 1));
    uv = input_uv;
    normal = isInstancing ? mat3(transpose(inverse(World))) * input_normal : mat3(transpose(inverse(model))) * input_normal;
}

