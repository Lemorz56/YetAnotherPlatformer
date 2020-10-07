// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include <SDL.h>
#include "includes/game.h"
#include "includes/graphics.h"
#include "includes/input.h"

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
    Input input;
    SDL_Event event;

    while (true){
        input.beginNewFrame(); // Reset pressed keys and release key

        if(SDL_PollEvent(&event)){
            if (event.type == SDL_KEYDOWN){

                if (event.key.repeat == 0){ // make sure its not HELD
                   input.keyDownEvent(event);
                }
            }
            else if (event.type == SDL_KEYUP){
                input.keyUpEvent(event);
            }
            else if (event.type == SDL_QUIT){
                return;
            }
        }
        // Using our own function to check if escape was pressed - then quit game loop
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            return;
        }
    }
}

void Game::draw(Graphics &graphics) {

}

void Game::update(float elapsedTime) {

}
