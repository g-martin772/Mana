#type vertex
#version 450

layout(location = 0) out vec3 fragColor;

vec2 positions[6] = vec2[](
    vec2(-0.5, -0.5), // links unten
    vec2(0.5, -0.5),  // rechts unten
    vec2(-0.5, 0.5),  // links oben
    vec2(0.5, 0.5),   // rechts oben
    vec2(-0.5, 0.5),  // links oben
    vec2(0.5, -0.5)   // rechts unten
);

vec3 colors[6] = vec3[](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0),
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    gl_Position = vec4(positions[gl_VertexIndex], 0.0, 1.0);
    fragColor = colors[gl_VertexIndex];
}

#type fragment
#version 450

layout(location = 0) in vec3 fragColor;

layout(location = 0) out vec4 outColor;

void main() {
    outColor = vec4(fragColor, 1.0);
}

