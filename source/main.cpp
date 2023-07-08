#include "assets.hpp"
#include "window.hpp"
#include "renderer.hpp"
#include "quad.hpp"
#include "imgui.hpp"

#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//TODO: OpenAL, assimp
//TODO: create Entity -> Object and EntityManager classes
//TODO: put position/size/textureID in Entity and use Entity list from EntityManager in imgui class 

int main(int argc, char **argv) {
    std::filesystem::current_path(std::filesystem::path(argv[0]).parent_path().parent_path());
    
    Window window("glplayground");
    Renderer renderer;

    ImGuiWrapper imgui;

    AssetLoader assetloader(std::filesystem::current_path());
    Shader *shader = assetloader.loadShader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    Texture *backgroundTexture = assetloader.loadTexture("background", "/assets/image.jpg");
    Texture *marioTexture = assetloader.loadTexture("mario", "/assets/mario.png");
    assetloader.bind();

    //TODO: figure out what the heck samplers are actually
    // Shader *shader = assetloader.find<Shader>("main");
    int samplers[2]; //should be limit of GL_MAX_TEXTURE_IMAGE_UNITS
    for (int i = 0; i < 2; i++) {
        samplers[i] = i;
    }
    shader->setImage("ourTextures", samplers);

    glm::mat4 projection = glm::ortho(0.0f, window.size().x, 0.0f, window.size().y, -1.0f, 1.0f);
    shader->setMatrix("mvp_matrix", projection);

    glm::vec3 positionBackgroundTexture = {50.0f, 250.0f, 0.0f};
    glm::vec3 positionMarioTexture = {500.0f, 250.0f, 0.0f};

    glm::vec3 sizeBackgroundTexture = {200.0f, 150.0f, 0.0f};
    glm::vec3 sizeMarioTexture = {150.0f, 200.0f, 0.0f};

    {
        Quad background(positionBackgroundTexture, sizeBackgroundTexture, backgroundTexture->getTextureId());
        Quad mario(positionMarioTexture, sizeMarioTexture, marioTexture->getTextureId());

        imgui.attach(window.instance());

        while (window.running()) {
            background.transform(positionBackgroundTexture, sizeBackgroundTexture, backgroundTexture->getTextureId());
            mario.transform(positionMarioTexture, sizeMarioTexture, marioTexture->getTextureId());
            
            renderer.clear();
            assetloader.bind();

            imgui.new_frame();

            renderer.draw(background.getMesh());
            renderer.draw(mario.getMesh());

            imgui.render(positionBackgroundTexture, positionMarioTexture);

            window.swap();
            window.pollEvents();
        }

        imgui.detach();
        assetloader.quit();
    }

    window.destroy();
    
    return 0;
}
