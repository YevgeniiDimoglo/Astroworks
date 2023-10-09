#version 450

layout(location = 0) in vec3 normalInterp;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec4 tangent;

layout(location = 4) in vec3 lightDirection;
layout(location = 5) in vec4 lightColor;
layout(location = 6) in vec4 baseColor;

layout(location = 7) in vec4 cameraPos;
layout(location = 8) in vec4 timerConstants;

layout(set = 1, binding = 0) uniform sampler2D albedoMap;
layout(set = 1, binding = 1) uniform sampler2D normalMap;
layout(set = 1, binding = 2) uniform sampler2D aoMap;
layout(set = 1, binding = 3) uniform sampler2D metallicMap;
layout(set = 1, binding = 4) uniform sampler2D roughnessMap;

layout(location = 0) out vec4 outColor;

#define PI 3.1415926535
#define ALBEDO pow(texture(albedoMap, fragTexCoord).rgb, vec3(2.2))

// Phong
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
    return d * lightColor * ks;
}

// PBR
vec3 Uncharted2Tonemap(vec3 x)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float E = 0.02;
	float F = 0.30;
	return ((x*(A*x+C*B)+D*E)/(x*(A*x+B)+D*F))-E/F;
}

float D_GGX(float dotNH, float roughness)
{
	float alpha = roughness * roughness;
	float alpha2 = alpha * alpha;
	float denom = dotNH * dotNH * (alpha2 - 1.0) + 1.0;
	return (alpha2)/(PI * denom*denom); 
}

float G_SchlicksmithGGX(float dotNL, float dotNV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;
	float GL = dotNL / (dotNL * (1.0 - k) + k);
	float GV = dotNV / (dotNV * (1.0 - k) + k);
	return GL * GV;
}

vec3 F_Schlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 F_SchlickR(float cosTheta, vec3 F0, float roughness)
{
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}

// vec3 prefilteredReflection(vec3 R, float roughness)
// {
// 	const float MAX_REFLECTION_LOD = 9.0; // todo: param/const
// 	float lod = roughness * MAX_REFLECTION_LOD;
// 	float lodf = floor(lod);
// 	float lodc = ceil(lod);
// 	vec3 a = textureLod(prefilteredMap, R, lodf).rgb;
// 	vec3 b = textureLod(prefilteredMap, R, lodc).rgb;
// 	return mix(a, b, lod - lodf);
// }

vec3 specularContribution(vec3 L, vec3 V, vec3 N, vec3 F0, float metallic, float roughness)
{
	// Precalculate vectors and dot products	
	vec3 H = normalize (V + L);
	float dotNH = clamp(dot(N, H), 0.0, 1.0);
	float dotNV = clamp(dot(N, V), 0.0, 1.0);
	float dotNL = clamp(dot(N, L), 0.0, 1.0);

	// Light color fixed
	vec3 lightColor = vec3(1.0);

	vec3 color = vec3(0.0);

	if (dotNL > 0.0) {
		// D = Normal distribution (Distribution of the microfacets)
		float D = D_GGX(dotNH, roughness); 
		// G = Geometric shadowing term (Microfacets shadowing)
		float G = G_SchlicksmithGGX(dotNL, dotNV, roughness);
		// F = Fresnel factor (Reflectance depending on angle of incidence)
		vec3 F = F_Schlick(dotNV, F0);		
		vec3 spec = D * F * G / (4.0 * dotNL * dotNV + 0.001);		
		vec3 kD = (vec3(1.0) - F) * (1.0 - metallic);			
		color += (kD * ALBEDO / PI + spec) * dotNL;
	}

	return color;
}

vec3 calculateNormal()
{
	vec3 tangentNormal = texture(normalMap, fragTexCoord).xyz * 2.0 - 1.0;

	vec3 N = normalize(normalInterp);
	vec3 T = normalize(tangent.xyz);
	vec3 B = normalize(cross(N, T));
	mat3 TBN = mat3(T, B, N);
	return normalize(TBN * tangentNormal);
}


void main() 
{
	vec3 N = calculateNormal();

	vec3 V = normalize(cameraPos.xyz - vertPos);
	vec3 R = reflect(-V, N); 

	float metallic = texture(metallicMap, fragTexCoord).r;
	float roughness = texture(roughnessMap, fragTexCoord).r;

	vec3 F0 = vec3(0.04); 
	F0 = mix(F0, ALBEDO, metallic);

	// vec3 Lo = vec3(0.0);
	// for(int i = 0; i < uboParams.lights[i].length(); i++) {
	// 	vec3 L = normalize(uboParams.lights[i].xyz - vertPos);
	// 	Lo += specularContribution(L, V, N, F0, metallic, roughness);
	// }   
	
	// vec2 brdf = texture(samplerBRDFLUT, vec2(max(dot(N, V), 0.0), roughness)).rg;
	// vec3 reflection = prefilteredReflection(R, roughness).rgb;	
	// vec3 irradiance = texture(samplerIrradiance, N).rgb;

	// // Diffuse based on irradiance
	 vec3 diffuse = 1 * ALBEDO;	

	vec3 F = F_SchlickR(max(dot(N, V), 0.0), F0, roughness);

	// // Specular reflectance
	// vec3 specular = reflection * (F * brdf.x + brdf.y);

	// Ambient part
	vec3 kD = 1.0 - F;
	kD *= 1.0 - metallic;	  
	vec3 ambient = (kD * diffuse) * texture(aoMap, fragTexCoord).rrr;
	
	vec3 color = ambient;

	// Tone mapping
	color = Uncharted2Tonemap(color *  4.5f);
	color = color * (1.0f / Uncharted2Tonemap(vec3(11.2f)));	
	// Gamma correction
	color = pow(color, vec3(1.0f / 2.2f));

	outColor = vec4(color, 1.0);

}