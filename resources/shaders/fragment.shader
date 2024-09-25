#version 330

in vec3 oCol;
in vec3 oPos;
out vec4 fragment;

uniform float time;

void main()
{
    fragment = vec4(sin(time + oPos.x), cos(time), sin(time + oPos.z), 1.0);
    // fragment = vec4(oCol, 1.0);
}