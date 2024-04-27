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

vec3 calculateDirLight(vec3 normal, vec3 view){
    if(DirLight.isActive){
        // ambient
        vec3 ambient = vec3(DirLight.ambient) * texture(material.diffuse_textures[0], TexCoord).rgb;
        
        // diffuse        
        vec3 lightDir = normalize(-vec3(DirLight.direction));
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 diffuse = vec3(DirLight.diffuse) * diff * texture(material.diffuse_textures[0], TexCoord).rgb;

        // specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(view, reflectDir), 0.0), material.shininess);

        vec3 specular = vec3(DirLight.specular) * spec * texture(material.specular_textures[0], TexCoord).rgb;


        return (ambient + diffuse + specular);
    }

    return vec3(0);
}

void main(){

    vec3 normal = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    FragColor = vec4(calculateDirLight(normal, view), 1.0);
}
