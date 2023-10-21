#version 450

layout(location = 0) in vec3 normalInterp;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 vertPos;
layout(location = 5) in vec4 baseColor;
layout(location = 6) in vec4 timerConstants;

layout(set = 0, binding = 1) uniform sampler2D shadowMap;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    float gamma = 0.5;
    outColor = pow(texture(texSampler, fragTexCoord), vec4(gamma)) * vec4(1.0f, 1.0f, 1.0f, 1.0f);
}
