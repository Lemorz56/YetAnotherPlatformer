// Created by Sebastian on 2020-10-25.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef SLOPE_H
#define SLOPE_H

#include "globals.h"

class Slope {
public:
    Slope() {}
    Slope(Vector2 p1, Vector2 p2) :
        _p1(p1),
        _p2(p2)
    {
        if(_p2.x - _p1.x != 0) {
            _slope = (fabs(_p2.y) - fabs(_p1.y)) / (fabs(_p2.x) - fabs(_p1.x));
        }
    }

    const inline float getSlope() const {
        return this->_slope;
    }

    const bool collidesWith(const Rectangle &other) const {
        return
                (other.getRight() >= _p2.x &&
                other.getLeft() <= _p1.x &&
                other.getTop() <= _p2.y &&
                other.getBottom() >= _p1.y)
                ||
                (other.getRight() >= _p1.x &&
                other.getLeft() <= _p2.x &&
                other.getTop() <= p1.y &&
                other.getBottom() >= _p2.y)
                ||
                (other.getLeft() <= _p1.x &&
                other.getRight() >= _p2.x &&
                other.getTop() <= _p1.y &&
                other.getBottom() >= _p2.y)
                ||
                (other.getLeft() <= _p2.x &&
                other.getRight() >= _p1.x &&
                other.getTop() <= _p2.y &&
                other.getBottom() >= _p1.y);
    }

private:
    Vector2 _p1, _p2;
    float _slope;
};

#endif //SLOPE_H
