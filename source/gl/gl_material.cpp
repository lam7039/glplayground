#include "gl/gl.hpp"
#include "material.hpp"

Material::Material(unsigned int shader_id) : shader_id(shader_id) {}

void Material::bind_samplers() {
    // int samplerLocation = glGetUniformLocation(shaderId, "uTexture");
    // glUseProgram shaderId;
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, textureId);
    // glUniform1i(samplerLocation, 0);
}
