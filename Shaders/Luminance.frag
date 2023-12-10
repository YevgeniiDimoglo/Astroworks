#version 450

layout (set = 0, binding = 0) uniform sampler2D samplerColor;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;

layout (location = 0) out vec4 outFragColor;

const float threshold = 0.5f;
const float intensity = 1.0f;

void main() 
{
    const vec3 luminanceValue = vec3(0.299, 0.587, 0.114);

    vec4 colorTex = texture(samplerColor, inUV);

    float luminance = dot(luminanceValue, colorTex.rgb);

    float contribution = max(0.0, luminance - threshold);

    contribution /= luminance;
    
    vec4 color = colorTex;
    color *= contribution * intensity;

    outFragColor = color;
}