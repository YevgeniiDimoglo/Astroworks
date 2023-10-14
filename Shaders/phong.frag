#version 450

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec4 inTangent;

layout(location = 4) in vec3 lightDirection;
layout(location = 5) in vec4 lightColor;
layout(location = 6) in vec4 baseColor;

layout(location = 7) in vec4 inCameraPos;
layout(location = 8) in vec4 timerConstants;

layout(set = 1, binding = 0) uniform sampler2D samplerColorMap;
layout(set = 1, binding = 1) uniform sampler2D samplerNormalMap;
layout(set = 1, binding = 2) uniform sampler2D aoMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D roughnessMap;

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

void main() 
{
    vec4 diffuseColor = texture(samplerColorMap, inUV) * baseColor;
    
    vec3 N = normalize(inNormal);
    vec3 T = normalize(inTangent.xyz);
    vec3 B = cross(inNormal, inTangent.xyz) * inTangent.w;

    if(inTangent.x == 0 && inTangent.y == 0 && inTangent.z == 0)
    {
        T = cross(inNormal, vec3(0, 1, 0));
        B = cross(inNormal, T);
    }

    mat3 TBN = mat3(T, B, N);
	vec3 normal = normalize(texture(samplerNormalMap, inUV)).xyz * 2.0 - vec3(1.0);
	N = normalize(TBN * normal);

    vec3 L = normalize(lightDirection);
    vec3 E = normalize(inCameraPos.xyz - vertPos);

    vec3 ka = {1, 1, 1};
    vec3 kd = {1, 1, 1};
    vec3 ks = {1, 1, 1};
    float shineness = 128;

    vec3 ambient = diffuseColor.rgb * 0.2f;
    vec3 directionalDiffuse = CalcHalfLambert(normal, L, vec3(lightColor), kd);
    vec3 specular = CalcPhongSpecular(normal, L, vec3(lightColor), E, shineness, ks.rgb);

    vec4 color;
    color.rgb = diffuseColor.rgb * (ambient + directionalDiffuse) + specular;
    color.a = diffuseColor.a;
    outColor = color;

}