#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 position {0.0f};
    glm::vec4 color {1.0f};
    glm::vec2 texCoords;
};

class Mesh {
public:
    //TODO: somehow use a vertexBufferId intead of passing the entire list
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, const std::string &texture);

    void bind(std::vector<Vertex> &vertices);
    void inputLayoutBind();
    void inputLayoutUnbind();
    void destroy();
    
    unsigned int getIndexCount() const;
    const std::string &getTexture() const;
private:
    const std::string &texture; 
    std::vector<Vertex> vertexData;
    std::vector<unsigned int> indexData;

    unsigned int inputLayoutObject {0};
    unsigned int vertexBufferObject {0};
    unsigned int elementBufferObject {0};
    
    unsigned int getVertexDataSize() const;
};
