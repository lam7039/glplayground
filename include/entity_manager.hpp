// #pragma once

// #include "entity.hpp"
// #include "drawable.hpp"

// class EntityManager {
// public:
//     void add_entity(std::shared_ptr<Entity> entity);
//     void remove_entity(unsigned int id);

//     void init_entities();
//     void update_entities();
//     void destroy_entities();
    
//     void update_drawables();
//     const DrawableMapAlias& get_drawables() const;
// private:
//     unsigned int identifier {1};
//     EntityMapAlias entities;
//     DrawableMapAlias drawables;
// };

// //TODO: load/unload Entities per scene
// //NOTE: is entity manager still necessary with an ECS?