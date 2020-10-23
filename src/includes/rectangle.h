// Created by Sebastian on 2020-10-18.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "globals.h"

class Rectangle {

public:
    Rectangle() = default;

    Rectangle(int x, int y, int width, int height) :
        _x(x),
        _y(y),
        _width(width),
        _height(height)
    {}

    const int getCenterX() const { return this->_x + this->_width / 2; }
    const int getCenterY() const { return this->_y + this->_height / 2; }

    const int getLeft() const { return this->_x; }
    const int getRight() const { return this->_x + _width; }
    const int getTop() const { return this->_y; }
    const int getBottom() const { return this->_y + this->_height; }

    const int getWidth() const { return this->_width; }
    const int getHeight() const { return this->_height; }

    const int getSides(const sides::Side side) const {
        return
                side == sides::LEFT ? this->getLeft() :
                side == sides::RIGHT ? this->getRight() :
                side == sides::TOP ? this->getTop() :
                side == sides::BOTTOM ? this->getBottom() :
                side == sides::NONE;
    }

    /* bool collidesWith
     * takes in another rect and checks if the two are colliding
     */
    const bool collidesWith(const Rectangle &other) const {
        return
                this->getRight() >= other.getLeft() &&
                this->getRight() <= other.getRight() &&
                this->getTop() <= other.getBottom() &&
                this->getBottom() >= other.getTop();
    }

    /* bool isValidRectangle
     *
     */
    const bool isValidRectangle() const {
        return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
    }
    int _x, _y, _width, _height;
private:
};
#endif //RECTANGLE_H