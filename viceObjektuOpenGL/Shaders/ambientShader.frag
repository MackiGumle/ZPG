# version 400

void main()
{
    float ambientStrength = 0.1;
    vec3 lightColor = vec3(1,1,0.3)
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient;
    FragColor = vec4(result, 1.0);
}