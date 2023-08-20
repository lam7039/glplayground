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
    AssetType type = AssetType::IMAGE;
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

class Shader : public Asset {
public:
    Shader(const std::string &name, const std::string &vertexSource = "/shaders/vertex.glsl", const std::string &fragmentSource = "/shaders/fragment.glsl");
    
    void bind() override;
    void destroy() override;
    void setWireframe();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setImage(const std::string &name, int *samplers);
    void setImage(const std::string &name, int sampler);
    void setMatrix(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int vertexShader {0};
    unsigned int fragmentShader {0};
    std::unordered_map<std::string, int> uniformLocationCache;

    unsigned int compileShader(unsigned int type, const char *source);
    unsigned int createProgram();

    int getLocation(const std::string &name);
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

const std::string &get_workspace();

std::shared_ptr<Asset> get_asset(const std::string &name);

template <typename T>
std::shared_ptr<T> get_asset(const std::string &name) {
    return std::static_pointer_cast<T>(get_asset(name));
}

void load_asset(const std::string &name, std::shared_ptr<Asset> asset);

template <typename T>
void load_asset(const std::string &name, const std::string &path) {
    load_asset(name, std::make_shared<T>(name, get_workspace() + path, true));
}

template <typename T>
void load_asset(const std::string &name, const std::string &vertex, const std::string &fragment) {
    load_asset(name, std::make_shared<T>(name, get_workspace() + vertex, get_workspace() + fragment));
}

void remove_asset(const std::string &name);
void destroy_assets();
