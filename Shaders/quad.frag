#version 450

layout (set = 0, binding = 0) uniform sampler2D samplerColor;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;

layout (location = 0) out vec4 outFragColor;

void main() 
{
    vec4 tempFragColor = texture(samplerColor, inUV);
    
    outFragColor = tempFragColor.rgba;
}