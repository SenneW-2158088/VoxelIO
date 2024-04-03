//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "AssetManager.h"

#include <iostream>

namespace fs = std::filesystem;

std::map<std::string, std::shared_ptr<Shader>> AssetManager::shaders{};

void AssetManager::initializeAssets() {
    loadShaders();
}

void AssetManager::clearAssets() {
    shaders.clear();
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