#version 330

in vec3 out_color;
out vec4 fragment;

void main()
{
    fragment = vec4(out_color, 1.0);
}