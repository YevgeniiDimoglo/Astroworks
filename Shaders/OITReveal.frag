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

float calculateShadow(vec4 shadowCoords, vec2 off)
{
    return texture(shadowMap, shadowCoords.xy + off).r;  
}

vec3 filterPCF(vec4 shadowCoords)
{
   vec2 texelSize = textureSize(shadowMap, 0);
   float scale = 1.5;
   float dx = scale * 1.0 / float(texelSize.x);
   float dy = scale * 1.0 / float(texelSize.y);

   float shadow = 0.0;
   int count = 0;
   int range = 10;

   for (int x = -range; x <= range; x++)
   {
      for (int y = -range; y <= range; y++)
      {
         shadow += calculateShadow(
               shadowCoords,
               vec2(dx * x, dy * y)
         );
         count++;
      }
   }

   return mix(vec3(0.2, 0.2, 0.2), vec3(1.f), count / (range * range));
}

vec3 CalcShadowColor()
{
    float depth = texture(shadowMap, inFragPosLightSpace.xy).r;

	return mix(vec3(0.2, 0.2, 0.2), vec3(1.f), step(inFragPosLightSpace.z - depth, 0.01));
}

void main() {
    vec4 diffuseColor = texture(albedoMap, inUV) * baseColor;
    
    vec3 N = normalize(inNormal);
    vec3 T = normalize(inTangent.xyz);
    vec3 B = cross(inNormal, inTangent.xyz) * inTangent.w;

    if(inTangent.x == 0 && inTangent.y == 0 && inTangent.z == 0)
    {
        T = cross(inNormal, vec3(0, 1, 0));
        B = cross(inNormal, T);
    }

    mat3 TBN = mat3(T, B, N);
	vec3 normal = normalize(texture(normalMap, inUV)).xyz * 2.0 - vec3(1.0);
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

    vec3 shadow = CalcShadowColor();

    directionalDiffuse *= shadow;
    specular *= shadow;

    vec3 color = (ambient + directionalDiffuse + specular ) * diffuseColor.rgb;

    outColor = vec4(color, diffuseColor.a);
}
