#include "dispatcher.hpp"

Dispatcher::Dispatcher() {
    
}

Entity *Dispatcher::dispatch(Entity *entity) {
    entities.push_back(entity);
}
