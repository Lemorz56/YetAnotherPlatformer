// Created by Sebastian Mossberg on 2020-10-06.
// Copyright (c) 2020 MSBRG. All rights reserved.

#include <SDL.h>
#include <SDL_image.h>

#include "includes/graphics.h"

Graphics::Graphics() {
    SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "YetAnotherPlatformer");
}

Graphics::~Graphics() {
    SDL_DestroyWindow(this->_window);
}

SDL_Surface* Graphics::loadImage(const std::string &filePath) {
    if (this->_spriteSheets.count(filePath) == 0) {
        this->_spriteSheets[filePath] = IMG_Load(filePath.c_str());
    }
    return this->_spriteSheets[filePath];
    // Making sure we only load each image once, if it already is loaded great, if its not then load it!
}

void Graphics::blitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle) {
    SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

void Graphics::flip() {
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear() {
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer* Graphics::getRenderer() const {
    return this->_renderer;
}