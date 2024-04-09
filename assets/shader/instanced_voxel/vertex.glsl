#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;
layout (location = 3) in mat4 aModel;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec4 viewPos;
};

uniform mat4 model;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;
out vec3 ViewPos;

void main() {
    Normal = mat3(transpose(inverse(aModel))) * aNormal;
    TexCoord = aTexture;
    FragPos = vec3(aModel * vec4(aPos, 1.0));
    ViewPos = vec3(viewPos);
    gl_Position = projection * view * aModel * vec4(aPos, 1.0);
}
