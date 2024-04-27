# VoxelIO

A simple voxel engine written in C++ and OpenGl.

## Uniforms

### Camera uniform

### Lighting uniform

For the directional lighting we use a uniform. The uniform shader struct can be used like this.

```c
layout(std140, binding = 0) uniform DirectionalLightUBO {
  bool active;
  vec3 direction;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};
```

## Shader Storage Buffers

In our engine it is possible to have a large amount of lights, but setting these for every shaders as a uniform is pretty slow. Using a uniform shader buffer is also possible but we are limited to 16kb space. Storage buffers are a bit slower but allow us to store a large amount of data on the gpu.

### Pointlight

Shader struct that defines a pointlight.

```c
struct PointLight {
    float constant;
    float linear;
    float quadratic;
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    vec4 position;
};
```

Accessing the SSBO buffer inside the shader.

```c
layout(std430) buffer PointLights {
    PointLight pointLights[];
} pointLightBuffer;
```

> Make sure u bind the buffer to the correct index using the `shader->setResourceBlockBinding()`

### Spotlight

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
To use the textured material, the following struct is required inside the shader, this struct allows multiple textures for diffuse and specular

```c
#define MAX_TEXTURES 8

struct Material {
    sampler2D diffuse_textures[MAX_TEXTURES];
    int diffuse_texture_count;
    sampler2D specular_textures[MAX_TEXTURES];
    int specular_texture_count;
    float shininess;
};
```

> Note: When using textured materials, the material is required to be used on each draw call! `material->use()`.

> Note: The max textures is set to 8 since opengl should minimally support 16 texture bindings. Thus 8 for each type of texture.
> You can adjust this to whatever you want I don't care, this is stable.

### Lighting

Just as for the camera data, it is much more efficient to store all the lighting data inside a uniform buffer. Therefore you can access all the lighting data by binding the uniform lighting buffer ([see](#lighting-uniform)).

**Dirlight**

A scene directional light is configured and is defined by the following shader struct.

The struct is stored inside a uniform because this data is mostly accessed in every shader object and does not contain a dynamic size.

```c
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
```

**Pointlight**

Hey, don't be scared in the dark... use a pointlight. Pointlights can be accessed from the pointlight SSBO with the following shader struct.

```c
struct PointLight {
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
};
```

**Spotlight**

For the classical horror game enjoyers. This struct can be used to access a spotlight from the spotlight SSBO.

```c
struct SpotLight {
  vec3  position;

  vec3  direction;
  float cutOff;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;

  float constant;
  float linear;
  float quadratic;
}
```

# Lighting calculations

```c
vec3 lightPos = vec3(1.0, 1.0, 1.0);

vec3 norm = normalize(Normal);
vec3 view = normalize(ViewPos - FragPos);

vec3 light_color = vec3(1, 1, 1);

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
```
