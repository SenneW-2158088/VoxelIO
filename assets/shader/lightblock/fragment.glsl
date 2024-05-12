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
  
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

void main(){

    vec3 normal = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    // FragColor = vec4(material.ambient, 1.0);
    FragColor = vec4(1.0);
}
