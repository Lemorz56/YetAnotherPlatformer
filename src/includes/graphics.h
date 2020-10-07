// Created by Sebastian Mossberg on 2020-10-06.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;


};

#endif //GRAPHICS_H
