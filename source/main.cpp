#include "assets.hpp"
#include "window.hpp"
#include "rectangle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: ImGui, OpenAL

int main(int argc, char **argv) {
    Window window("glplayground");

    AssetLoader assetloader;
    assetloader.loadShader("main", "shaders/vertex.glsl", "shaders/fragment.glsl");
    assetloader.loadTexture("image", "assets/image.jpg");
    assetloader.loadTexture("mario", "assets/mario.png");

    Shader *shader = assetloader.find<Shader>("main");
    shader->bind();

    int samplers[2]; //should be limit of GL_MAX_TEXTURE_IMAGE_UNITS
    for (int i = 0; i < 2; i++) {
        samplers[i] = i;
    }
    shader->setImage("ourTextures", samplers);

    glm::mat4 projection = glm::ortho(0.0f, window.size().x, 0.0f, window.size().y, -1.0f, 1.0f);
    shader->setMatrix("mvp_matrix", projection);

    {
        Rectangle image(50.0f, 250.0f, 200.0f, 150.0f, 0.0f);
        Rectangle mario(500.0f, 250.0f, 150.0f, 200.0f, 1.0f);

        while (window.running()) {
            window.clear();
            assetloader.bind();

            image.draw();
            mario.draw();

            window.swap();
            window.pollEvents();
        }

        assetloader.quit();
    }
    
    return 0;
}
