#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include <filesystem>

class AssetManager {
public:
    std::shared_ptr<Asset> get_asset(const std::string& name);
    std::shared_ptr<Shader> get_shader(const std::string& name);
    std::shared_ptr<Texture> get_texture(const std::string& name);
    
    void load_asset(const std::string& name, std::shared_ptr<Asset> asset);
    void load_shader(const std::string& name, const std::string& vertex, const std::string& fragment);
    void load_texture(const std::string& name, const std::string& path);
    void remove_asset(const std::string& name);

    void init_assets();
    void destroy_assets();

    const std::string& get_workspace() const;
private:
    std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
    const std::string workspace = std::filesystem::current_path();
};

std::shared_ptr<AssetManager>& get_asset_manager();
