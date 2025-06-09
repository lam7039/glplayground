#include "asset_manager.hpp"

#include <filesystem>

entt::resource<Shader> AssetManager::get_shader(std::string_view name) {
    return shader_cache[entt::hashed_string{name.data()}];
}

entt::resource<Texture> AssetManager::get_texture(std::string_view name) {
    return texture_cache[entt::hashed_string{name.data()}];
}

void AssetManager::load_shader(std::string_view name, std::string_view vertex, std::string_view fragment) {
    shader_cache.load(entt::hashed_string{name.data()}, workspace + vertex.data(), workspace + fragment.data());
}

void AssetManager::load_texture(std::string_view name, std::string_view source) {
    texture_cache.load(entt::hashed_string{name.data()}, workspace + source.data(), true);
}

void AssetManager::remove_shader(std::string_view name) {
    shader_cache.erase(entt::hashed_string{name.data()});
}

void AssetManager::remove_texture(std::string_view name) {
    texture_cache.erase(entt::hashed_string{name.data()});
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

void AssetManager::set_workspace(std::string_view path) {
    workspace = std::filesystem::absolute(std::filesystem::path(path.data())).parent_path().parent_path().string();
}

std::string_view AssetManager::get_workspace() const {
    return workspace;
}

const std::shared_ptr<AssetManager>& get_asset_manager() {
    static const std::shared_ptr<AssetManager> instance = std::make_shared<AssetManager>();
    return instance;
}

//TODO: don't destroy commonly used assets on scene unload
