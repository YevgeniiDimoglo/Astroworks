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
      vec4 timer;
	vec4 additionalValues;
} pushModel;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;
layout(location = 3) in vec4 inTangent;

layout(location = 0) out vec3 outTexCoord;

void main()
{
      outTexCoord = inPos;
	outTexCoord.xy *= -1.0;
	mat4 viewMat = mat4(mat3(uboScene.model));
	gl_Position = uboScene.projection * viewMat * vec4(inPos.xyz, 1.0);
}