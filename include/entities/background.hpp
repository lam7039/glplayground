#include "entity.hpp"
#include "drawable.hpp"

class Background : public Entity, public Drawable {
public:
    Background(int width, int height);

    void init() override final;
    void update() override final;
    void draw() override final;
    void destroy() override final;

private:
    int width;
    int height;
};
