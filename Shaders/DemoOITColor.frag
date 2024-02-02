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
layout(location = 9) in vec4 inTimerConstants;

layout(binding = 1) uniform sampler2D shadowMap;

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D roughnessMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D aoMap;
layout(set = 1, binding = 5) uniform sampler2D emissiveMap;
layout(set = 1, binding = 6) uniform sampler2D additionalMap;

layout(location = 0) out vec4 outColor;

void main() {

    vec2 texcoord1 = vec2(inUV.x + inTimerConstants.g * 0.01, inUV.y + inTimerConstants.g * 0.03);

    vec4 diffuseColor = texture(additionalMap, texcoord1) * baseColor;

    vec3 ambient = diffuseColor.rgb * 1.0f;

    vec3 color = (ambient) * diffuseColor.rgb; 

    // weight function
    float weight = clamp(pow(min(1.0, diffuseColor.a * 10.0) + 0.01, 3.0) * 1e8 * 
                         pow(1.0 - gl_FragCoord.z * 0.9, 3.0), 1e-2, 3e3);

    // store pixel color accumulation
    vec4 accum = vec4(color.rgb * diffuseColor.a, diffuseColor.a) * weight;
    
    outColor = accum;
}
