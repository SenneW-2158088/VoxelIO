//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_ASSETMANAGER_H
#define VOXELIO_ASSETMANAGER_H

#include "graphics/Cubemap.h"
#include "graphics/Mesh.h"
#include "graphics/Model.h"
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <graphics/Shader.h>
#include <graphics/Texture.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <filesystem>
#include <map>

#define SOURCE_DIR _SOURCE_DIR

static const std::string ASSET_PATH = std::filesystem::path(SOURCE_DIR) / "assets";
static const std::string SHADER_PATH = std::filesystem::path(ASSET_PATH) / "shader";
static const std::string TEXTURE_PATH = std::filesystem::path(ASSET_PATH) / "texture";
static const std::string CUBEMAP_PATH = std::filesystem::path(ASSET_PATH) / "cubemap";
static const std::string MODEL_PATH = std::filesystem::path(ASSET_PATH) / "model";
static const std::string SOUND_PATH= std::filesystem::path(ASSET_PATH) / "sound" / "beat.mp3";

class AssetManager {
private:
  // Assets
  static std::map<std::string, std::shared_ptr<Shader>> shaders;
  static std::map<std::string, std::shared_ptr<Texture>> textures;
  static std::map<std::string, std::shared_ptr<Cubemap>> cubemaps;
  static std::map<std::string, std::shared_ptr<graphics::Model>> models;

  // Load shaders
  static void loadShaders();
  static Shader *loadShader(const std::string &vertex,
                            const std::string &fragment);

  // Load textures
  static void loadTextures();
  static Texture *loadTexture(const std::string &filename,
                              Texture::Format format);

  // Load Cubemaps
  static void loadCubemaps();
  static Cubemap *loadCubemap(const std::string &filename);

  // Load models
  static void loadModels();
  static graphics::Model *loadModel(const std::string &filename);
  static void processModelNode(aiNode *node, const aiScene *scene,
                               std::vector<Mesh::Mesh *> &meshes,
                               std::vector<Material *> &materials, std::filesystem::path& path);
  static void processModelMesh(aiMesh *mesh, const aiScene *scene,
                               std::vector<Mesh::Mesh *> &meshes,
                               std::vector<Material *> &materials, std::filesystem::path& path);
  static Material* processModelMaterial(aiMaterial *material, const aiScene *scene, std::filesystem::path& path);

public:
  AssetManager() = default;
  static void initializeAssets();
  static void clearAssets();

  static Shader *getShader(const std::string &name);
  static Texture *getTexture(const std::string &name);
  static Cubemap *getCubemap(const std::string &name);
  static graphics::Model *getModel(const std::string &name);
};

#endif // VOXELIO_ASSETMANAGER_H
