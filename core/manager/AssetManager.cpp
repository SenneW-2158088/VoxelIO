//
// Created by Senne Wertelaers on 01/04/2024.
//

#include "AssetManager.h"
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


void AssetManager::loadCubemaps(){
    if(fs::is_directory(CUBEMAP_PATH)){
            for (const auto& entry : fs::directory_iterator(CUBEMAP_PATH)) {
            std::string name = entry.path().filename();
            std::cout << "Loading " << entry.path().string() << std::endl;

            Cubemap* cubemap = loadCubemap(entry.path().string());
            cubemaps.emplace(name, std::shared_ptr<Cubemap>(cubemap));

            std::cout << "Loaded Cubemap: " << name << std::endl;
        }
    }
}

Cubemap *AssetManager::loadCubemap(const std::string &filename){
    static std::string faces[6] = {"right", "left", "top", "bottom", "back", "front"};
    static std::string extensions[2] = {"png", "jpg"}; // supported extensions

    std::vector<std::string> facePaths{};

    if(fs::is_directory(filename)) {
        for(const auto &face : faces){
            std::cout << "Trying to find: " << filename << "/" << face << std::endl;
            for(const auto &ext : extensions){
                const std::string filePath = std::filesystem::path(filename) / (face + "." + ext);
                if(fs::exists(filePath)){
                    facePaths.push_back(filePath);
                    std::cout << "Found cubemap: " << filePath << std::endl;
                    break;
                }
            }
        }
    }

    for(auto f : facePaths){
        std::cout << f << std::endl;
    }

    // Load the cubemap
    return new Cubemap(facePaths);

}

Cubemap *AssetManager::getCubemap(const std::string &name){
    return cubemaps.at(name).get();
}


