#version 450

layout(binding = 0) uniform UniformBufferObject
{
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 lightDirection;
    vec4 lightColor;
    vec4 cameraPosition;
} ubo;

layout(push_constant) uniform PushModel{
      mat4 model;
      vec4 baseColor;
} pushModel;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 normalInterp;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 vertPos;
layout(location = 3) out vec3 lightDirection;
layout(location = 4) out vec4 lightColor;
layout(location = 5) out vec4 baseColor;

void main() 
{
    gl_Position = ubo.proj * ubo.view * pushModel.model * vec4(inPosition, 1.0);
    vec4 vertPos4 = pushModel.model * vec4(inPosition, 1.0);
    vertPos = vec3(vertPos4) / vertPos4.w;

    lightDirection = vec3(ubo.lightDirection);
    lightColor = ubo.lightColor;

    normalInterp = inNormal;
    fragTexCoord = inTexCoord;
    baseColor = pushModel.baseColor;
}