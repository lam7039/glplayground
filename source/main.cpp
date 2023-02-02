#include "assets.hpp"
#include "window.hpp"
#include "vertex.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: OpenAL

int main(int argc, char **argv) {
    Window window("glplayground");

    // glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 500.0f, -1.0f, 1.0f);
    glm::mat4 projection = glm::ortho(0.0f, window.size().x, 0.0f, window.size().y, -1.0f, 1.0f);

    AssetLoader assetloader;
    Shader *shader = static_cast<Shader*>(assetloader.loadShader("main", "shaders/vertex.glsl", "shaders/fragment.glsl"));

    int samplers[2] = { 0, 1 };
    shader->bind();
    shader->setImage("ourTextures", samplers);
    shader->setMatrix("mvp_matrix", projection);

    assetloader.loadTexture("image", "assets/image.jpg");
    assetloader.loadTexture("mario", "assets/mario.png");

    VertexArray vertexArrays;
    vertexArrays.init();

    while (window.running()) {
        window.pollEvents();
        
        window.clear();
        assetloader.bind();

        vertexArrays.bind();
        vertexArrays.draw();

        window.swap();
    }

    assetloader.quit();
    window.quit();
    return 0;
}
