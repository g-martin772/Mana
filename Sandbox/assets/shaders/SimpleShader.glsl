#type vertex
#version 450 core

layout (location = 0) in vec3 a_Pos;
layout (location = 1) in vec4 a_Color;

layout (location = 0) out vec4 v_Color;

mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
    mat4 result = mat4(1.0);
    result[0][0] = 2.0 / (right - left);
    result[1][1] = 2.0 / (top - bottom);
    result[2][2] = -2.0 / (far - near);
    result[3][0] = -(right + left) / (right - left);
    result[3][1] = -(top + bottom) / (top - bottom);
    result[3][2] = -(far + near) / (far - near);
    return result;
}

void main() {
    v_Color = a_Color;
	gl_Position = ortho(500, 500, 500, 500, -10, 10) * vec4(a_Pos, 1.0);
}

#type fragment
#version 450 core

layout (location = 0) out vec4 color;

layout (location = 0) in vec4 v_Color;

void main() {
	color = v_Color;
}

