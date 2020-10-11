// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef GAME_H
#define GAME_H
#include "player.h"
#include "level.h"

/* Game Class
 * Holds all information for our main game loop
 */

// Forward declare Graphics class
class Graphics;

class Game{
public:
    Game();
    ~Game();
private:
    void gameLoop();
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    Player _player;

    Level _level;
};

#endif //GAME_H
