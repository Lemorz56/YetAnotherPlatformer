// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include <SDL.h>
#include "includes/game.h"
#include "includes/graphics.h"

/* Game Class
 * This class holds all information for our main game loop
 */

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics;
    SDL_Event event;

    while (true){
        if(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                return;
            }
        } // sdl quit
    } //true loop breaks
}

void Game::draw(Graphics &graphics) {

}

void Game::update(float elapsedTime) {

}
