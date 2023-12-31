#version 450

layout (set = 0, binding = 0) uniform sampler2D samplerColor;
layout (set = 0, binding = 1) uniform sampler2D bloomTexture;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;

layout (location = 0) out vec4 outFragColor;

float random (in vec2 st)
{
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))* 43758.5453123);
}

float noise(in vec2 st)
{
    vec2 i = floor(st);
    vec2 f = fract(st);
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));
    vec2 u = f * f * (3.0 - 2.0 * f);
    return mix(a, b, u.x) + (c - a)* u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

#define octaves 3
float fbm(in vec2 p)
{
    float value = 0.0;
    float freq = 1.13;
    float amp = 0.57;    
    for (int i = 0; i < octaves; i++)
    {
        value += amp * (noise((p - vec2(1.0)) * freq));
        freq *= 1.61;
        amp *= 0.47;
    }
    return value;
}

float pat(in vec2 p)
{
    float time = timer.r*0.75;
    vec2 aPos = vec2(sin(time * 0.035), sin(time * 0.05)) * 3.;
    vec2 aScale = vec2(3.25);
    float a = fbm(p * aScale + aPos);
    vec2 bPos = vec2(sin(time * 0.09), sin(time * 0.11)) * 1.2;
    vec2 bScale = vec2(0.75);
    float b = fbm((p + a) * bScale + bPos);
    vec2 cPos = vec2(-0.6, -0.5) + vec2(sin(-time * 0.01), sin(time * 0.1)) * 1.9;
    vec2 cScale = vec2(1.25);
    float c = fbm((p + b) * cScale + cPos);
    return c;
}

vec2 Shake(float maxshake, float mag)
{
    float speed = 20.0*mag;
    float shakescale = maxshake * mag;
    
    float time = timer.r*speed;			// speed of shake
    
    vec2 p1 = vec2(0.25,0.25);
    vec2 p2 = vec2(0.75,0.75);
    p1 += time;
    p2 += time;
    
    // random shake is just too violent...
    //float val1 = random(p1);
    //float val2 = random(p2);
    
    float val1 = pat(p1);
    float val2 = pat(p2);
    val1 = clamp(val1,0.0,1.0);
    val2 = clamp(val2,0.0,1.0);
    
    return vec2(val1*shakescale,val2*shakescale);
}

void main() 
{

  float maxshake = 0.05;				// max shake amount
  float mag = 0.5+sin(timer.r)*0.5;		// shake magnitude...

  vec2 shakexy = Shake(maxshake,mag) * vec2(0.f, 0.f);

  vec4 tempFragColor = texture(samplerColor, inUV + shakexy) * vec4(1.0f, 1.0f, 1.f, 1.0f);

  tempFragColor += texture(bloomTexture, inUV + shakexy) * vec4(1.0f, 1.0f, 1.f, 1.0f);

  float gamma = 1.0;
  tempFragColor.rgb = pow(tempFragColor.rgb, vec3(1.0/gamma));

  outFragColor = tempFragColor.rgba;
}