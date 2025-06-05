#include "asset_manager.hpp"

std::weak_ptr<Shader> AssetManager::get_shader(const std::string& name) const {
    auto shader = shaders.find(name);
    return shader != shaders.end() ? shader->second : std::weak_ptr<Shader>();
}

std::weak_ptr<Texture> AssetManager::get_texture(const std::string& name) const {
    auto texture = textures.find(name);
    return texture != textures.end() ? texture->second : std::weak_ptr<Texture>();
}

void AssetManager::load_shader(const std::string& name, const std::string& vertex, const std::string& fragment) {
    shaders[name] = std::make_shared<Shader>(workspace + vertex, workspace + fragment);
}

void AssetManager::load_texture(const std::string& name, const std::string& path) {
    textures[name] = std::make_shared<Texture>(workspace + path, true);
}

void AssetManager::remove_shader(const std::string& name) {
    auto shader = shaders.find(name);
    if (shader != shaders.end()) {
        shader->second->destroy();
        shaders.erase(name);
    }
}

void AssetManager::remove_texture(const std::string& name) {
    auto texture = textures.find(name);
    if (texture != textures.end()) {
        texture->second->destroy();
        textures.erase(name);
    }
}

void AssetManager::init_assets() {
    for (auto& [name, shader] : shaders) {
        shader->load();
    }
    for (auto& [name, texture] : textures) {
        texture->load();
    }
}

void AssetManager::destroy_assets() {
    for (auto& [name, shader] : shaders) {
        shader->destroy();
    }
    for (auto& [name, texture] : textures) {
        texture->destroy();
    }
    shaders.clear();
    textures.clear();
}

void AssetManager::set_workspace(const std::string& path) {
    workspace = std::filesystem::absolute(std::filesystem::path(path)).parent_path().parent_path().string();
}

const std::string& AssetManager::get_workspace() const {
    return workspace;
}

const std::shared_ptr<AssetManager>& get_asset_manager() {
    static const std::shared_ptr<AssetManager> instance = std::make_shared<AssetManager>();
    return instance;
}

//TODO: implement reference counting, aka how many times an object has been loaded, so it doesn't unload an asset if other objects still use it in the scene
//TODO: implement a preventUnload boolean for preventing unloading of a commonly used asset
