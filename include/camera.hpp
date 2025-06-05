#include "entity.hpp"
#include "shader.hpp"

class Camera : public Entity {
public:
    Camera(glm::vec2 viewport);

    void init() override final;
    void update() override final;
    void destroy() override final;
private:
    unsigned int identifier;

    glm::mat4 projection;
    glm::mat4 view {1.0f};
};

//TODO: use Rectangle class in EnTT instead of inheriting position and size from an Entity class