#version 430 core

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

struct PointLight {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    vec4 distance;
};

layout(std430, binding = 3) buffer PointLights {
    PointLight lights[];
} pl;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 view){
    vec3 lightDir = normalize(vec3(light.position) - position);  // Fixed to use light's position
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view, reflectDir), 0.0), 32.0);

    float distance = length(vec3(light.position) - position);
    float attenuation = 1.0 / (light.distance.x + light.distance.y * distance + 
                               light.distance.z* (distance * distance));    
    // combine results
    vec3 ambient  = vec3(light.ambient) * texture(material.diffuse_textures[0], TexCoord).rgb;
    vec3 diffuse  = vec3(light.diffuse) * diff * texture(material.diffuse_textures[0], TexCoord).rgb;
    vec3 specular = vec3(light.specular) * spec * texture(material.specular_textures[0], TexCoord).rgb;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);    
}



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
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    vec3 dirLightColor = calculateDirLight(norm, view);
    vec3 pointLightColor = vec3(0);

    for(int i = 0; i < pl.lights.length(); i++){
        pointLightColor += calculatePointLight(pl.lights[i], norm, FragPos, view);
    }

    vec3 color = pointLightColor + dirLightColor * vec3(0.4);


    FragColor = vec4(color, 1.0);
}
