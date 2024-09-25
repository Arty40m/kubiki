#version 330

layout(location = 0) in vec3 vPos;
out vec3 out_pos;

uniform mat4 MVP;

void main()
{
    out_pos = vPos;
    gl_Position = MVP * vec4(vPos, 1.0);
}