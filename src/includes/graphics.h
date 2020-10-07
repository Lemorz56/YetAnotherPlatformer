// Created by Sebastian Mossberg on 2020-10-06.
// Copyright (c) 2020 MSBRG. All rights reserved.
#ifndef GRAPHICS_H
#define GRAPHICS_H
/* Graphics Class
 * Holds all information to deal with the graphics for the game
 */
#include <map>
#include <string>

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
    Graphics();
    ~Graphics();

    /* SDL_Surface *loadImage
     * Loads an image into _spriteSheets map if it doesn't already exist.
     * Each image will ever only be loaded ONCE.
     * Returns the image from the map whether or not it was just loaded
     */
    SDL_Surface* loadImage(const std::string &filePath);

    void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);
private:
    SDL_Window* _window;
    SDL_Renderer* _renderer;

    std::map<std::string, SDL_Surface*> _spriteSheets;
};

#endif //GRAPHICS_H
