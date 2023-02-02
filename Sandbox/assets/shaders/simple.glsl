#type vertex
#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec4 inColor;

layout(location = 0) out vec4 fragColor;

void main() {
    gl_Position = vec4(inPos, 1.0);
    fragColor = vec4(inColor);
}

#type fragment
#version 450

layout(location = 0) in vec4 fragColor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor);
}

