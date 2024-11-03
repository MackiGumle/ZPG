#version 400
in vec4 worldPos;
in vec3 worldNor;

out vec4 frag_color;

//uniform vec3 lightPos;
//uniform vec3 lightColor;
uniform vec3 viewPos;

void main(void)
{
    vec3 lightPos = vec3(0.0, 0.0, 0.0);
    vec3 lightColor = vec3 (1.0, 1.0, 1.0);

    vec3 color = vec3(0.385, 0.647, 0.812);
    // ambient
    vec3 ambient = vec3(0.1, 0.1, 0.1);
    // diffuse
    vec3 lightDir = normalize(lightPos - vec3(worldPos));
    vec3 normal = normalize(worldNor);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(viewPos - vec3(worldPos));
    float spec = 0.0;
 
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    frag_color = vec4(ambient + diffuse + specular, 1.0);
}