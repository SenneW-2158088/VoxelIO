//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_ASSETMANAGER_H
#define VOXELIO_ASSETMANAGER_H

#include <graphics/Shader.h>
#include <graphics/Texture.h>
#include "graphics/Cubemap.h"
#include "graphics/model.h"

#include <filesystem>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define SOURCE_DIR _SOURCE_DIR

static const std::string ASSET_PATH   = std::filesystem::path(SOURCE_DIR) / "assets";
static const std::string SHADER_PATH  = std::filesystem::path(ASSET_PATH) / "shader";
static const std::string TEXTURE_PATH = std::filesystem::path(ASSET_PATH) / "texture";
static const std::string CUBEMAP_PATH = std::filesystem::path(ASSET_PATH) / "cubemap";
static const std::string MODEL_PATH   = std::filesystem::path(ASSET_PATH) / "model";

class AssetManager {
private:
    // Assets
    static std::map<std::string, std::shared_ptr<Shader>> shaders;
    static std::map<std::string, std::shared_ptr<Texture>> textures;
    static std::map<std::string, std::shared_ptr<Cubemap>> cubemaps;
    static std::map<std::string, std::shared_ptr<graphics::Model>> models;

    // Load shaders
    static void loadShaders();
    static Shader* loadShader(const std::string &vertex, const std::string &fragment);

    // Load textures
    static void loadTextures();
    static Texture* loadTexture(const std::string &filename, Texture::Format format);

    // Load Cubemaps
    static void loadCubemaps();
    static Cubemap* loadCubemap(const std::string &filename);

    // Load models
    static void loadModels();
    static graphics::Model *loadModel(const std::string &filename);
    static void processModelNode(aiNode *node, const aiScene *scene);
    static void processModelMesh(aiMesh *mesh, const aiScene *scene);
    static void processModelTexture(aiMesh *mesh, const aiScene *scene);
    
public:
    AssetManager() = default;
    static void initializeAssets();
    static void clearAssets();

    static Shader* getShader(const std::string &name);
    static Texture* getTexture(const std::string &name);
    static Cubemap* getCubemap(const std::string &name);
};


#endif //VOXELIO_ASSETMANAGER_H
