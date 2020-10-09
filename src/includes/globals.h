// Created by Sebastian on 2020-10-09.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef GLOBALS_H
#define GLOBALS_H

namespace globals {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    const float SPRITE_SCALE = 2.0f;
}

struct Vector2{
    int x, y;
    Vector2() : // default constructor
    x(0), y(0)
    {}
    Vector2(int x, int y) : // our constructor
        x(x), y(y)
    {}
    Vector2 zero() { // returns an empty vector2
        return Vector2(0, 0);
    }
};

#endif //GLOBALS_H
