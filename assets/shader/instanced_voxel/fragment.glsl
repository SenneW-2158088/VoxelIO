
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

uniform sampler2D blockTexture;
uniform bool highlighted;

vec3 calculateDirLight(vec3 normal, vec3 view){
    if(DirLight.isActive){
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
    vec3 color = calculateDirLight(norm, view);
    if(highlighted){
        color = color * vec3(0.2, 0.2, 0.2);
    }
    FragColor = vec4(color, 1.0);
    // FragColor = pointLightBuffer.pointLights[0].ambient;
}
