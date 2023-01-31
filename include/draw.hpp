#pragma once

#include <string>
#include <glm/glm.hpp>

//to AssetLoader?
struct Surface {
    void *surface;
    glm::vec2 size;
    bool hasAlpha;
    void *pixels;
};

struct Vertex {
    glm::vec3 position;
    glm::vec4 color;
    glm::vec2 texCoords;
    float textureId;
};

struct Window {
    bool running {false};
    glm::vec2 position, size;
    void **window {nullptr};
    void *context {nullptr};
};

class Context {
public:
    void init(glm::vec2 position, glm::vec2 size, void **glFuncName);
    void clearColor(glm::vec4 color = {0.2f, 0.2f, 0.2f, 1.0f});
    void clear();
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
    void init();
    void bind();
    void draw();
};
