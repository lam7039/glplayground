#include "asset_manager.hpp"

std::shared_ptr<Asset> AssetManager::get_asset(const std::string& name) {
    return assets[name];
}

std::shared_ptr<Shader> AssetManager::get_shader(const std::string& name) {
    return std::static_pointer_cast<Shader>(get_asset(name));
}

std::shared_ptr<Texture> AssetManager::get_texture(const std::string& name) {
    return std::static_pointer_cast<Texture>(get_asset(name));
}

void AssetManager::load_asset(const std::string& name, std::shared_ptr<Asset> asset) {
    assets[name] = std::move(asset);
}

void AssetManager::load_shader(const std::string& name, const std::string& vertex, const std::string& fragment) {
    load_asset(name, std::make_shared<Shader>(workspace + vertex, workspace + fragment));
}

void AssetManager::load_texture(const std::string& name, const std::string& path) {
    load_asset(name, std::make_shared<Texture>(workspace + path, true));
}

void AssetManager::remove_asset(const std::string& name) {
    assets[name]->destroy();
    assets.erase(name);
}

void AssetManager::init_assets() {
    for (auto& [name, asset] : assets) {
        asset->init();
    }
}

void AssetManager::destroy_assets() {
    for (auto& [name, asset] : assets) {
        asset->destroy();
    }
    assets.clear();
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
