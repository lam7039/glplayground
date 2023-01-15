#include "gl.hpp"
#include "draw.hpp"
#include <iostream>
#include <array>
#include <string.h>

static GLVertexArray glVertexArray;

static std::array<Vertex, 4> createQuad(float x, float y, float textureId) {
    float size = 1.0f;
    
    // top right
    Vertex v0;
    v0.position = {x + size, y, 0.0f};
    v0.color = {1.0f, 0.0f, 0.0f};
    v0.texCoords = {1.0f, 1.0f};
    v0.textureId = textureId;

    // bottom right
    Vertex v1;
    v1.position = {x + size, y + size, 0.0f};
    v1.color = {0.0f, 1.0f, 0.0f};
    v1.texCoords = {1.0f, 0.0f};
    v1.textureId = textureId;

    // bottom left
    Vertex v2;
    v2.position = {x, y + size, 0.0f};
    v2.color = {0.0f, 0.0f, 1.0f};
    v2.texCoords = {0.0f, 0.0f};
    v2.textureId = textureId;

    // top left 
    Vertex v3;
    v3.position = {x, y, 0.0f};
    v3.color = {1.0f, 1.0f, 1.0f};
    v3.texCoords = {0.0f, 1.0f};
    v3.textureId = textureId;

    return {v0, v1, v2, v3};
}

void VertexArray::init() {
    const size_t maxQuadCount = 8;
    const size_t maxVertexCount = maxQuadCount * 4;
    const size_t maxIndexCount = maxQuadCount * 6;


    glCreateVertexArrays(1, &glVertexArray.vertexArrayObject);
    glBindVertexArray(glVertexArray.vertexArrayObject);

    glCreateBuffers(1, &glVertexArray.vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, glVertexArray.vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, maxQuadCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;
    for (size_t i = 0; i < maxIndexCount; i += 6) {
        indices [i + 0] = 0 + offset;
        indices [i + 1] = 1 + offset;
        indices [i + 2] = 3 + offset;

        indices [i + 3] = 1 + offset;
        indices [i + 4] = 2 + offset;
        indices [i + 5] = 3 + offset;

        offset += 4;
    }

    glCreateBuffers(1, &glVertexArray.elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glVertexArray.elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    
    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));
    
    //texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));
    
    //texture id
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, textureId));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::bind() {
    auto q0 = createQuad(-1.0f, -0.5f, 0.0f);
    auto q1 = createQuad( 0.0f, -0.5f, 1.0f);

    Vertex vertices[8];
    memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
    memcpy(vertices + q0.size(), q1.data(), q1.size() * sizeof(Vertex));

    glBindBuffer(GL_ARRAY_BUFFER, glVertexArray.vertexBufferObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
}

void VertexArray::draw() {
    glBindVertexArray(glVertexArray.vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}
