#version 450

layout(binding = 0) uniform UBOScene
{
    mat4 model;
    mat4 view;
    mat4 projection;
    vec4 lightDirection;
    vec4 lightColor;
    vec4 viewPos;
    vec4 timerConstants;
} uboScene;

layout(push_constant) uniform PushModel{
      mat4 model;
      vec4 baseColor;
      vec4 timer;
} primitive;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inTangent;

layout(location = 0) out vec3 outNormal;
layout(location = 1) out vec2 outUV;
layout(location = 2) out vec3 outVertPos;
layout(location = 3) out vec4 outTangent;

layout(location = 4) out vec3 outLightDirection;
layout(location = 5) out vec4 outLightColor;
layout(location = 6) out vec4 outBaseColor;

layout(location = 7) out vec4 outCameraPos;
layout(location = 8) out vec4 outTimerConstants;

void main() 
{
    outNormal = inNormal;
    outBaseColor = primitive.baseColor;
    outUV = inUV;
    outTangent = inTangent;
    gl_Position = uboScene.projection * uboScene.view * primitive.model * vec4(inPos, 1.0);
    
    vec4 vertPos4 = primitive.model * vec4(inPos, 1.0);
    outVertPos = vertPos4.xyz / vertPos4.w;
    
    outLightDirection = vec3(uboScene.lightDirection);
    outLightColor = uboScene.lightColor;

    outNormal = mat3(primitive.model) * inNormal;

    outCameraPos = uboScene.viewPos;
    outTimerConstants = primitive.timer;
}