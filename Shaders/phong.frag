#version 450

layout(location = 0) in vec3 normalInterp;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec3 lightDirection;
layout(location = 4) in vec4 lightColor;
layout(location = 5) in vec4 baseColor;

layout(set = 1, binding = 0) uniform sampler2D texSampler;

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
    return d * lightColor * ks;
}

void main() 
{
    vec4 diffuseColor = texture(texSampler, fragTexCoord) * baseColor;
    
    vec3 N = normalize(normalInterp);
    vec3 L = normalize(lightDirection);
    vec3 E = {0, 0, 0};

    vec3 ka = {1, 1, 1};
    vec3 kd = {1, 1, 1};
    vec3 ks = {1, 1, 1};
    float shineness = 128;

    vec3 ambient = ka * vec3(0.2, 0.2, 0.2);
    vec3 directionalDiffuse = CalcHalfLambert(N, L, vec3(lightColor), kd);

    vec4 color = vec4(ambient, diffuseColor.a);
    color.rgb = diffuseColor.rgb * (color.rgb + directionalDiffuse);

    outColor = color;

}