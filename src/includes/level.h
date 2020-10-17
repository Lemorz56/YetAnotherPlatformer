// Created by Sebastian on 2020-10-10.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef LEVEL_H
#define LEVEL_H
#include <string>
#include <vector>

#include "globals.h"
#include "includes/tile.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level {
public:
    Level();
    Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
    ~Level();
    void update(int elapsedTime);
    void draw(Graphics &graphics);

private:
    std::string _mapName;
    Vector2 _spawnPoint;

    Vector2 _size;
    Vector2 _tileSize;

    SDL_Texture* _backgroundTexture;

    std::vector<Tile>_tileList;
    std::vector<Tileset>_tilesets;

    /* void loadMap
     * loads a map
     */
    void loadMap(std::string mapName, Graphics &graphics);
};

// Tileset structure
struct Tileset {
    SDL_Texture* Texture;
    int FirstGid;
    Tileset() {
        this->FirstGid = -1;
    }

    Tileset(SDL_Texture* texture, int firstGid) {
        this->Texture = texture;
        this->FirstGid = firstGid;
    }
};

#endif //LEVEL_H