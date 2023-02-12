#pragma once

class ImGuiWrapper {
public:
    void attach(void *window);
    void detach();
    void render();
};
