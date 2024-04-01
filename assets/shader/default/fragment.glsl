#version 330 core

layout (location = 0) out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec3 ViewPos;

void main(){
    vec3 norm = normalize(Normal);
    vec3 view = normalize(ViewPos - FragPos);

    FragColor = vec4(0.5, 0.0, 0.0, 1.0);
}


