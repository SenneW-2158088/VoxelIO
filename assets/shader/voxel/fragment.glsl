#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 ViewPos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
  

uniform sampler2D blockTexture;
uniform Material material;

vec3 calculateLighting(vec3 lightPos, vec3 viewPos, vec3 fragPos, vec3 normal){

    // ambient lighting
    float as = 0.4;
    vec3 ambient = as * vec3(1.0, 1.0, 1.0); // light color

    vec3 lightDir = normalize(lightPos - fragPos);  

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 0.3, 1.0);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // specular lighting
    float ss = 0.9;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32) * ss;


    return ambient + diffuse + spec;
}

void main(){
    vec3 lightPos = vec3(1.0, 1.0, 1.0);
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    FragColor = vec4(calculateLighting(lightPos, ViewPos, FragPos, norm), 1.0) * texture(blockTexture, TexCoord);
}
