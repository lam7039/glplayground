#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

struct TransformComponent {
    glm::vec3 position {0.0f};
    // glm::vec3 size {1.0f};
    glm::vec3 scale {1.0f};
    glm::vec3 rotation {0.0f}; //TODO: glm::quat rotation;

    //TODO: implement dirty flag and caching of matrix when there's thousands of entities to transform
    // bool dirty {true};
    // glm::mat4 cached_matrix;

    glm::mat4 matrix() const {
        // if (!dirty) {
        //     return cached_matrix;
        // }

        glm::mat4 model(1.0f);

        model = glm::translate(model, position);
        
        model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        
        model = glm::scale(model, scale);


        // cached_matrix = model;

        return model;
    }
};
