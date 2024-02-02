#version 450

layout (set = 2, binding = 0) uniform sampler2D AccumSampler;
layout (set = 2, binding = 1) uniform sampler2D ColorSampler;

layout (location = 0) in vec2 inUV;

layout (location = 0) out vec4 outColor;

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

void main() {
    ivec2 coords = ivec2(gl_FragCoord.xy);
	
	// fragment revealage
	float revealage = texelFetch(ColorSampler, coords, 0).r;

	// save the blending and color texture fetch cost if there is not a transparent fragment
	if (revealage.r == 1.0f) 
	  	discard;
 
	// fragment color
	vec4 accumulation = texelFetch(AccumSampler, coords, 0);
	
	// suppress overflow
	if (isinf(max3(abs(accumulation.rgb)))) 
		accumulation.rgb = vec3(accumulation.a);

	// prevent floating point precision bug
	vec3 average_color = accumulation.rgb / max(accumulation.a, EPSILON);

	// blend pixels
	outColor = vec4(average_color, 1.0f - revealage.r);
}
