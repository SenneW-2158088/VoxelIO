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

#define MAX_TEXTURES 8
struct Material {
    sampler2D diffuse_textures[MAX_TEXTURES];
    int diffuse_texture_count;
    sampler2D specular_textures[MAX_TEXTURES];
    int specular_texture_count;
    float shininess;
};

uniform Material material;

vec3 calculateDirlightAmbient(vec4 color) {
    return vec3(DirLight.ambient) * vec3(color);
}

vec3 calculateDirlightDiffuse(vec3 normal, vec4 color) {
    vec3 lightDir = normalize(-vec3(DirLight.direction));
    float diff = max(dot(normal, lightDir), 0.0);
    return vec3(DirLight.diffuse) * diff * vec3(color);
}

vec3 calculateDirlightSpecular(vec3 normal, vec3 viewDir, vec4 color) {
    vec3 lightDir = normalize(-vec3(DirLight.direction));
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    return vec3(DirLight.specular) * spec * vec3(texture(material.specular_textures[0], TexCoord).rgb);
}

void main() {
    vec3 normal = normalize(Normal);
    vec3 viewDir = normalize(ViewPos - FragPos);

    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    for(int i = 0; i < material.diffuse_texture_count; i++) {
        vec4 textureColor = texture(material.diffuse_textures[i], TexCoord);
        ambient += calculateDirlightAmbient(textureColor);
        diffuse += calculateDirlightDiffuse(normal, textureColor);
    }

    for(int i = 0; i < material.specular_texture_count; i++) {
        vec4 textureColor = texture(material.specular_textures[i], TexCoord);
        specular += calculateDirlightSpecular(-normal, viewDir, textureColor);
    }

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
