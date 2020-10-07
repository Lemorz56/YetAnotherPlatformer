// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef INPUT_H
#define INPUT_H
#include <map>
#include <SDL.h>

class Input {
public:
    void beginNewFrame();
    void keyUpEvent(const SDL_Event& event);
    void keyDownEvent(const SDL_Event &event);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyRelease(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

private:
    std::map<SDL_Scancode, bool>_heldKeys;
    std::map<SDL_Scancode, bool>_pressedKeys;
    std::map<SDL_Scancode, bool>_releasedKeys;
};

#endif //INPUT_H