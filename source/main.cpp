#include "assets.hpp"
#include "renderer.hpp"
#include "rectangle.hpp"
#include "imgui.hpp"
#include "window.hpp"

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

    renderer.clearColor();
    renderer.clear();
    window.swap();

    ImGuiWrapper imgui;

    AssetLoader assetloader(std::filesystem::current_path());
    Shader *shader = assetloader.loadShader("main", "/shaders/vertex.glsl", "/shaders/fragment.glsl");
    Texture *backgroundTexture = assetloader.loadTexture("background", "/assets/image.jpg");
    Texture *marioTexture = assetloader.loadTexture("mario", "/assets/mario.png");
    assetloader.bind();

    //TODO: figure out where to put it (shader/texture/asset)
    // Shader *shader = assetloader.find<Shader>("main");
    // int maxTextureImageUnits;
    // glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
    int samplers[2]; //should be limit of GL_MAX_TEXTURE_IMAGE_UNITS
    for (int i = 0; i < 2; i++) {
        samplers[i] = i;
    }
    shader->setImage("ourTextures", samplers);

    glm::mat4 projection = glm::ortho(0.0f, window.size().x, 0.0f, window.size().y, -1.0f, 1.0f);
    shader->setMatrix("mvp_matrix", projection);

    glm::vec3 positionTextureBackground = {50.0f, 250.0f, 0.0f};
    glm::vec3 positionTextureMario = {500.0f, 250.0f, 0.0f};

    glm::vec3 sizeTextureBackground = {200.0f, 150.0f, 0.0f};
    glm::vec3 sizeTextureMario = {150.0f, 200.0f, 0.0f};

    Rectangle background(positionTextureBackground, sizeTextureBackground, backgroundTexture->getTextureId());
    Rectangle mario(positionTextureMario, sizeTextureMario, marioTexture->getTextureId());

    imgui.attach(window.instance());

    while (window.running()) {
        background.transform(positionTextureBackground, sizeTextureBackground);
        mario.transform(positionTextureMario, sizeTextureMario);

        renderer.clear();
        assetloader.bind();

        renderer.drawMesh(background.getMesh());
        renderer.drawMesh(mario.getMesh());

        imgui.set(positionTextureBackground, positionTextureMario, sizeTextureBackground, sizeTextureMario);
        imgui.render();

        window.swap();
        window.pollEvents();
    }

    imgui.detach();
    assetloader.quit();

    mario.destroy();
    background.destroy();

    window.destroy();
    
    return 0;
}
