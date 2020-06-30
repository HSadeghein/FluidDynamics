#version 330
#ifdef GL_ARB_shading_language_420pack
#extension GL_ARB_shading_language_420pack : require
#endif

layout(location = 0) in vec4 pos;

void main()
{
    gl_Position = pos;
}

