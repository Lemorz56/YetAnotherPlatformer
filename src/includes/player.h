// Created by Sebastian on 2020-10-09.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef PLAYER_H
#define PLAYER_H
#include "animatedsprite.h"
#include "globals.h"
#include "slope.h"

class Graphics;

class Player : public AnimatedSprite {
public:
    Player();
    Player(Graphics &graphics, Vector2 spawnPoint);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    /* void moveLeft
     * moves the player left by -dx
     */
    void moveLeft();

    /* void moveRight
     * moves the player right by dx
     */
    void moveRight();

    /* void stopMoving
     * stops moving player and idle in the dir we faced
     */
    void stopMoving();

    /* void jump()
     * starts jumping
     */
    void jump();

    virtual void animationDone(std::string currentAnimation);
    virtual void setupAnimations();

    void handleTileCollisions(std::vector<Rectangle> &others);
    void handleSlopeCollisions(std::vector<Slope> &others);

    const float getX() const; // ONLY get not change
    const float getY() const; // ONLY get not change

private:
    float _dx, _dy;

    Direction _facing;

    bool _grounded;
};
#endif //PLAYER_H