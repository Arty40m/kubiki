#version 330

layout(location = 0) in vec3 vPos;
layout(location = 1) in vec3 vCol;
out vec3 oCol;
out vec3 oPos;

uniform mat4 MVP;
uniform float time;

void main()
{
    // gl_Position = MVP * vec4(vPos, 1.0);
    float y = vPos.y + sin(time + vPos.x * vPos.z);
    gl_Position = MVP * vec4(vPos.x, y, vPos.z, 1.0);

    oCol = vCol;
    oPos = vPos;
}