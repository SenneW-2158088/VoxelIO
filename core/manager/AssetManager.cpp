//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "AssetManager.h"
#include "graphics/Texture.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

std::map<std::string, std::shared_ptr<Shader>> AssetManager::shaders{};
std::map<std::string, std::shared_ptr<Shader>> AssetManager::textures{};

void AssetManager::initializeAssets() {
    loadShaders();
    loadTextures();
}

void AssetManager::clearAssets() {
    shaders.clear();
    textures.clear();
}

void AssetManager::loadShaders() {
    if (fs::is_directory(SHADER_PATH)) {
        for (const auto &entry: fs::directory_iterator(SHADER_PATH)) {
            std::string name = entry.path().filename();
            Shader* shader = loadShader(entry.path() / "vertex.glsl", entry.path() / "fragment.glsl");
            shaders.emplace(name, std::shared_ptr<Shader>(shader));
            std::cout << "Loaded shader: " << name << std::endl;
        }
    }
}

Shader *AssetManager::loadShader(const std::string &vertex, const std::string &fragment) {
    return new Shader(vertex, fragment);
}
Shader *AssetManager::getShader(const std::string &name) {
    return shaders.at(name).get();
}

void AssetManager::loadTextures() {
    if(fs::is_directory(TEXTURE_PATH)){
        for (const auto& entry : fs::directory_iterator(TEXTURE_PATH)) {
            std::string name = entry.path().filename();

            std::cout << "Loading " << entry.path().string() << std::endl;

            Texture* texture = loadTexture(entry.path().string());
            textures.emplace(name, std::shared_ptr<Texture>(texture));
            std::cout << "Loaded Texture: " << name << std::endl;
        }
    }
}

Texture* AssetManager::loadTexture(const std::string &filename){
    return new Texture(filename);
}

Texture* AssetManager::getTexture(const std::string &name){
    return textures.at(name).get();
}
