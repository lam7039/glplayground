#pragma once

#include "shader.hpp"
#include "texture.hpp"

#include <entt/entt.hpp>

class AssetManager {
public:
    entt::resource<Shader> get_shader(std::string_view name);
    entt::resource<Texture> get_texture(std::string_view name);
    
    void load_shader(std::string_view name, std::string_view vertex, std::string_view fragment);
    void load_texture(std::string_view name, std::string_view source);

    void remove_shader(std::string_view name);
    void remove_texture(std::string_view name);

    void destroy_assets();

    void set_workspace(std::string_view path);
    std::string_view get_workspace() const;
private:
    struct ShaderLoader final {
        using result_type = std::shared_ptr<Shader>;

        result_type operator()(std::string_view vertex, std::string_view fragment) const {
            auto shader = std::make_shared<Shader>(vertex, fragment);
            shader->load();
            return shader;
        }
    };

    struct TextureLoader final {
        using result_type = std::shared_ptr<Texture>;
        
        result_type operator()(std::string_view source, bool mipmap) const {
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
