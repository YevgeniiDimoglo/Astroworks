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

vec3 CalcHalfLambert(vec3 normal, vec3 lightVector, vec3 lightColor, vec3 kd)
{
    float d = clamp(dot(-lightVector, normal) * 0.5 + 0.5, 0, 1);
    return lightColor * d * kd;
}

vec3 CalcLambertDiffuse(vec3 normal, vec3 lightVector, vec3 lightColor, vec3 kd)
{
    float d = max(dot(-lightVector, normal), 0);
    return lightColor * d * kd;
}

vec3 CalcPhongSpecular(vec3 normal, vec3 lightVector, vec3 lightColor, vec3 eyeVector, float shininess, vec3 ks)
{
    vec3 R = reflect(lightVector, normal);
    float d = max(0, (dot(R, eyeVector)));
    d = pow(d, shininess);
    return lightColor * d * ks;
}

float ShadowCalculation(vec4 fragPosLightSpace)
{
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    float currentDepth = projCoords.z;
    float bias = 0.0005;
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;  

    return shadow;
}  

void main() 
{
    vec2 texcoord1 = vec2(inUV.x + timerConstants.g * 0.1, inUV.y + timerConstants.g * 0.3);
    vec2 texcoord2 = vec2(inUV.x + timerConstants.g * 0.4, inUV.y + timerConstants.g * 0.2);
    
    vec4 diffuseColor;
    {
        vec4 DC1 = texture(albedoMap, texcoord1);
        vec4 DC2 = texture(albedoMap, texcoord2);
        
        diffuseColor = ((DC1 + DC2) * 0.5f) * baseColor;
    }

    vec3 N;
    {     
        vec3 N1 = texture(normalMap, texcoord1).xyz * 2 - 1;
        vec3 N2 = texture(normalMap, texcoord2).xyz * 2 - 1;
        N = N1 + N2;
        N = normalize(N);
    }

    vec3 L = normalize(lightDirection);
    vec3 E = normalize(inCameraPos.xyz - vertPos);

    vec3 ka = {1, 1, 1};
    vec3 kd = {1, 1, 1};
    vec3 ks = {1, 1, 1};
    float shineness = 128;

    vec3 ambient = diffuseColor.rgb * 0.2f;
    vec3 directionalDiffuse = CalcHalfLambert(N, L, vec3(lightColor), kd);
    vec3 specular = CalcPhongSpecular(N, L, vec3(lightColor), E, shineness, ks.rgb);
    float shadow = ShadowCalculation(inFragPosLightSpace);  

    vec3 lighting = (ambient + (1.0 - shadow * 0.1) * (directionalDiffuse + specular)) * diffuseColor.rgb; 

    outColor = vec4(lighting, 1.0f);
}