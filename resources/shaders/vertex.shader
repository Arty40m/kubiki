#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
out vec3 out_color;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(vPos, 1.0);
    out_color = vCol;
}