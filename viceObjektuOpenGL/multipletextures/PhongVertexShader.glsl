#version 450

layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 vt;

uniform mat4 modelMatrix;

out vec2 vt_out;

void main () {
	 gl_Position = modelMatrix * vec4(vp, 1.0);
	 vt_out = vt;
}
