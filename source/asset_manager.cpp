#include "asset_manager.hpp"

#include <filesystem>

entt::resource<Shader> AssetManager::get_shader(const std::string& name) {
    return shader_cache[entt::hashed_string{name.c_str()}];
}

entt::resource<Texture> AssetManager::get_texture(const std::string& name) {
    return texture_cache[entt::hashed_string{name.c_str()}];
}

void AssetManager::load_shader(const std::string& name, const std::string& vertex, const std::string& fragment) {
    shader_cache.load(entt::hashed_string{name.c_str()}, workspace + vertex, workspace + fragment);
}

void AssetManager::load_texture(const std::string& name, const std::string& source) {
    texture_cache.load(entt::hashed_string{name.c_str()}, workspace + source, true);
}

void AssetManager::remove_shader(const std::string& name) {
    shader_cache.erase(entt::hashed_string{name.c_str()});
}

void AssetManager::remove_texture(const std::string& name) {
    texture_cache.erase(entt::hashed_string{name.c_str()});
}

void AssetManager::destroy_assets() {
    for (const auto& [id, shader] : shader_cache) {
        shader->destroy();
    }
    for (const auto& [id, texture] : texture_cache) {
        texture->destroy();
    }

    shader_cache.clear();
    texture_cache.clear();
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

//TODO: don't destroy commonly used assets on scene unload
