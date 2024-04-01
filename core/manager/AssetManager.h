//
// Created by Senne Wertelaers on 01/04/2024.
//

#ifndef VOXELIO_ASSETMANAGER_H
#define VOXELIO_ASSETMANAGER_H

#include <map>
#include <graphics/Shader.h>
#include <filesystem>

#define SOURCE_DIR _SOURCE_DIR

static const std::string ASSET_PATH = std::filesystem::path(SOURCE_DIR) / "assets";
static const std::string SHADER_PATH = std::filesystem::path(ASSET_PATH) / "shader";

class AssetManager {
private:
    static std::map<std::string, Shader> shaders;

    // Load shaders
    static void loadShaders();
public:
    AssetManager() = default;
    static void initializeAssets();
    static void clearAssets();

    static Shader* getShader(const std::string &name);
};


#endif //VOXELIO_ASSETMANAGER_H
