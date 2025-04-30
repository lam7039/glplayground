#include "entity.hpp"
#include "shader.hpp"

class Camera : public Entity {
public:
    Camera(glm::vec2 viewport);

    void init() override final;
    void update() override final;
    void destroy() override final;
    
    void set_position(float x, float y, float z);
    void set_size(float x, float y, float z);
    
private:
    unsigned int identifier;

    std::shared_ptr<Shader> shader;
    glm::mat4 projection;
};
