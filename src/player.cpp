// Created by Sebastian on 2020-10-09.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include "includes/player.h"
#include "includes/graphics.h"
#include "includes/animatedsprite.h"

Player::Player() {};

Player::Player(Graphics &graphics, float x, float y) :
    AnimatedSprite(graphics, "res/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100)
{
    graphics.loadImage("res/sprites/MyChar.png");
}