#pragma once

#include <string>
#include "vector2.hpp"
#include "vector3.hpp"

struct Window {
    bool running {false};
    vector2i position, size;
    void **window {nullptr};
    void *context {nullptr};
};

class Context {
public:
    void init(vector2i position, vector2i size, void **glFuncName);
    void clearColor(vector3f color = {0.2f, 0.2f, 0.2f});
    void clear();
};

//to AssetLoader?
struct Surface {
    void *surface;
    vector2i size;
    bool hasAlpha;
    void *pixels;
};

class Shader {
public:
    void init(std::string vertexSource = "../shaders/vertex.glsl", std::string fragmentSource = "../shaders/fragment.glsl");
    void use();
    void setWireframe();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setImage(const std::string &name, int *samplers) const;
    int programId() const;
};

class Texture {
    unsigned int textureId;
public:
    void load(std::string path);
    void bind(int index);
    void destroy();
};

class VertexArray {
public:
    void init(int shaderProgramId);
    void draw();
};
