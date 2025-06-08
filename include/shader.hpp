#pragma once

#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

//TODO: load shaders separately and load them into a shader program class
class Shader {
public:
    Shader(const std::string& vertex_source = "/shaders/vertex.glsl", const std::string& fragment_source = "/shaders/fragment.glsl");
    
    void load();
    void bind();
    void destroy();

    void set_bool(const std::string& name, bool value);
    void set_int(const std::string& name, int value);
    void set_float(const std::string& name, float value);
    void set_image(const std::string& name, int* samplers);
    void set_image(const std::string& name, int sampler);
    void set_matrix(const std::string& name, const glm::mat4& matrix);

private:
    unsigned int program_id;
    const std::string vertex_source;
    const std::string fragment_source;

    std::unordered_map<std::string, int> uniform_location_cache;
    int get_location(const std::string& name);
};
