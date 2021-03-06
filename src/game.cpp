// Created by Sebastian on 2020-10-07.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include <SDL.h>
#include "includes/game.h"
#include "includes/graphics.h"
#include "includes/input.h"

// Creating the in namespace to keep the out of the way, dont want them global
namespace {
    const int FPS = 50;
    const int MAX_FRAME_TIME = 5 * 1000 / FPS;
}

Game::Game() {
    SDL_Init(SDL_INIT_EVERYTHING);
    printf("SDL Init done\n");
    this->gameLoop();
}

Game::~Game() {

}

void Game::gameLoop() {
    Graphics graphics;
    Input input;
    SDL_Event event;
    printf("Starting Gameloop\n");

    // CREATE & INIT LEVEL
    this->_level = Level("Map1", Vector2(100, 100), graphics);
    printf("Map Loaded\n");

    // CREATE & INIT PLAYER
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint()); //this->_level.getPlayerSpawnPoint()
    printf("Player Loaded\n");

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
        else if (input.isKeyHeld(SDL_SCANCODE_LEFT) == true) {
            this->_player.moveLeft();
        }
        else if (input.isKeyHeld(SDL_SCANCODE_RIGHT) == true) {
            this->_player.moveRight();
        }

        if(input.wasKeyPressed(SDL_SCANCODE_SPACE) == true) {
            this->_player.jump();
        }

        if(input.wasKeyPressed(SDL_SCANCODE_UP) == true) {
            _player.jump();
        }

        if (!input.isKeyHeld(SDL_SCANCODE_LEFT) && !input.isKeyHeld(SDL_SCANCODE_RIGHT)) {
            this->_player.stopMoving();
        }

        const int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_UPDATE_TIME;
        // If this takes less time then MAX_FRAME_TIME - pass it along
        // If takes more then MAX_FRAME_TIME - pass MAX_FRAME_TIME
        this->update(std::min(ELAPSED_TIME_MS, MAX_FRAME_TIME));
        LAST_UPDATE_TIME = CURRENT_TIME_MS;
        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics) {
    // First clear the frame
    graphics.clear();

    // Draw the frame
    this->_level.draw(graphics);
    this->_player.draw(graphics);

    // Update the surface to the display
    graphics.flip();
}

void Game::update(float elapsedTime) {
    // Update the player and the level
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime);

    // Check collisions
    std::vector<Rectangle> others;
    if ((others = this->_level.checkTileCollisions(this->_player.getBoundingBox())).size() > 0) {
        //Player collided with at least one tile. Handle it.
        this->_player.handleTileCollisions(others);
    }
    // Check SLOPE Collisions
    std::vector<Slope> otherSlopes;
    if ((otherSlopes = this->_level.checkSlopeCollisions(_player.getBoundingBox())).size() > 0) {
        _player.handleSlopeCollisions(otherSlopes);
    }
}