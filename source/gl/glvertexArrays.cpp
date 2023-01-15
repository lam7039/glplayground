#include "gl.hpp"
#include "draw.hpp"

static GLVertexArray glVertexArray;

void VertexArray::init(int shaderProgramId) {
    //xyz rgb st, index
    float vertices[] = {
         0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   0.0f, // top right
         0.0f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   0.0f, // bottom right
        -1.0f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   0.0f, // bottom left
        -1.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   0.0f, // top left 
        
         1.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,   1.0f, // top right
         1.0f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,   1.0f, // bottom right
         0.0f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,   1.0f, // bottom left
         0.0f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   1.0f, // top left 
    };

    glCreateVertexArrays(1, &glVertexArray.vertexArrayObject);
    glBindVertexArray(glVertexArray.vertexArrayObject);

    glCreateBuffers(1, &glVertexArray.vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, glVertexArray.vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int indices[] = {
        0, 1, 3, 1, 2, 3,
        4, 5, 7, 5, 6, 7
    };

    glCreateBuffers(1, &glVertexArray.elementBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glVertexArray.elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    // glBindAttribLocation(shaderProgramId, 0, "inPosition");
    
    //color
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3* sizeof(float)));
    // glBindAttribLocation(shaderProgramId, 1, "inColor");
    
    //texcoords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
    // glBindAttribLocation(shaderProgramId, 2, "inTexCoord");
    
    //texture id
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
    // glBindAttribLocation(shaderProgramId, 3, "inTextureId");

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::draw() {
    glBindVertexArray(glVertexArray.vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
