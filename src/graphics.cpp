// Created by Sebastian Mossberg on 2020-10-06.
// Copyright (c) 2020 MSBRG. All rights reserved.

#include <SDL.h>
#include "includes/graphics.h"

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "YetAnotherPlatformer");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->_window);
}