#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif

struct VertexInput
{
    vec3 position;
    vec3 normal;
    vec3 tangent;
    vec2 uv;
};

struct FragmentInput
{
    vec4 position;
    vec2 uv;
};

layout(binding = 0, std140) uniform MatrixBuffer
{
    layout(row_major) mat4 worldMatrix;
    layout(row_major) mat4 viewMatrix;
    layout(row_major) mat4 projectionMatrix;
} _71;

layout(location = 0) in vec3 input_position;
layout(location = 1) in vec3 input_normal;
layout(location = 2) in vec3 input_tangent;
layout(location = 3) in vec2 input_uv;
out vec2 _entryPointOutput_uv;

FragmentInput _main(VertexInput _input)
{
    FragmentInput _output;
    _output.position = vec4(_input.position, 1.0);
    _output.uv = _input.uv;
    return _output;
}

void main()
{
    VertexInput _input;
    _input.position = input_position;
    _input.normal = input_normal;
    _input.tangent = input_tangent;
    _input.uv = input_uv;
    VertexInput param = _input;
    FragmentInput flattenTemp = _main(param);
    gl_Position = flattenTemp.position;
    _entryPointOutput_uv = flattenTemp.uv;
}

