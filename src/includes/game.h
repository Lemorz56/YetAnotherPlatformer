// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef GAME_H
#define GAME_H
#include "sprite.h"

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

    Sprite _player;
};

#endif //GAME_H
