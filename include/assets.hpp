#pragma once

#include <glm/glm.hpp>

#include <unordered_map>
#include <string>
#include <memory>

enum AssetType {
    IMAGE,
    SOUND,
    SHADER,
    FONT
};

class Asset {
public:
    AssetType type;
    Asset(const std::string &name, AssetType type);

    virtual void bind() = 0;
    virtual void destroy() = 0;

    unsigned int getId() const;
    unsigned int getReferenceCount() const;

    void addReference();
    void removeReference();
protected:
    unsigned int id {0};
    unsigned int referenceCount {0};
};

//TODO: separate shader from asset file
class Shader : public Asset {
public:
    Shader(const std::string &name, const std::string &vertex_source = "/shaders/vertex.glsl", const std::string &fragment_source = "/shaders/fragment.glsl");
    
    void bind() override;
    void destroy() override;
    void set_wireframe();

    void set_bool(const std::string &name, bool value);
    void set_int(const std::string &name, int value);
    void set_float(const std::string &name, float value);
    void set_image(const std::string &name, int *samplers);
    void set_image(const std::string &name, int sampler);
    void set_matrix(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int vertex_shader {0};
    unsigned int fragment_shader {0};
    std::unordered_map<std::string, int> uniform_location_cache;

    unsigned int compile_shader(unsigned int type, const char *source);
    unsigned int create_program();

    int get_location(const std::string &name);
};

class Texture : public Asset {
public:
    Texture(const std::string &name, const std::string &path, bool mipmap = false);

    void bind() override;
    void bind(int index);
    void destroy() override;
private:
    unsigned int slot {0};
};

namespace Global {

    const std::string &get_workspace();

    std::shared_ptr<Asset> get_asset(const std::string &name);

    template <typename T>
    std::shared_ptr<T> get_asset(const std::string &name) {
        return std::static_pointer_cast<T>(get_asset(name));
    }

    void load_asset(const std::string &name, std::shared_ptr<Asset> asset);
    void load_shader(const std::string &name, const std::string &vertex, const std::string &fragment);
    void load_texture(const std::string &name, const std::string &path);

    void remove_asset(const std::string &name);
    void destroy_assets();

}