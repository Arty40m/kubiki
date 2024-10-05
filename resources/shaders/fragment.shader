#version 330

in vec3 oCol;
in vec4 oPos;
out vec4 fragment;

uniform float time;

void main()
{
    float x = oPos.z / 100.0f;
    fragment = vec4(x, x, x, 1.0f);
}