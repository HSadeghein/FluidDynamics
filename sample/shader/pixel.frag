#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif

struct FragmentInput
{
    vec4 position;
};

in vec4 input_position;
layout(location = 0) out vec4 _entryPointOutput;

vec4 _main(FragmentInput _input)
{
    return vec4(1.0, 0.0, 0.0, 1.0);
}

void main()
{
    FragmentInput _input;
    _input.position = input_position;
    FragmentInput param = _input;
    _entryPointOutput = _main(param);
}

