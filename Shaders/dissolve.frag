#version 450

layout(location = 0) in vec3 normalInterp;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 vertPos;
layout(location = 3) in vec3 lightDirection;
layout(location = 4) in vec4 lightColor;
layout(location = 5) in vec4 baseColor;
layout(location = 6) in vec4 timerConstants;

layout(set = 1, binding = 0) uniform sampler2D texSampler;
layout(set = 2, binding = 0) uniform sampler2D dissolveSampler;

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

const float N = 2.0; // grid ratio
float gridTexture( in vec2 p )
{
    // coordinates
    vec2 i = step( fract(p), vec2(1.0/N) );
    //pattern
    //return (1.0-i.x)*(1.0-i.y);   // grid (N=10)
    
    // other possible patterns are these
    //return 1.0-i.x*i.y;           // squares (N=4)
    return 1.0-i.x-i.y+2.0*i.x*i.y; // checker (N=2)
}

#define mask_tile 0.3

void main() 
{
    vec4 diffuseColor = texture(texSampler, fragTexCoord) * baseColor;

    float dissolveFactor = texture(dissolveSampler, fragTexCoord).r;
 
    vec4 clrBG = vec4(1., 1., 1., 0.); //* gridTexture(fragTexCoord.xy/vec2(5., 5.)) + 0.6;
    
    // set this to fade the alpha (0-1)
    float t = 1.0 - timerConstants.r;
    
	// set these to increase/decrease the edge width
    float edge_width_start = 0.25; // width at the start of the dissolve (alpha = 1)
    float edge_width_end = 0.05; // width at the end of the dissolve (alpha = 0)
    
    float edge_width = mix(edge_width_start, edge_width_end, smoothstep(0., 1., t)); // 
    
    // increase the alpha range by the edge width so we are not left with only glowy edges 
    float myAlpha = mix(0. - edge_width, 1., t); 

    float a = step(dissolveFactor, myAlpha);

    float edge = smoothstep(dissolveFactor - edge_width, dissolveFactor, myAlpha);

    vec4 edgeColor = vec4(1.0, 1.0, 1.0, 1.0);
    edgeColor *= edge;

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

    color += edgeColor;

    outColor = mix(color, clrBG, a);;
}