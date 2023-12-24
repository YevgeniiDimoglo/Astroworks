#version 450

layout (set = 0, binding = 0) uniform sampler2D samplerColor;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;
layout (location = 2) in vec4 additionalValues;

layout (location = 0) out vec4 outFragColor;

void main() 
{
    const vec3 luminanceValue = vec3(0.299, 0.587, 0.114);

    vec4 colorTex = texture(samplerColor, inUV);

    float luminance = dot(luminanceValue, colorTex.rgb);

    float contribution = max(0.0, luminance - clamp(additionalValues.z, 0.0f, 1.0f));

    contribution /= luminance;
    
    vec4 color = colorTex;
    color *= contribution * clamp(additionalValues.w, 0.0f, 10.0f);

    outFragColor = color;
}