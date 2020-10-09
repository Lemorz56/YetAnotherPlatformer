// Created by Sebastian on 2020-10-08.
// Copyright (c) 2020 MSBRG. All rights reserved.
/*
 * Enemy class, player class and so on will be derived from this class therefore virtual methods and destructors
 * Sprite class - information for individual sprites
 */
#ifndef SPRITE_H
#define SPRITE_H
#include <SDL.h>
#include <string>
#include "graphics.h"

class Sprite {
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
           float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);
protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;
private:
    float _x, _y;
};

#endif //SPRITE_H