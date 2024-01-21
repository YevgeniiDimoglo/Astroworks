#version 450

layout (set = 2, binding = 0) uniform sampler2D AccumSampler;
layout (set = 2, binding = 1) uniform sampler2D RevelageSampler;
layout (set = 2, binding = 2) uniform sampler2D FinalTextureSampler;

layout (location = 0) in vec2 inUV;
layout (location = 1) in vec4 timer;

layout (location = 0) out vec4 outColor;

// epsilon number
const float EPSILON = 0.00001f;

// calculate floating point numbers equality accurately
bool isApproximatelyEqual(float a, float b)
{
    return abs(a - b) <= (abs(a) < abs(b) ? abs(b) : abs(a)) * EPSILON;
}

// get the max value between three values
float max3(vec3 v)
{
    return max(max(v.x, v.y), v.z);
}

void main()
{
    // fragment coordination
    ivec2 coords = ivec2(gl_FragCoord.xy);

    float revealage = texture(RevelageSampler, coords).r;

    // save the blending and color texture fetch cost if there is not a transparent fragment
    if (isApproximatelyEqual(revealage, 1.0f))
        discard;

    // fragment color
    vec4 accumulation = texture(AccumSampler, coords);

    // suppress overflow
    if (isinf(max3(abs(accumulation.rgb))))
        accumulation.rgb = vec3(accumulation.a);

    // prevent floating point precision bug
    vec3 average_color = accumulation.rgb / max(accumulation.a, EPSILON);

    // blend pixels
    outColor = vec4(average_color, 1.0f - revealage);
}
