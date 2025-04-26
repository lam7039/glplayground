#pragma once

#include "asset.hpp"

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

class Shader : public Asset {
public:
    Shader(const std::string &vertex_source = "/shaders/vertex.glsl", const std::string &fragment_source = "/shaders/fragment.glsl");
    
    void bind() override;
    void destroy() override;
    void set_wireframe();

    void set_bool(const std::string &name, bool value);
    void set_int(const std::string &name, int value);
    void set_float(const std::string &name, float value);
    void set_image(const std::string &name, int *samplers);
    void set_image(const std::string &name, int sampler);
    void set_matrix(const std::string &name, const glm::mat4 &matrix);

private:
    unsigned int vertex_shader {0};
    unsigned int fragment_shader {0};
    std::unordered_map<std::string, int> uniform_location_cache;

    unsigned int compile_shader(unsigned int type, const char *source);
    unsigned int create_program();

    int get_location(const std::string &name);
};
