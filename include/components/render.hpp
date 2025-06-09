#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <string>

//TODO: figure out how to use TextureComponent instead of Texture class and separate load/destroy to a loader and bind to gl_renderer possibly?
struct TextureComponent {
    bool mipmap {false};
    uint32_t id {0};
    uint32_t slot {0};
    const std::string source;
};

struct CameraComponent {
    bool orthographic {true};
    glm::mat4 projection {1.0f};
    glm::mat4 view {1.0f};
};
