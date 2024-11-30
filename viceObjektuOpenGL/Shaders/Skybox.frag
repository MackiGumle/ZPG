#version 450


in vec3 fragmentLocalPosition;
in vec4 worldPos;


uniform samplerCube textureUnitID;
uniform bool hasTexture = false;



out vec4 frag_colour;



void main () {
	 
    // frag_colour = texture(UISky, fragmentLocalPosition);

    if(hasTexture) {
//    frag_colour = texture(textureUnitID, vec3(worldPos));
		frag_colour = texture(textureUnitID, fragmentLocalPosition);
	} else {
		frag_colour = worldPos;
		}

    //frag_colour = texture(textureUnitID, vec3(worldPos));
    //frag_colour = texture(textureUnitID, fragmentLocalPosition);
}

