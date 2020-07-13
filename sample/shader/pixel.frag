#version 450

struct FragmentInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 1, std140) uniform ColorBuffers
{
    vec4 color;
} _36;

uniform sampler2D SPIRV_Cross_CombinedshaderTexturesampleType;

layout(location = 0) in vec2 _entryPointOutput_uv;
layout(location = 0) out vec4 _entryPointOutput;

vec4 _main(FragmentInput _input)
{
    vec4 texColor = texture(SPIRV_Cross_CombinedshaderTexturesampleType, _input.uv);
    return texColor * _36.color;
}

void main()
{
    FragmentInput _input;
    _input.position = gl_FragCoord;
    _input.uv = _entryPointOutput_uv;
    FragmentInput param = _input;
    _entryPointOutput = _main(param);
}

