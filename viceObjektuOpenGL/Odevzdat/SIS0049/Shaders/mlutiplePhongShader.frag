// Author: SIS0049 - Oliver Siskan
#version 400

// Inputs from vertex shader
in vec4 worldPos;
in vec3 worldNor;
in vec2 uvc;

// Output color
out vec4 fragColor;

uniform vec3 viewPos; // Camera position in world space
uniform sampler2D textureUnitID;
uniform bool hasTexture = false;


struct Material {
    float ambient;
    float diffuse;
    float specular;
    float shininess;
    vec3 color;
};

struct Light {
    int type;          // 0 = point light, 1 = directional light, 2 = spot light
    float angle;       // For spotlights: angle in radians defining the cone
    vec3 direction;    // For directional and spotlights: light direction (normalized)
    vec3 position;     // For point lights and spotlights: light position
    vec3 color;        // Light color
    float intensity;   // Light intensity
    float constant;    // Constant attenuation
    float linear;      // Linear attenuation
    float quadratic;   // Quadratic attenuation
};


uniform Light lights[32];
uniform Light cameraLight; // Flashlight
uniform int numLights;    // number of lights in the scene
uniform Material material;

// Function to calculate light contribution
vec3 calculateLight(Light light, vec3 norm, vec3 viewDir, vec3 fragPos) {
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);
    float attenuation = 0.0;

    vec3 lightDir;
    if (light.type == 0) { // Point light
        vec3 toLight = light.position - fragPos;
        float distance = length(toLight);
        lightDir = normalize(toLight);
        attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    } else if (light.type == 1) { // Directional light
        lightDir = normalize(-light.direction);
        attenuation = 1.0;
    } else if (light.type == 2) { // Spotlight
        vec3 toLight = light.position - fragPos;
        float distance = length(toLight);
        lightDir = normalize(toLight);
        float dotLF = dot(lightDir, normalize(-light.direction)); // angle from light to fragment
        float alpha = cos(light.angle); 

        if (dotLF > alpha) {
            float intensity = (dotLF - alpha)/(1-alpha);
            attenuation = intensity;
        } 
    }

    // Ambient component
    ambient = material.ambient * light.color * light.intensity * attenuation;

    // Diffuse component
    float diff = max(dot(norm, lightDir), 0.0);
    diffuse = diff * material.diffuse * light.color * light.intensity * attenuation;

    // Specular component
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    specular = spec * material.specular * light.color * light.intensity * attenuation;

    return ambient + diffuse + specular;
}

void main(void) {
    vec3 norm = normalize(worldNor);
    vec3 viewDir = normalize(viewPos - worldPos.xyz);

    vec3 finalColor = vec3(0.0);

    // Accumulate light contributions
    for (int i = 0; i < numLights; ++i) {
        finalColor += calculateLight(lights[i], norm, viewDir, worldPos.xyz);
    }

    finalColor *= material.color;
    
    if (hasTexture) {
        finalColor *= texture(textureUnitID, uvc).rgb;
    }

    fragColor = vec4(finalColor, 1.0);
}

