#include "entity.hpp"
#include "assets.hpp"

class Camera : public Entity {
public:
    Camera(glm::vec2 viewport, const std::string &identifier);

    void init();
    void update();
    void destroy();
    void setPosition(float x, float y, float z);
    void setSize(float x, float y, float z);

private:
    std::shared_ptr<Shader> shader;
    glm::mat4 projection;
};
