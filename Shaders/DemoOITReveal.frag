#version 450

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec4 inTangent;

layout(location = 4) in vec3 lightDirection;
layout(location = 5) in vec4 lightColor;
layout(location = 6) in vec4 baseColor;
layout(location = 7) in vec4 inFragPosLightSpace;

layout(location = 8) in vec4 inCameraPos;
layout(location = 9) in vec4 timerConstants;

layout(binding = 1) uniform sampler2D shadowMap;

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D roughnessMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D aoMap;
layout(set = 1, binding = 5) uniform sampler2D emissiveMap;

layout(location = 0) out vec4 outColor;

void main() {

    vec4 diffuseColor = texture(albedoMap, inUV) * baseColor;

    vec3 ambient = diffuseColor.rgb * 1.0f;

    vec3 color = (ambient) * diffuseColor.rgb; 

    outColor = vec4(diffuseColor.a, 0.f, 0.f, 0.f);
}
