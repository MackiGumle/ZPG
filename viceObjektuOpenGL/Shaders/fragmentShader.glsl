#version 330
in vec3 color;
out vec4 frag_colour;
void main () {
     frag_colour = vec4 (color.x, color.y, color.z, 1.0);
};
