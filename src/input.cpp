// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include "includes/input.h"
/* Input Class
 * Keeps track of keyboard state
 */

// Function gets called at the beginning of each new frame
// to reset the keys that are no longer relevant
void Input::beginNewFrame() {
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
}


// This gets called when a key has been PRESSED
void Input::keyDownEvent(const SDL_Event &event) {
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

// This gets called when a key has been RELEASED
void Input::keyUpEvent(const SDL_Event &event) {
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false; // we let go of key
}

// Check if a certain key was PRESSED during the current frame
bool Input::wasKeyPressed(SDL_Scancode key) {
    return this->_pressedKeys[key];
}
// Check if a certain key was RELEASED during the current frame
bool Input::wasKeyRelease(SDL_Scancode key) {
    return this->_releasedKeys[key];
}
// Check if a certain key was HELD during the current frame
bool Input::isKeyHeld(SDL_Scancode key) {
    return this->_heldKeys[key];
}