// Created by Sebastian on 2020-10-10.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include "includes/level.h"
#include "includes/graphics.h"
#include "includes/globals.h"

#include <SDL.h>

Level::Level() {};

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0,0))
{
        this->loadMap(mapName, graphics);
}