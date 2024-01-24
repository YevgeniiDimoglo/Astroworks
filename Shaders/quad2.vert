#version 450

out gl_PerVertex
{
	vec4 gl_Position;
};

const vec2 kVertices[4] = vec2[]
(
 vec2(-1.0,  1.0),
 vec2(-1.0, -1.0),
 vec2( 1.0,  1.0),
 vec2( 1.0, -1.0)
 );

layout (location = 0) out vec2 outUV;

void main() 
{
	gl_Position = vec4(kVertices[gl_VertexIndex], 1.0, 1.0);
    outUV = gl_Position.xy / 2.0 + 0.5;
}