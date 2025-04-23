#include "gl/gl.hpp"
#include "material.hpp"

Material::Material(unsigned int shaderId) : shaderId(shaderId) {}

void Material::bindSamplers() {
    // int samplerLocation = glGetUniformLocation(shaderId, "ourTextures");
    // glUseProgram shaderId;
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, textureId);
    // glUniform1i(samplerLocation, 0);
}
