#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include <glm/glm.hpp>

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

// class Audio : public Asset {
// public:
//     Audio(const std::string &name);
// };

class AssetLoader {
public:
    AssetLoader();
    
    template <typename T>
    void load(const std::string &name, const std::string &path) {
        assets[name] = std::make_shared<T>(name, workspace + path, true);

        if (assets[name]->type == AssetType::IMAGE) {
            textureCount++;
        }
    }

    template <typename T>
    void load(const std::string &name, const std::string &vertex, const std::string &fragment) {
        assets[name] = std::make_shared<T>(name, workspace + vertex, workspace + fragment);
    }

    template <typename T>
    std::shared_ptr<T> find(const std::string &name) {
        return std::static_pointer_cast<T>(assets[name]);
    }

    std::unordered_map<std::string, std::shared_ptr<Asset>> &getAll();
    //TODO: use Open Asset Import Library (assimp) to load all assets (maybe keep stbi_image for fast image loading)

    void remove(const std::string &name);
    void bind();
    void quit();
    
private:
    std::string workspace;
    std::unordered_map<std::string, std::shared_ptr<Asset>> assets;
    
    //TODO: check how many times an asset is being used
    unsigned int textureCount {0};
};

static std::unique_ptr<AssetLoader> assetLoader = nullptr;
