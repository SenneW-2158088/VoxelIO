#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 ViewPos;

// struct Material {
//     vec3 ambient;
//     vec3 diffuse;
//     vec3 specular;
//     float shininess;
// }; 
  
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

uniform Material material;

void main(){
    vec3 lightPos = vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    vec3 light_color = vec3(.3, .6, .4);

    // diffuse
    vec3 lightDir = normalize(lightPos - FragPos);  
    float diff = max(dot(norm, lightDir), 0.0);

    // specular
    vec3 viewDir = normalize(ViewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient  = light_color * texture(material.diffuse, TexCoord).rgb;
    vec3 diffuse  = light_color * diff * vec3(texture(material.diffuse, TexCoord));  
    vec3 specular = light_color * spec * vec3(texture(material.specular, TexCoord));

    FragColor = vec4(ambient + diffuse + specular, 1.0);
}
