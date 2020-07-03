#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif

struct VertexInput
{
    vec4 position;
};

struct FragmentInput
{
    vec4 position;
};

layout(binding = 0, std140) uniform MatrixBuffer
{
    layout(row_major) mat4 worldMatrix;
    layout(row_major) mat4 viewMatrix;
    layout(row_major) mat4 projectionMatrix;
} _40;

layout(location = 0) in vec4 input_position;

FragmentInput _main(VertexInput _input)
{
    FragmentInput _output;
    _output.position = _input.position;
    return _output;
}

void main()
{
    VertexInput _input;
    _input.position = input_position;
    VertexInput param = _input;
    gl_Position = _main(param).position;
}

