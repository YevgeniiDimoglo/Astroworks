#version 450

layout(set = 0, binding = 0) uniform UBOScene
{
    mat4 model;
    mat4 view;
    mat4 projection;
    mat4 lightMVP;
    vec4 lightDirection;
    vec4 lightColor;
    vec4 viewPos;
    vec4 timerConstants;
} uboScene;

layout(push_constant) uniform PushModel{
      mat4 model;
      vec4 baseColor;
} pushModel;

layout(location = 0) in vec3 inPosition;

layout(location = 0) out vec3 outTexCoord;

void main()
{
   gl_Position = (
         uboScene.projection * uboScene.view * pushModel.model * vec4(inPosition, 1.0)
   ).xyww;

   outTexCoord = inPosition;
}