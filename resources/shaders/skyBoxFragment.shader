#version 330

in vec3 out_pos;
out vec4 fragment;

// uniform float boxSize;
uniform vec3 dir; 

void main()
{
    vec2 st = gl_FragCoord.xy/vec2(1024, 768);
   
    float d = dot(dir, vec3(0.0f, 1.0f, 0.0f));
    d = 0.5*d + 0.5;
    d = d + 0.5*(st.y - 0.5);
   
    vec4 skyColor = vec4(0.34f*d, 0.715f*d, 0.85f*d, 1.0f);

    fragment = skyColor;
}