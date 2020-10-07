// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include <SDL.h>
#include "includes/game.h"
#include "includes/graphics.h"
#include "includes/input.h"

/* Game Class
 * Holds all information for our main game loop
 */

// Creating the in namespace to keep the out of the way, dont want them global
namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

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

    int LAST_UPDATE_TIME = SDL_GetTicks();
    // STARTING GAME LOOP
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
        // Using input function to check if escape was pressed - then quit game loop
        if (input.wasKeyPressed(SDL_SCANCODE_ESCAPE)){
            return;
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        // If this takes less time then MAX_FRAME_TIME - pass it along
        // If takes more then MAX_FRAME_TIME - pass MAX_FRAME_TIME
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
    }
}

void Game::draw(Graphics &graphics) {

}

void Game::update(float elapsedTime) {

}
