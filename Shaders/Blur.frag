#version 450

layout (set = 0, binding = 0) uniform sampler2D samplerColor;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;

layout (location = 0) out vec4 outFragColor;

#define KERNEL_MAX 16
const int kernelSize = 9;

void main() 
{
    // Gaussian kernel values (for a standard deviation of 1.5)
    const float kernel[kernelSize] = float[](0.06136, 0.24477, 0.38774, 0.24477, 0.06136,
                                             0.24477, 0.38774, 0.24477, 0.06136);

    vec2 texelSize = 1.0 / vec2(1920, 1080);

    // Horizontal blur
    vec3 result = vec3(0.0);
    for (int i = -kernelSize/2; i <= kernelSize/2; ++i)
    {
        vec2 offset = vec2(float(i), 0.0) * texelSize;
        result += texture(samplerColor, inUV + offset).rgb * kernel[i + kernelSize/2];
    }

    // Vertical blur
    vec3 finalColor = vec3(0.0);
    for (int i = -kernelSize/2; i <= kernelSize/2; ++i)
    {
        vec2 offset = vec2(0.0, float(i)) * texelSize;
        finalColor += result * kernel[i + kernelSize/2];
    }

    outFragColor = vec4(finalColor, 1.0);
}