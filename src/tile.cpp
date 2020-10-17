// Created by Sebastian on 2020-10-17.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include "includes/tile.h"
#include "includes/graphics.h"

#include <SDL.h>

Tile::Tile(){}

Tile::Tile(SDL_Texture *tileset, Vector2 size, Vector2 tilesetPosition, Vector2 position) :
        _tileset(tileset),
        _size(size),
        _tilesetPosition(tilesetPosition),
        _position(Vector2(position.x * globals::SPRITE_SCALE, position.y * globals::SPRITE_SCALE))
{}


void Tile::update(int elapsedTime) {

}
// TODO fix the implicit casting
void Tile::draw(Graphics &graphics) {
    SDL_Rect destRect = { this->_position.x, this->_position.y,
                          static_cast<int>(this->_size.x * globals::SPRITE_SCALE),
                          static_cast<int>(this->_size.y * globals::SPRITE_SCALE) };

    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y };

    graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}
