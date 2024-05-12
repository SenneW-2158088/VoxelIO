#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 ViewPos;

layout(std140) uniform DirectionalLightData {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 direction;
    bool isActive;
} DirLight;

uniform float time;

float perlin(vec2 p) {
    // Implement Perlin noise generation here
    return fract(sin(dot(p ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 calculateDirLight(vec3 normal, vec3 view){
    if(DirLight.isActive){
        // ambient
        vec3 ambient = vec3(DirLight.ambient) * vec3(0.0, 0.3, 0.7);
        
        // diffuse        
        vec3 lightDir = normalize(-vec3(DirLight.direction));
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 diffuse = vec3(DirLight.diffuse) * diff * vec3(0.0, 0.3, 0.7);

        // specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(view, reflectDir), 0.0), 32.0);

        vec3 specular = vec3(DirLight.specular) * spec * vec3(0.0, 0.3, 0.7);


        return (ambient + diffuse + specular);
    }

    return vec3(0);
}

void main() {
    vec3 lightPos = vec3(2.0, 2.0, 2.0);
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    vec3 dirLighting = calculateDirLight(norm, view);

    // Calculate wave pattern using a simple sine function
    float wave = sin(dot(FragPos.xz, vec2(1.0, 1.0)) * 0.1 + time);
    wave = wave * 0.5 + 0.5;  // Normalize wave between 0 and 1

    // Combine effects
    vec3 waterColor = vec3(0.0, 0.3, 0.7) + vec3(wave * 0.1);  // Water color affected by waves
    vec3 result = dirLighting + waterColor;
    FragColor = vec4(result, 1.0);
}
