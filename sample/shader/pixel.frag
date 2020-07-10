#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif

struct FragmentInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 0, std140) uniform ColorBuffers
{
    vec4 color;
} _53;

uniform sampler2D SPIRV_Cross_CombinedshaderTexturesampleType;

in vec2 _entryPointOutput_uv;
layout(location = 0) out vec4 _entryPointOutput;

vec4 _main(FragmentInput _input)
{
    vec4 texColor = texture(SPIRV_Cross_CombinedshaderTexturesampleType, _input.uv);
    return texColor;
}

void main()
{
    FragmentInput _input;
    _input.position = gl_FragCoord;
    _input.uv = _entryPointOutput_uv;
    FragmentInput param = _input;
    _entryPointOutput = _main(param);
}

