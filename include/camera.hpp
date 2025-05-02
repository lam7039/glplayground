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

    std::shared_ptr<Shader> shader;
    glm::mat4 projection;
};
