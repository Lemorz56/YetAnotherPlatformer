// Created by Sebastian on 2020-10-08.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include <SDL_image.h>
#include "includes/sprite.h"
#include "includes/graphics.h"
#include "includes/globals.h"

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
               float posX, float posY) :
        _x(posX),
        _y(posY)
{
    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = width;
    this->_sourceRect.h = height;

    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));
    if (this->_spriteSheet == NULL) {
        printf("\nError: Unable to load image\n");
    }

}
    //if(!this->_spriteSheet) { printf( "IMG LOAD: %s\n", IMG_GetError()); }
    Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
    SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * globals::SPRITE_SCALE,
                                      this->_sourceRect.h * globals::SPRITE_SCALE };
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update() {}