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
#include "rectangle.h"
#include "globals.h"

class Sprite {
public:
    Sprite();
    Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
           float posX, float posY);
    virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);

    const Rectangle getBoundingBox() const;
    const sides::Side getCollisionSide(Rectangle &other) const;

protected:
    SDL_Rect _sourceRect;
    SDL_Texture* _spriteSheet;

    Rectangle _boundingBox;

    float _x, _y;
private:
};

#endif //SPRITE_H
