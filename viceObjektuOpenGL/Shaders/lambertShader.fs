#version 400

in vec4 worldPos ;
in vec3 worldNor ;

out vec4 frag_color;

//uniform vec3 lightPos;
//uniform vec3 lightColor;

void main(void)
{
    vec3 lightPos = vec3(0.0, 0.0, 0.0);
    vec3 lightColor = vec3 (1.0, 1.0, 1.0);

    vec3 lightDir = normalize(lightPos - vec3(worldPos));
    
    vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);

    vec3 norm = normalize(worldNor);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = vec4(diff * lightColor, 1.0);

    frag_color = (ambient + diffuse) * objectColor;
}