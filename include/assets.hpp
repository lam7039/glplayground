#pragma once

#include <unordered_map>
#include <string>

#include "glm/glm.hpp"

enum AssetType {
    IMAGE,
    SOUND,
    SHADER,
    FONT
};

class Asset {
public:
    const std::string &name;
    AssetType type = AssetType::IMAGE;

    virtual void bind();
    virtual void bind(int index);
    Asset(const std::string &name, AssetType type);
};

class Shader : public Asset {
public:
    Shader(const std::string &name, const std::string &vertexSource = "../shaders/vertex.glsl", const std::string &fragmentSource = "../shaders/fragment.glsl");
    
    void bind() override;
    void setWireframe();

    void setBool(const std::string &name, bool value);
    void setInt(const std::string &name, int value);
    void setFloat(const std::string &name, float value);
    void setImage(const std::string &name, int *samplers);
    void setMatrix(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int programId {0};
    int getLocation(const std::string &name) const;
};

class Texture : public Asset {
public:
    Texture(const std::string &name, const std::string &path, bool mipmap = false);

    void bind(int index) override;
    void destroy();
    
private:
    unsigned int textureId {0};
};

class AssetLoader {
public:
    AssetLoader();

    template <typename T>
    T *find(const std::string &name);
    Asset *loadTexture(const std::string &name, const std::string &path);
    Asset *loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
    
    void bind();
    void quit();
    
private:
    std::string workspace;
    std::unordered_map<std::string, Asset*> assets;
};
