#include "assets.hpp"
#include "window.hpp"
#include "vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: OpenAL

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

    VertexArray vertexArrays;
    vertexArrays.init();

    while (window.running()) {
        window.clear();
        assetloader.bind();

        vertexArrays.bind();
        vertexArrays.draw();

        window.swap();
        window.pollEvents();
    }

    assetloader.quit();
    vertexArrays.quit();
    window.quit();
    return 0;
}
