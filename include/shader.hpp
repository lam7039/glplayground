#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

//TODO: load shaders separately and load them into a shader program class
class Shader {
public:
    Shader(std::string_view vertex_source = "/shaders/vertex.glsl", std::string_view fragment_source = "/shaders/fragment.glsl");
    
    void load();
    void bind();
    void destroy();

    void set_bool(std::string_view name, bool value);
    void set_int(std::string_view name, int value);
    void set_float(std::string_view name, float value);
    void set_image(std::string_view name, int* samplers);
    void set_image(std::string_view name, int sampler);
    void set_matrix(std::string_view name, const glm::mat4& matrix);

private:
    unsigned int program_id;
    const std::string vertex_source;
    const std::string fragment_source;

    std::unordered_map<std::string, int> uniform_location_cache;
    int get_location(std::string_view name);
};
