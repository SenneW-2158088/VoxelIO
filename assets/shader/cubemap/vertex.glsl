#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

layout (std140) uniform Matrices
{
    mat4 projection;
    mat4 view;
    vec4 viewPos;
};


uniform mat4 model;

out vec3 TexCoords;


void main() {
    //    TextureCoordinates = vec3(aPos.x, aPos.y, -aPos.z);
    TexCoords = aPos;

    // regular vertex position calculation
    vec4 pos = projection * mat4(mat3(view)) * vec4(aPos, 1.f);

    // set the position z & w to w -> resulting in farthest z buffer value
    gl_Position = pos.xyww;
}
