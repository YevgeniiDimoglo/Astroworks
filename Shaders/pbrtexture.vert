#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 lightDirection;
    vec4 lightColor;
    vec4 cameraPosition;
    vec4 timerConstants;
} ubo;

layout(push_constant) uniform PushModel{
      mat4 model;
      vec4 baseColor;
      vec4 timer;
} pushModel;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 inTangent;

layout(location = 0) out vec3 normalInterp;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 vertPos;
layout(location = 3) out vec4 tangent;

layout(location = 4) out vec3 lightDirection;
layout(location = 5) out vec4 lightColor;
layout(location = 6) out vec4 baseColor;

layout(location = 7) out vec4 cameraPos;

layout(location = 8) out vec4 timerConstants;

void main() 
{
    gl_Position = ubo.proj * ubo.view * pushModel.model * vec4(inPosition, 1.0);
    vec4 vertPos4 = pushModel.model * vec4(inPosition, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;

    lightDirection = vec3(ubo.lightDirection);
    lightColor = ubo.lightColor;

    normalInterp = inNormal;
    tangent = vec4(mat3(ubo.model) * inTangent.xyz, inTangent.w);

    fragTexCoord = inTexCoord;
    baseColor = pushModel.baseColor;

    cameraPos = ubo.cameraPosition;

    timerConstants = pushModel.timer;
}