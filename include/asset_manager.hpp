#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include <filesystem>

class AssetManager {
public:
    std::weak_ptr<Shader> get_shader(const std::string& name) const;
    std::weak_ptr<Texture> get_texture(const std::string& name) const;
    
    void load_shader(const std::string& name, const std::string& vertex, const std::string& fragment);
    void load_texture(const std::string& name, const std::string& path);

    void remove_shader(const std::string& name);
    void remove_texture(const std::string& name);

    void init_assets();
    void destroy_assets();

    void set_workspace(const std::string& path);
    const std::string& get_workspace() const;
private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
    std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    std::string workspace;
};

//TODO: load/unload assets per scene
const std::shared_ptr<AssetManager>& get_asset_manager();
