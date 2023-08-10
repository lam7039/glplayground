#include "entity.hpp"
#include "assets.hpp"

class Camera : public Entity {
public:
    Camera(glm::vec2 windowSize);

    void init();
    void update();
    void setPosition(float x, float y, float z);
    void setSize(float x, float y, float z);
    
    glm::vec3 getPosition();

private:
    std::shared_ptr<Shader> shader;
    glm::mat4 projection;
};
