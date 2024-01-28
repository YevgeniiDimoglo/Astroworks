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

layout(location = 0) in vec3 inNormal;
layout(location = 1) in vec2 inUV;
layout(location = 2) in vec3 inVertPos;
layout(location = 3) in vec4 inTangent;

layout(location = 4) in vec4 inBaseColor;
layout(location = 5) in vec4 inFragPosLightSpace;

layout(location = 6) in vec4 timerConstants;

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

const float Dielectric = 0.04f;
const float adjustMetalness = 0.0f;
const float adjustSmoothness = 0.0f;

struct PBRInfo
{
	float NdotL;                 
	float NdotV;                 
	float NdotH;                 
	float LdotH;                  
	float VdotH;                  
	float perceptualRoughness;    
	vec3 reflectance0;            
	vec3 reflectance90;           
	float alphaRoughness;         
	vec3 diffuseColor;            
	vec3 specularColor;          
	vec3 n;								
	vec3 v;								
};

struct IBLinfo
{
   vec3 diffuseLight;
   vec3 specularLight;
   vec3 brdf;
};

vec4 SRGBtoLINEAR(vec4 srgbIn)
{
	vec3 linOut = pow(srgbIn.xyz,vec3(2.2));

	return vec4(linOut, srgbIn.a);
}

vec3 getIBLContribution(PBRInfo pbrInputs, vec3 n, vec3 reflection)
{
	vec2 brdfSamplePoint = clamp(vec2(pbrInputs.NdotV, 1.0-pbrInputs.perceptualRoughness), vec2(0.0, 0.0), vec2(1.0, 1.0));
	vec3 brdf = texture(bdrfLUT, brdfSamplePoint).rgb;

	vec3 cm = vec3(1.0, 1.0, 1.0);

	vec3 diffuseLight = texture(samplerCubeMapIrr, n.xyz * cm).rgb;
	vec3 specularLight = texture(samplerCubeMap, reflection.xyz * cm).rgb;

	vec3 diffuse = diffuseLight * pbrInputs.diffuseColor;
	vec3 specular = specularLight * (pbrInputs.specularColor * brdf.x + brdf.y);

	return diffuse + specular;
}

vec3 diffuseBurley(PBRInfo pbrInputs)
{
	float f90 = 2.0 * pbrInputs.LdotH * pbrInputs.LdotH * pbrInputs.alphaRoughness - 0.5;

	return (pbrInputs.diffuseColor / PI) * (1.0 + f90 * pow((1.0 - pbrInputs.NdotL), 5.0)) * (1.0 + f90 * pow((1.0 - pbrInputs.NdotV), 5.0));
}

vec3 specularReflection(PBRInfo pbrInputs)
{
	return pbrInputs.reflectance0 + (pbrInputs.reflectance90 - pbrInputs.reflectance0) * pow(clamp(1.0 - pbrInputs.VdotH, 0.0, 1.0), 5.0);
}

float geometricOcclusion(PBRInfo pbrInputs)
{
	float NdotL = pbrInputs.NdotL;
	float NdotV = pbrInputs.NdotV;
	float rSqr = pbrInputs.alphaRoughness * pbrInputs.alphaRoughness;

	float attenuationL = 2.0 * NdotL / (NdotL + sqrt(rSqr + (1.0 - rSqr) * (NdotL * NdotL)));
	float attenuationV = 2.0 * NdotV / (NdotV + sqrt(rSqr + (1.0 - rSqr) * (NdotV * NdotV)));
	return attenuationL * attenuationV;
}


float microfacetDistribution(PBRInfo pbrInputs)
{
	float roughnessSq = pbrInputs.alphaRoughness * pbrInputs.alphaRoughness;
	float f = (pbrInputs.NdotH * roughnessSq - pbrInputs.NdotH) * pbrInputs.NdotH + 1.0;
	return roughnessSq / (PI * f * f);
}


vec3 calculatePBRLightContribution( inout PBRInfo pbrInputs, vec3 lightDirection, vec3 lightColor )
{
	vec3 n = pbrInputs.n;
	vec3 v = pbrInputs.v;
	vec3 l = normalize(lightDirection);	
	vec3 h = normalize(l+v);			

	float NdotV = pbrInputs.NdotV;
	float NdotL = clamp(dot(n, l), 0.001, 1.0);
	float NdotH = clamp(dot(n, h), 0.0, 1.0);
	float LdotH = clamp(dot(l, h), 0.0, 1.0);
	float VdotH = clamp(dot(v, h), 0.0, 1.0);

	pbrInputs.NdotL = NdotL;
	pbrInputs.NdotH = NdotH;
	pbrInputs.LdotH = LdotH;
	pbrInputs.VdotH = VdotH;

	vec3 F = specularReflection(pbrInputs);
	float G = geometricOcclusion(pbrInputs);
	float D = microfacetDistribution(pbrInputs);

	vec3 diffuseContrib = (1.0 - F) * diffuseBurley(pbrInputs);
	vec3 specContrib = F * G * D / (4.0 * NdotL * NdotV);
	vec3 color = NdotL * lightColor * (diffuseContrib + specContrib);

	return color;
}

mat3 cotangentFrame( vec3 N, vec3 p, vec2 uv )
{
	vec3 dp1 = dFdx( p );
	vec3 dp2 = dFdy( p );
	vec2 duv1 = dFdx( uv );
	vec2 duv2 = dFdy( uv );

	vec3 dp2perp = cross( dp2, N );
	vec3 dp1perp = cross( N, dp1 );
	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );

	float w = (dot(cross(N, T), B) < 0.0) ? -1.0 : 1.0;

	T = T * w;

	return mat3( T * invmax, B * invmax, N );
}

vec3 perturbNormal(vec3 n, vec3 v, vec3 normalSample, vec2 uv)
{
	vec3 map = normalize( 2.0 * normalSample - vec3(1.0) );
	mat3 TBN = cotangentFrame(n, v, uv);
	return normalize(TBN * map);
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
	vec4 albedoColor = texture(albedoMap, inUV) * inBaseColor;
	
    outColor = vec4(albedoColor.a, 0.f, 0.f, 0.f);
}
