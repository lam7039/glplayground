#include "entity.hpp"
#include "drawable.hpp"

class Player : public Entity, public Drawable {
public:
    void init() override final;
    void update() override final;
    void draw() override final;
    void destroy() override final;
};
