#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include <entt/entt.hpp>

class AssetManager {
public:
    entt::resource<Shader> get_shader(const std::string& name);
    entt::resource<Texture> get_texture(const std::string& name);
    
    void load_shader(const std::string& name, const std::string& vertex, const std::string& fragment);
    void load_texture(const std::string& name, const std::string& source);

    void remove_shader(const std::string& name);
    void remove_texture(const std::string& name);

    void destroy_assets();

    void set_workspace(const std::string& path);
    const std::string& get_workspace() const;
private:
    struct ShaderLoader final {
        using result_type = std::shared_ptr<Shader>;

        result_type operator()(const std::string& vertex, const std::string& fragment) const {
            auto shader = std::make_shared<Shader>(vertex, fragment);
            shader->load();
            return shader;
        }
    };

    struct TextureLoader final {
        using result_type = std::shared_ptr<Texture>;
        
        result_type operator()(const std::string& source, bool mipmap) const {
            auto texture = std::make_shared<Texture>(source, mipmap);
            texture->load();
            return texture;
        }
    };

    entt::resource_cache<Shader, ShaderLoader> shader_cache;
    entt::resource_cache<Texture, TextureLoader> texture_cache;

    std::string workspace;
};

const std::shared_ptr<AssetManager>& get_asset_manager();
