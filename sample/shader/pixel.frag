#version 450

layout(binding = 1, std140) uniform ColorBuffers
{
    vec4 color;
} _color;

uniform sampler2D _sampler;

layout(location = 0) in vec2 uv;
layout(location = 0) out vec4 pixel_color;

void main()
{
    vec4 texColor = texture(_sampler, uv);
    pixel_color = texColor * _color.color;
}

