#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
out vec3 oCol;
out vec4 oPos;

uniform mat4 MVP;
uniform float time;

void main()
{
    vec4 pos = MVP * vec4(vPos, 1.0);
    gl_Position = pos;

    oCol = vCol;
    oPos = pos;
}