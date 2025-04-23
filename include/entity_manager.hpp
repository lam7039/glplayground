#pragma once

#include "entity.hpp"
#include "drawable.hpp"

class EntityManager {
public:
    void add_entity(std::shared_ptr<Entity> entity);

    template <typename T>
    void add_entity(glm::vec3 position, glm::vec3 size, std::string asset = "") {
        add_entity(std::make_shared<T>(position, size, asset));
    }

    void remove_entity(unsigned int id);

    void init_entities();
    void update_entities();
    void destroy_entities();
    
    DrawableMapAlias get_drawables() const;
private:
    unsigned int id {1};
    EntityMapAlias entities;
    DrawableMapAlias drawables;
};
