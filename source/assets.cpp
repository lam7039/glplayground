#include "assets.hpp"
#include <filesystem>
#include <iostream>

Asset::Asset(const std::string &name, AssetType type) : name(name), type(type) {}

void Asset::bind() {}
void Asset::bind(int index) {}

AssetLoader::AssetLoader() {
    workspace = std::string(std::filesystem::current_path()) + "/../";
}

Asset *AssetLoader::loadTexture(const std::string &name, const std::string &path) {
    assets[name] = new Texture(name, workspace + path);
    return assets[name];
}

Asset *AssetLoader::loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
    assets[name] = new Shader(name, workspace + vertexPath, workspace + fragmentPath);
    return assets[name];
}

Asset *AssetLoader::find(std::string name) {
    return assets[name];
}

void AssetLoader::bind() {
    find("main")->bind();
    find("image")->bind(0);
    find("mario")->bind(1);
}

void AssetLoader::quit() {
    for (auto asset : assets) {
        if (asset.second->type == IMAGE) {
            static_cast<Texture*>(asset.second)->destroy();
        }
    }
    assets.clear();
}
