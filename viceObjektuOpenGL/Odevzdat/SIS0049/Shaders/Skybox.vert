// Author: SIS0049 - Oliver Siskan
#version 450
layout(location = 0) in vec3 vp;


uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentLocalPosition;
out vec4 worldPos;


void main () {
	
	worldPos  = modelMatrix * vec4(vp, 1.0);
	 
	fragmentLocalPosition = vp;

	gl_Position = projectionMatrix * viewMatrix * worldPos;
}
