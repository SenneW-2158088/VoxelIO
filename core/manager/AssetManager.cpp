//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "AssetManager.h"
#include "graphics/Material.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"
#include "graphics/model.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::map<std::string, std::shared_ptr<Shader>> AssetManager::shaders{};
std::map<std::string, std::shared_ptr<Texture>> AssetManager::textures{};
std::map<std::string, std::shared_ptr<Cubemap>> AssetManager::cubemaps{};

void AssetManager::initializeAssets() {
  loadShaders();
  loadTextures();
  loadCubemaps();
}

void AssetManager::clearAssets() {
  shaders.clear();
  textures.clear();
  cubemaps.clear();
}

void AssetManager::loadShaders() {
  if (fs::is_directory(SHADER_PATH)) {
    for (const auto &entry : fs::directory_iterator(SHADER_PATH)) {
      std::string name = entry.path().filename();
      Shader *shader = loadShader(entry.path() / "vertex.glsl",
                                  entry.path() / "fragment.glsl");
      shaders.emplace(name, std::shared_ptr<Shader>(shader));
      std::cout << "Loaded shader: " << name << std::endl;
    }
  }
}

Shader *AssetManager::loadShader(const std::string &vertex,
                                 const std::string &fragment) {
  return new Shader(vertex, fragment);
}
Shader *AssetManager::getShader(const std::string &name) {
  return shaders.at(name).get();
}

void AssetManager::loadTextures() {
  if (fs::is_directory(TEXTURE_PATH)) {
    for (const auto &entry : fs::directory_iterator(TEXTURE_PATH)) {
      std::string name = entry.path().filename();

      std::cout << "Loading " << entry.path().string() << std::endl;

      Texture::Format format = (entry.path().extension().string() == ".png" ) ? Texture::Format::PNG: Texture::Format::JPG;

      std::cout << "Detected format " << entry.path().extension().string() << std::endl;

      Texture *texture = loadTexture(entry.path().string(), format);
      textures.emplace(name, std::shared_ptr<Texture>(texture));
      std::cout << "Loaded Texture: " << name << std::endl;
    }
  }
}

Texture *AssetManager::loadTexture(const std::string &filename, Texture::Format format) {
  return new Texture(filename, format);
}

Texture *AssetManager::getTexture(const std::string &name) {
  return textures.at(name).get();
}

void AssetManager::loadCubemaps() {
  if (fs::is_directory(CUBEMAP_PATH)) {
    for (const auto &entry : fs::directory_iterator(CUBEMAP_PATH)) {
      std::string name = entry.path().filename();
      std::cout << "Loading " << entry.path().string() << std::endl;

      Cubemap *cubemap = loadCubemap(entry.path().string());
      cubemaps.emplace(name, std::shared_ptr<Cubemap>(cubemap));

      std::cout << "Loaded Cubemap: " << name << std::endl;
    }
  }
}

Cubemap *AssetManager::loadCubemap(const std::string &filename) {
  static std::string faces[6] = {"right",  "left",  "top",
                                 "bottom", "front", "back"};
  static std::string extensions[2] = {"png", "jpg"}; // supported extensions

  std::vector<std::string> facePaths{};

  if (fs::is_directory(filename)) {
    for (const auto &face : faces) {
      for (const auto &ext : extensions) {
        const std::string filePath =
            std::filesystem::path(filename) / (face + "." + ext);
        if (fs::exists(filePath)) {
          facePaths.push_back(filePath);
          break;
        }
      }
    }
  }

  // Load the cubemap
  return new Cubemap(facePaths);
}

Cubemap *AssetManager::getCubemap(const std::string &name) {
  return cubemaps.at(name).get();
}


void AssetManager::loadModels(){
  // list all the models
}


graphics::Model *AssetManager::loadModel(const std::string &filename) {
  Assimp::Importer import;
  const aiScene *scene = import.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);	
	
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
  {
      std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
      return nullptr;
  }

  std::vector<Mesh::Mesh> meshes;
  std::vector<Material> materials;

  // AssetManager::processModelNode();
}


void AssetManager::processModelNode(aiNode *node, const aiScene *scene){
  // iterate over each node an process each mesh
  
  // process all the node's meshes (if any)
    // for(unsigned int i = 0; i < node->mNumMeshes; i++)
    // {
    //     aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
    //     meshes.push_back(processMesh(mesh, scene));			
    // }
    // // then do the same for each of its children
    // for(unsigned int i = 0; i < node->mNumChildren; i++)
    // {
    //     processNode(node->mChildren[i], scene);
    // }
}

void AssetManager::processModelMesh(aiMesh *mesh, const aiScene *scene){
  // process the mesh
  // find a way to to correctly set the texture id's
    // vector<Vertex> vertices;
    // vector<unsigned int> indices;
    // vector<Texture> textures;

    // for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    // {
    //     Vertex vertex;
    //     // process vertex positions, normals and texture coordinates
    //     [...]
    //     vertices.push_back(vertex);
    // }
    // // process indices
    // for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    // {
    //     aiFace face = mesh->mFaces[i];
    //     for(unsigned int j = 0; j < face.mNumIndices; j++)
    //         indices.push_back(face.mIndices[j]);
    // } 
    // // process material
    // if(mesh->mMaterialIndex >= 0)
    // {
    //     [...]
    // }

    // return Mesh(vertices, indices, textures);
  
}

void AssetManager::processModelTexture(aiMesh *mesh, const aiScene *scene){
  // process the textures
}

