#include "assets.hpp"
#include "window.hpp"
#include "rectangle.hpp"
#include "imgui.hpp"

#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: OpenAL, assimp

int main(int argc, char **argv) {
    std::filesystem::path current_path = std::filesystem::current_path();

    Window window("glplayground");
    ImGuiWrapper imgui;

    AssetLoader assetloader(std::string(current_path) + "/../");
    Shader *shader = assetloader.loadShader("main", "shaders/vertex.glsl", "shaders/fragment.glsl");
    Texture *imageTexture = assetloader.loadTexture("image", "assets/image.jpg");
    Texture *marioTexture = assetloader.loadTexture("mario", "assets/mario.png");
    assetloader.bind();

    // Shader *shader = assetloader.find<Shader>("main");
    int samplers[2]; //should be limit of GL_MAX_TEXTURE_IMAGE_UNITS
    for (int i = 0; i < 2; i++) {
        samplers[i] = i;
    }
    shader->setImage("ourTextures", samplers);

    glm::mat4 projection = glm::ortho(0.0f, window.size().x, 0.0f, window.size().y, -1.0f, 1.0f);
    shader->setMatrix("mvp_matrix", projection);

    {
        Rectangle image(50.0f, 250.0f, 200.0f, 150.0f, imageTexture->getTextureId());
        Rectangle mario(500.0f, 250.0f, 150.0f, 200.0f, marioTexture->getTextureId());

        imgui.attach(window.get());

        while (window.running()) {
            window.clear();
            assetloader.bind();

            image.draw();
            mario.draw();
            imgui.render();

            window.swap();

            window.pollEvents();
        }

        imgui.detach();
        assetloader.quit();
    }

    window.destroy();
    
    return 0;
}
