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

vec3 CalcFresnel(float HdotV, vec3 F0)
{
    return F0 + (1.0f - F0) * pow(1.0f - HdotV, 5.0);
}

float CalcdistributuionGGX(float NdotH, float roughness)
{
    float a = roughness * roughness;
	float a2 = a * a;
    float denom = NdotH * NdotH * (a2 - 1.0f) + 1.0f;
    denom = PI * denom * denom;

	return a2 / max(denom, 0.0000001);
}

float CalcGeometryFunction(float NdotV, float NdotL, float roughness)
{
	float r = roughness + 1.0f;
    float k = (r * r) / 8.0f;
    float ggx1 = NdotV / (NdotV * (1.0f - k) + k);
    float ggx2 = NdotL / (NdotL * (1.0f - k) + k);

	return ggx1 * ggx2;
}

vec3 SpecularBRDF(float NdotV, float NdotL, float NdotH, float HdotV, vec3 fresnelF0, float roughness)
{
    float D = CalcdistributuionGGX(NdotH, roughness);
    
    float G = CalcGeometryFunction(NdotV, NdotL, roughness);
    
    vec3 F = CalcFresnel(HdotV, fresnelF0);
    
    return D * G * F / (4.0 * NdotV * NdotL);
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
    vec3 H = normalize(V + L);
    
    float NdotV = max(dot(N, V), 0.0000001);
    float NdotL = max(dot(N, L), 0.0000001);
    float HdotV = max(dot(N, V), 0.0);
    float NdotH = max(dot(N, H), 0.0);
    
    vec3 irradiance = lightColor * NdotL;
    
    irradiance *= PI;
    
    outDiffuse = DiffuseBRDF(diffuseReflectance) * irradiance;
    
    outSpecular = SpecularBRDF(NdotV, NdotL, NdotH, HdotV, F0, roughness) * irradiance;
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

vec3 getNormal()
{
	vec3 tangentNormal = texture(normalMap, inUV).xyz * 2.0 - 1.0;

	vec3 q1 = dFdx(vertPos);
	vec3 q2 = dFdy(vertPos);
	vec2 st1 = dFdx(inUV);
	vec2 st2 = dFdy(inUV);

	vec3 N = normalize(normalInterp);
	vec3 T = normalize(q1 * st2.t - q2 * st1.t);
	vec3 B = -normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);

	return normalize(TBN * tangentNormal);
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

	vec3 F0 = mix(vec3(0.04f), albedoColor.rgb, metallic);

    vec3 N = getNormal();

	vec3 V = normalize(cameraPos.xyz - vertPos.xyz);

    vec3 directAmbient = vec3(0.03) * albedoColor.rgb;
	vec3 directDiffuse = vec3(0.f);
	vec3 directSpecular = vec3(0.f);
	
    DirectBDRF(diffuseReflectance, F0, N, V, lightDirection,
                   lightColor.rgb, roughness,
                    directDiffuse, directSpecular);
	

	outColor = vec4(directAmbient + directDiffuse + directSpecular, albedoColor.a);
}