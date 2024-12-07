#version 450

in vec3 fragmentLocalPosition;
in vec4 worldPos;

uniform samplerCube textureUnitID;
uniform bool hasTexture = false;

out vec4 frag_colour;

void main () {
    if(hasTexture) {
		frag_colour = texture(textureUnitID, fragmentLocalPosition);
	} else {
		frag_colour = worldPos;
	}
}

