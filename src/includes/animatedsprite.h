// Created by Sebastian on 2020-10-09.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include <map>
#include <string>
#include <vector>
#include "sprite.h"
#include "globals.h"

class Graphics;

/* AnimatedSprite class
 * holds logic for animating sprites
 */
class AnimatedSprite : public Sprite {
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
            float posX, float posY, float timeToUpdate);

    /* void playAnimation
     * plays the animation if it's not already playing
     */
    void playAnimation(std::string animation, bool once = false);

    /* void update
     * Updates the animated sprite (basically a timer)
     */
    void update(int elapsedTime);

    /* void draw
     * draws the sprite to the screen
     */
    void draw(Graphics &graphics, int x, int y);

protected:
    double _timeToUpdate;
    bool _currentAnimationOnce;
    std::string _currentAnimation;

    /* void addAnimation
     * adds an animation to the map of animations for the sprite
     */
    void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

    /* void resetAnimations
     *  reset all animations with the sprite
     */
    void resetAnimations();

    /* void stopAnimation
     * stops the current animation
     */
    void stopAnimation();

    /* bool setVisible
     * changes the visibility of the animated sprite
     */
    void setVisible(bool visible);

    /* virtual void animationDone
     * Logic that happens when the animation ends
     */
    virtual void animationDone(std::string currentAnimation) = 0;

    /* virtual void setupAnimations
     * A required function to setup all animations for a sprite
     */
    virtual void setupAnimations() = 0; // Pure virtual so that only derived can implement it

private:
    std::map<std::string, std::vector<SDL_Rect>> _animations;
    std::map<std::string, Vector2> _offsets;

    int _frameIndex; //frame we are at
    double _timeElapsed;
    bool _visible;
};

#endif //ANIMATEDSPRITE_H