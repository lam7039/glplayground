#include "entity.hpp"
#include "assets.hpp"

class Camera : public Entity {
public:
    Camera(glm::vec2 viewport);

    void init();
    void update();
    void destroy();
    
    void set_position(float x, float y, float z);
    void set_size(float x, float y, float z);
    
private:
    glm::vec3 position {0.0f, 0.0f, 0.0f};
    glm::vec3 size {1.0f, 1.0f, 1.0f};
    unsigned int identifier;

    std::shared_ptr<Shader> shader;
    glm::mat4 projection;
};
