#include "windows.hpp"
#include "assets.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: replace SDL with GLFW, OpenAL

int main(int argc, char **argv) {
    WindowManager windowmanager;
    windowmanager.add("Gamedev practice");

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 500.0f, -1.0f, 1.0f);

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

    while (windowmanager.find(0)->running) {
        windowmanager.setCurrent(0);
        windowmanager.pollEvents(0);
        
        windowmanager.clearContext();
        assetloader.bind();

        vertexArrays.bind();
        vertexArrays.draw();

        windowmanager.swap(0);
    }

    assetloader.quit();
    windowmanager.quit();
    return 0;
}
