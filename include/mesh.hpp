#pragma once

#include <vector>

class Mesh {
public:
    Mesh(const std::vector<float> &vertices, const std::vector<unsigned int> &indices);

    const float *getVertexDataPtr() const;
    unsigned int getVertexDataSize() const;
    unsigned int getIndexCount() const;
private:
    std::vector<float> vertexData;
    std::vector<unsigned int> indexData;
};