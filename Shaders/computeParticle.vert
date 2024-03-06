#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec3 fragColor;

const float size = 5.0f;
const float scale = 1.0f;

void main() {

    gl_PointSize = size;
    gl_Position = vec4(inPosition.xy, 0.0, 1.0);
    fragColor = inColor.rgb;
}