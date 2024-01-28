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
layout(binding = 2) uniform samplerCube samplerCubeMap;
layout(binding = 3) uniform samplerCube samplerCubeMapIrr;
layout(binding = 4) uniform sampler2D bdrfLUT;

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D roughnessMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D aoMap;
layout(set = 1, binding = 5) uniform sampler2D emissiveMap;

layout(location = 0) out vec4 outColor;

#define PI 3.1415926535

#define ShadowBias 0.001
#define ShadowColor vec3(0.2, 0.2, 0.2)

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

float PCF(int kernelSize, vec2 shadowCoord, float depth)
{
	float size = 1.0 / float( textureSize(shadowMap, 0 ).x );
	float shadow = 0.0;
	int range = kernelSize / 2;
	for ( int v=-range; v<=range; v++ ) for ( int u=-range; u<=range; u++ )
		shadow += (depth >= texture( shadowMap, shadowCoord + size * vec2(u, v) ).r) ? 1.0 : 0.0;
	return shadow / (kernelSize * kernelSize);
}

float shadowFactor(vec4 shadowCoord)
{
	vec4 shadowCoords4 = shadowCoord / shadowCoord.w;

	if (shadowCoords4.z > -1.0 && shadowCoords4.z < 1.0)
	{
		float depthBias = -0.0055;
		float shadowSample = PCF( 13, shadowCoords4.xy, shadowCoords4.z + depthBias );
		return mix(1.0, 0.3, shadowSample);
	}

	return 1.0; 
}

void main() 
{
    vec2 texcoord1 = vec2(inUV.x + timerConstants.g * 0.001, inUV.y + timerConstants.g * 0.003);
    vec2 texcoord2 = vec2(inUV.x + timerConstants.g * 0.004, inUV.y + timerConstants.g * 0.002);
    
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

    vec3 ambient = diffuseColor.rgb * 0.1f;
    vec3 directionalDiffuse = CalcHalfLambert(N, L, vec3(lightColor), kd);
    vec3 specular = CalcPhongSpecular(N, L, vec3(lightColor), E, shineness, ks.rgb);

    vec3 reflectDir = reflect(normalize(vertPos), N);

    vec3 reflectionColor = texture(samplerCubeMap, reflectDir).xyz;

    vec3 lighting = (ambient + directionalDiffuse + reflectionColor + specular) * diffuseColor.rgb; 

    outColor = vec4(shadowFactor(inFragPosLightSpace) * lighting, diffuseColor.a);
}