#version 450

layout(location = 0) in vec3 normalInterp;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec4 tangent;

layout(location = 4) in vec3 lightDirection;
layout(location = 5) in vec4 lightColor;
layout(location = 6) in vec4 baseColor;

layout(location = 7) in vec4 cameraPos;
layout(location = 8) in vec4 timerConstants;

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D roughnessMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D AoMap;

layout(location = 0) out vec4 outColor;

#define PI 3.1415926535

const float Dielectric = 0.04f;
const float adjustMetalness = 0.0f;
const float adjustSmoothness = 0.0f;

vec3 DiffuseBRDF(vec3 diffuseReflectance)
{
    return diffuseReflectance / PI;
}

vec3 CalcFresnel(vec3 F0, float VdotH)
{
    return F0 + (1.0f - F0) * pow(clamp(1.0 - VdotH, 0.0, 1.0), 5.0);
}

float CalcNormalDistributionFunction(float NdotH, float roughness)
{
    float roughnessSq = roughness * roughness;
	float f = (NdotH * roughnessSq - NdotH) * NdotH + 1.0;

	return roughnessSq / (PI * f * f);
}

float CalcGeometryFunction(float NdotV, float k)
{
    return NdotV / (NdotV * (1.0 - k) + k);
}

float CalcGeometryFunction(float NdotL, float NdotV, float roughness)
{
	float r = roughness * 0.5f;

	float attenuationL = 2.0 * NdotL / (NdotL + sqrt(r * r + (1.0 - r * r) * (NdotL * NdotL)));
	float attenuationV = 2.0 * NdotV / (NdotV + sqrt(r * r + (1.0 - r * r) * (NdotV * NdotV)));

	return attenuationL * attenuationV;
}

vec3 SpecularBRDF(float NdotV, float NdotL, float NdotH, float VdotH, vec3 fresnelF0, float roughness)
{
    float D = CalcNormalDistributionFunction(NdotH, roughness);
    
    float G = CalcGeometryFunction(NdotL, NdotV, roughness);
    
    vec3 F = CalcFresnel(fresnelF0, VdotH);
    
    return F * G * D / (4.0 * NdotL * NdotV);
}

void DirectBDRF(vec3 diffuseReflectance,
                vec3 F0,
                vec3 normal,
                vec3 eyeVector,
                vec3 lightVector,
                vec3 lightColor,
                float roughness,
                out vec3 outDiffuse,
                out vec3 outSpecular)
{
    vec3 N = normal;
    vec3 L = lightVector;
    vec3 V = eyeVector;
    vec3 H = normalize(L + V);
    
    float NdotL = clamp(dot(N, L), 0.001, 1.0);
	float NdotV = clamp(abs(dot(N, V)), 0.001, 1.0);
	float NdotH = clamp(dot(N, H), 0.0, 1.0);
	float LdotH = clamp(dot(L, H), 0.0, 1.0);
	float VdotH = clamp(dot(V, H), 0.0, 1.0);
    
    vec3 irradiance = lightColor * NdotL;
    
    irradiance *= PI;
    
    outDiffuse = DiffuseBRDF(diffuseReflectance) * irradiance;
    
    outSpecular = SpecularBRDF(NdotV, NdotL, NdotH ,VdotH, F0, roughness) * irradiance;
}

vec3 EnvBRDFApprox(vec3 F0, float roughness, float NdotV)
{
    const vec4 c0 = { -1.0f, -0.0275f, -0.572f, 0.022f };
    const vec4 c1 = { 1.0f, 0.0425f, 1.04f, -0.04f };
    vec4 r = roughness * c0 + c1;
    float a004 = min(r.x * r.x, exp2(-9.28f * NdotV)) * r.x + r.y;
    vec2 AB = vec2(-1.04f, 1.04f) * a004 + r.zw;
    return F0 * AB.x + AB.y;
}

void main() 
{
	vec4 albedoColor = texture(albedoMap, inUV) * baseColor;

	float metallic = texture(roughnessMap, inUV).r;

	float roughness = texture(roughnessMap, inUV).g;

	float ambientOcclusion = texture(AoMap, inUV).r;

	metallic = clamp(metallic + adjustMetalness, 0.0, 1.0);
	roughness = clamp(roughness + adjustSmoothness, 0.0, 1.0);

    roughness = 1.0f - roughness;

	vec3 D0 = vec3(0.02f);
	vec3 diffuseReflectance = mix(albedoColor.rgb, D0, metallic);

	vec3 F0 = vec3(0.04f);
	vec3 specularColor = mix(F0, albedoColor.rgb, metallic);
	float reflectance = max(max(specularColor.r, specularColor.g), specularColor.b);

	vec3 N = normalize(normalInterp);
    vec3 T = normalize(tangent.xyz);
    vec3 B = cross(normalInterp, tangent.xyz) * tangent.w;

    if(tangent.x == 0 && tangent.y == 0 && tangent.z == 0)
    {
        T = cross(normalInterp, vec3(0, 1, 0));
        B = cross(normalInterp, T);
    }

    mat3 TBN = mat3(T, B, N);
	vec3 normal = normalize(texture(normalMap, inUV)).xyz * 2.0 - vec3(1.0);
	N = normalize(TBN * normal);

	vec3 E = normalize(cameraPos.xyz - vertPos.xyz);

	vec3 directDiffuse = vec3(0.f);
	vec3 directSpecular = vec3(0.f);
	
    DirectBDRF(diffuseReflectance, specularColor, N, E, lightDirection,
                   lightColor.rgb, roughness,
                    directDiffuse, directSpecular);
	

	outColor = vec4(directDiffuse + directSpecular, albedoColor.a);
}