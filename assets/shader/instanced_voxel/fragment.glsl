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

struct PointLight {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
    float constant;
    float linear;
    float quadratic;
};

struct TestData{
    vec3 ambient;
    vec3 diffuse;
    vec3 position;
};

// layout(std430, binding = 3) buffer PointLights {
//     PointLight lights[];
// } pl;

layout(std430, binding = 3) buffer PointLights {
    float data[];
} pl;

// layout(std430, binding = 3) buffer pls {
//     float test;
// };

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

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 position, vec3 view){
    vec3 lightDir = normalize(-vec3(DirLight.direction));
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(view, reflectDir), 0.0), 32.0);

    float distance    = length(vec3(light.position) - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = vec3(light.ambient)  * texture(blockTexture, TexCoord).rgb;
    vec3 diffuse  = vec3(light.diffuse)  * diff * texture(blockTexture, TexCoord).rgb;
    vec3 specular = vec3(light.specular) * spec * texture(blockTexture, TexCoord).rgb;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);    
}

void main(){
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    vec3 dirLightColor = calculateDirLight(norm, view);
    vec3 pointLightColor = vec3(0);

    // for(int i = 0; i < pl.lights.length(); i++){
    //     // pointLightColor += calculatePointLight(lights[i], norm, FragPos, view);
    //     pointLightColor += vec3(pl.lights[i].ambient);
    // }

    vec3 color = dirLightColor + pointLightColor;

    // if(test == 1.0){
    if (pl.data.length() > 0) {
        FragColor = vec4(0.0, pl.data[1], 0.0, 1.0); // Display the first element as red intensity
    } else {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Yellow if length is 0
    }

    if(highlighted){
        color = dirLightColor * vec3(0.2, 0.2, 0.2) ;
    }

    // FragColor = vec4(color, 1.0);
}
