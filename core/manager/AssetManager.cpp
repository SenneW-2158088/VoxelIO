//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "AssetManager.h"

#include <iostream>

namespace fs = std::filesystem;

std::map<std::string, Shader> AssetManager::shaders{};

void AssetManager::initializeAssets() {
    loadShaders();
}

void AssetManager::clearAssets() {
    shaders.clear();
}

void AssetManager::loadShaders() {
    if (fs::is_directory(SHADER_PATH)) {
        for (const auto &entry: fs::directory_iterator(SHADER_PATH)) {
            Shader shader = Shader(entry.path() / "vertex.glsl", entry.path() / "fragment.glsl");
            std::string name = entry.path().filename();
            shaders.emplace(name, shader);

            std::cout << "Loaded shader: " << name << std::endl;
        }
    }
}

Shader *AssetManager::getShader(const std::string &name) {
    return &shaders.at(name);
}