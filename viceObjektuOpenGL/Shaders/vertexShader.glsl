#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vc;
out vec3 color;
void main () {
    gl_Position = vec4 (vp.x, vp.y, vp.z, 1.0);
    color = vc;
};