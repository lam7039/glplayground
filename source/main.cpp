#include "windows.hpp"
#include "assets.hpp"
// #include "object.hpp"

int main(int argc, char **argv) {
    WindowManager windowmanager;
    windowmanager.add("Gamedev practice");

    AssetLoader assetloader;
    // Asset *imageAsset = assetloader.load({"image", "assets/image.jpg"});
    // Asset *marioAsset = assetloader.load({"mario", "assets/mario.png"});

    Shader shader;
    VertexArray vertexArrays;
    Texture imageTexture;
    Texture marioTexture;

    shader.init(assetloader.getWorkspace() + "shaders/vertex.glsl", assetloader.getWorkspace() + "shaders/fragment.glsl");
    shader.use();
    int samplers[2] = { 0, 1 };
    shader.setImage("ourTextures", samplers);

    vertexArrays.init(shader.programId());
    imageTexture.load("assets/image.jpg");
    marioTexture.load("assets/mario.png");
    


    // Object object(assetloader.getWorkspace());
    // Object marioObject(assetloader.getWorkspace());

    // object.init(assetloader.find("image"));
    // marioObject.init(assetloader.find("mario"));

    // assetloader.destroy("image");
    // assetloader.destroy("mario");

    while (windowmanager.find(0)->running) {
        windowmanager.setCurrent(0);
        windowmanager.pollEvents(0);
        
        windowmanager.clearContext();

        // object.draw(0);
        // marioObject.draw(1);

        shader.use();
        imageTexture.bind(0);
        marioTexture.bind(1);
        vertexArrays.draw();

        windowmanager.swap(0);

        // for (int i = 0; i < windowmanager.windowCount(); i++) {
        //     windowmanager.setCurrent(i);
        //     windowmanager.pollEvents(i);
            
        //     windowmanager.clearContext();

        //     object.draw(0);
        //     marioObject.draw(1);

        //     windowmanager.swap(i);
        // }
    }

    // marioObject.destroy();
    // object.destroy();
    imageTexture.destroy();
    marioTexture.destroy();

    assetloader.quit();
    windowmanager.quit();
    return 0;
}
