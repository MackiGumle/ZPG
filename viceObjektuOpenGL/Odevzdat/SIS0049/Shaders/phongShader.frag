// Author: SIS0049 - Oliver Siskan
#version 400

in vec4 worldPos ;
in vec3 worldNor ;

out vec4 fragColor ;

//uniform vec3 lightPos; 
uniform vec3 viewPos; 
//uniform vec3 lightColor;
//uniform vec3 objectColor;

void main ( void )
{
    vec3 lightPos = vec3 (0.0 ,0.0 ,0.0);
    vec3 lightColor = vec3 (1.0 ,1.0 ,1.0);
    vec3 objectColor = vec3 (0.385 ,0.647 ,0.812);
    //vec3 viewPos = vec3 (0.0 ,0.0 ,0.0);

    // ambient
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    // diffuse
    vec3 norm = normalize(worldNor);
    vec3 lightDir = normalize(lightPos - worldPos.xyz);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - worldPos.xyz);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0);
}