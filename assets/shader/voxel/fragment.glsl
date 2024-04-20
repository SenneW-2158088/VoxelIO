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
    int isActive;
} DirLight;

uniform sampler2D blockTexture;

vec3 calculateLighting(vec3 lightPos, vec3 viewPos, vec3 fragPos, vec3 normal){

    // ambient lighting
    float as = 1;
    vec3 ambient = as * vec3(1.0, 1.0, 1.0); // light color

    vec3 lightDir = normalize(lightPos - fragPos);  

    // Diffuse lighting
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(.8, .2, .8);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    // specular lighting
    float ss = 0.9;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32) * ss;


    return ambient + diffuse + spec;
}

vec3 calculateDirLight(vec3 normal, vec3 view){
    if(DirLight.isActive != 0){
        // ambient
        vec3 ambient = vec3(DirLight.ambient) * texture(blockTexture, TexCoord).rgb;
        
        // diffuse        
        vec3 lightDir = normalize(-vec3(DirLight.direction));
        float diff = max(dot(normal, lightDir), 0.0);

        vec3 diffuse = vec3(DirLight.diffuse) * diff * texture(blockTexture, TexCoord).rgb;

        // specular
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(view, reflectDir), 0.0), 32.0);

        vec3 specular = vec3(DirLight.specular) * spec * texture(blockTexture, TexCoord).rgb;


        return (ambient + diffuse + specular);
    }

    return vec3(0);
}

void main(){
    vec3 lightPos = vec3(2.0, 2.0, 2.0);
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    // FragColor = vec4(calculateLighting(lightPos, ViewPos, FragPos, norm), 1.0) * texture(blockTexture, TexCoord);
    FragColor = vec4(calculateDirLight(norm, view), 1.0);
}
