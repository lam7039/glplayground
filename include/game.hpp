#pragma once

// class Context {
// public:
//     vector2i position;
//     vector2i size;
//     vector3f color;

//     void init(vector2i position, vector2i size, void **glFuncName);
//     void clearColor(vector3f color = {0.2f, 0.2f, 0.2f});
//     void clear();
// };

class Game {
public:
    void init();
    void quit();

    void update();
    void render();
};
