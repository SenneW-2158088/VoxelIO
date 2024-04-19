# VoxelIO

A simple voxel engine written in C++ and OpenGl.

## Shaders

### Textures

To add a texture to the shader, just call the `texture->apply(&shader)` method. Inside the shader the texture can be accessed with the `uniform sampler2D Texture`.

### Materials

The engine supports multiple types of material. To add a material to a shader just call the `material->apply(&shader)` method.

**Colored material**
To use the colored material, the following struct is required inside the shader

```c
  struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
```

**Textured material**
To use the textured material, the following struct is required inside the shader

```c
  struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
```

> Note: When using textured materials, the material is required to be used on each draw call! `material->use()`.
