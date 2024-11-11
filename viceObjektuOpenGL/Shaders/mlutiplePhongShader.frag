#version 400

// Inputs from vertex shader
in vec4 worldPos;
in vec3 worldNor;

// Output color
out vec4 fragColor;

// Uniforms for lighting and material properties
uniform vec3 viewPos;                             // Camera position in world space

// Material properties
uniform float ambientStrength = 0.1;  // Ambient light strength
uniform float diffuseStrength = 1.0;  // Diffuse strength
uniform float specularStrength = 0.5; // Specular strength
uniform float shininess = 32.0;       // Shininess factor for specular highlight
uniform vec3 objectColor = vec3(0.385, 0.647, 0.812); // Object color


// Define a struct to represent a light source with attenuation
struct Light {
    vec3 position;
    vec3 color;
    float intensity;
    float constant;    // Constant attenuation factor
    float linear;      // Linear attenuation factor
    float quadratic;   // Quadratic attenuation factor
};

// Uniform array for lights and number of lights
uniform Light lights[10]; // Max 10 lights
uniform int numLights;    // Actual number of lights in the scene

void main(void)
{
    vec3 norm = normalize(worldNor);
    vec3 viewDir = normalize(viewPos - worldPos.xyz);

    // Initialize color components
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    // Loop over all lights
    for (int i = 0; i < numLights; ++i) {
        Light light = lights[i];

        // Calculate distance and attenuation
        float distance = length(light.position - worldPos.xyz);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

        // Ambient component
        ambient += ambientStrength * light.color * light.intensity * attenuation;

        // Diffuse component
        vec3 lightDir = normalize(light.position - worldPos.xyz);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuse += diff * diffuseStrength * light.color * light.intensity * attenuation;

        // Specular component
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        specular += specularStrength * spec * light.color * light.intensity * attenuation;
    }

    // Combine all light contributions
    vec3 result = (ambient + diffuse + specular) * objectColor;
    fragColor = vec4(result, 1.0); // Set alpha to 1 for full opacity
//    fragColor = vec4(objectColor, 1.0); // Set alpha to 1 for full opacity
}


//#version 400
//
//const int MAX_LIGHTS = 16;
//in vec4 worldPos;
//in vec3 worldNor;
//
//out vec4 fragColor;
//
//struct PointLight {
//    vec3 color;
//    float ambientIntensity;
//    vec3 position;
//};
//
//uniform vec3 viewPos;
//uniform int numLights;
//uniform PointLight lights[MAX_LIGHTS];
//
//void main(void)
//{
//    vec3 result = vec3(0.0);
//
//    for (int i = 0; i < numLights; i++) {
//        PointLight light = lights[i];
//
//        // attenuation
//        float distance = length(worldPos.xyz - light.position);
//        float attenuation = 1.0 / (distance * distance);
//
//        // ambient
//        vec3 ambient = light.ambientIntensity * light.color;
//
//        // diffuse
//        vec3 norm = normalize(worldNor);
//        vec3 lightDir = normalize(light.position - worldPos.xyz);
//        float diff = max(dot(norm, lightDir), 0.0);
//        vec3 diffuse = diff * light.color;
//
//        // specular
//        float specularStrength = 0.5;
//        vec3 viewDir = normalize(viewPos - worldPos.xyz);
//        vec3 reflectDir = reflect(-lightDir, norm);
//        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
//        vec3 specular = specularStrength * spec * light.color;
//
//        vec3 combined = (ambient + diffuse + specular) * attenuation;
//        result += combined;
//    }
//
//    fragColor = vec4(result, 1.0);
//}
//
//
