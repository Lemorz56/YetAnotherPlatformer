// Created by Sebastian on 2020-10-10.
// Copyright (c) 2020 MSBRG. All rights reserved.
#include "includes/level.h"
#include "includes/graphics.h"
#include "includes/globals.h"
#include "includes/tinyxml2.h"
#include <SDL_log.h>

#include <sstream>
#include <algorithm>
#include <cmath>
#include <SDL.h>

using namespace tinyxml2;

Level::Level() {};

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0,0))
{
        this->loadMap(mapName, graphics);
}

Level::~Level() {}

void Level::loadMap(std::string mapName, Graphics &graphics) { //TODO This needs to be commented seriously
    // Parse .tmx file
    XMLDocument doc;
    std::stringstream ss;
    ss << "res/maps/" << mapName << ".tmx"; // passing Map1 will result in the res/maps/Map1.tmx
    doc.LoadFile(ss.str().c_str());
    XMLElement* mapNode = doc.FirstChildElement("map");

    // Get the width and the height of the whole map and store it in _size
    int width, height;
    mapNode->QueryIntAttribute("width", &width);
    mapNode->QueryIntAttribute("height", &height);
    this->_size = Vector2(width, height);

    // Get the width and the height of the tile and store it in _tileSize
    int tileWidth, tileHeight;
    mapNode->QueryIntAttribute("tilewidth", &tileWidth);
    mapNode->QueryIntAttribute("tileheight", &tileHeight);
    this->_tileSize = Vector2(tileWidth, tileHeight);

    // Get the tilesets
    XMLElement* pTileset = mapNode->FirstChildElement("tileset");
    if (pTileset != nullptr){
        while(pTileset) {
            int firstgid;
            const char* source = pTileset->FirstChildElement("image")->Attribute("source");
            char* path;
            std::stringstream ss;
            ss << source;
            pTileset->QueryIntAttribute("firstgid", &firstgid);
            // create texture
            SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
            this->_tilesets.emplace_back(tex, firstgid); //TODO Note emplace instead of push

            pTileset = pTileset->NextSiblingElement("tileset");
        }
    }

    // Load the layers TODO: fix super ugly loop to parse data
    XMLElement* pLayer = mapNode->FirstChildElement("layer");
    if (pLayer != nullptr) {
        while (pLayer) {
            // LOading the data element
            XMLElement* pData = pLayer->FirstChildElement("data");
            if (pData != nullptr) {
                while (pData) {
                    // Loading the tile element
                    XMLElement* pTile = pData->FirstChildElement("tile");
                    if (pTile != nullptr) {
                        int tileCounter = 0;
                        while(pTile) {
                            // Build each individual tile here
                            // IF gid is 0, no tile will be drawn
                            if (pTile->IntAttribute("gid") == 0) {
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    // WHY here again? cause if 0 below it will never make it down to the rest
                                    continue;
                                }
                                else {
                                    break; //nothing left, break out of loop
                                }
                            }

                            //IF not zero
                            // Get the tileset for this gid
                            int gid = pTile->IntAttribute("gid");
                            Tileset tls;
                            for (auto & _tileset : this->_tilesets) {
                                if (_tileset.FirstGid <= gid) {
                                    // THIS is the tileset we want
                                    tls = _tileset;
                                    break;
                                }
                            }

                            if (tls.FirstGid == -1) {
                                // NO tileset found for this gid
                                tileCounter++;
                                if (pTile->NextSiblingElement("tile")) {
                                    pTile = pTile->NextSiblingElement("tile");
                                    continue;
                                }
                                else {
                                    break;
                                }
                            }

                            // Get the position of the tile in the level
                            int xx = 0;
                            int yy = 0;
                            xx = tileCounter % width;
                            xx *= tileWidth;
                            yy += tileHeight * (tileCounter / width);
                            Vector2 finalTilePosition = Vector2(xx, yy);

                            // Calculate the position of the tile in the tileset - TSxx = Tileset XX
                            int tilesetWidth, tilesetHeight;
                            SDL_QueryTexture(tls.Texture, nullptr, nullptr, &tilesetWidth, &tilesetHeight);
                            int TSxx = gid % (tilesetWidth / tileWidth) - 1;
                            TSxx *= tileWidth;
                            int TSyy = 0;
                            int amount = (gid / (tilesetWidth / tileWidth));
                            TSyy = tileHeight * amount;

                            Vector2 finalTilesetPosition = Vector2(TSxx, TSyy);

                            // Build the actual tile and add it to the levels tile list
                            Tile tile (tls.Texture, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
                            this->_tileList.emplace_back(tile);
                            tileCounter++;

                            pTile = pTile->NextSiblingElement("tile"); // loop if theres more then 1 tile point
                        }
                    }
                    pData = pData->NextSiblingElement("data"); // loop if theres more then 1 data point
                }
            }
            pLayer = pLayer->NextSiblingElement("layer"); //loop if theres more then 1 layer point
        }
    }

    // Parse out the collisions
    XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
    if(pObjectGroup) {
        while(pObjectGroup) {
            const char* name = pObjectGroup->Attribute("name");
            std::stringstream ss;
            ss << name;
            if(ss.str() == "collisions") {
                XMLElement* pObject = pObjectGroup->FirstChildElement("object");

                if(pObject) {
                    while(pObject) {

                        float x, y, width, height;
                        x = pObject->FloatAttribute("x");
                        y = pObject->FloatAttribute("y");
                        width = pObject->FloatAttribute("width");
                        height = pObject->FloatAttribute("height");
                        this->_collisionRects.emplace_back(Rectangle(
                                std::ceil(x) * globals::SPRITE_SCALE,
                                std::ceil(y) * globals::SPRITE_SCALE,
                                std::ceil(width) * globals::SPRITE_SCALE,
                                std::ceil(height) * globals::SPRITE_SCALE
                                ));

                        pObject = pObject->NextSiblingElement("object");
                    }
                }
            }
            // other objectgroups go here with an else if(ss.str() == "whatever)
            pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
        }
    }
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
    for (auto & i : this->_tileList) {
        i.draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollision(const Rectangle &other) {
    std::vector<Rectangle> others;
    for (int i = 0; i < this->_collisionRects.size(); i++) {
        if(this->_collisionRects.at(i).collidesWith(other)) {
            others.emplace_back(this->_collisionRects.at(i));
        }
    }
    return others;
}

/* OLD DRAW function
    SDL_Rect sourceRect = { 0, 0, 64, 64 };
    SDL_Rect destRect;
    for (int x = 0; x < this->_size.x / 64; x++) {
        for (int y = 0; y < this->_size.y / 64; y++) {
            destRect.x = x * 64 * globals::SPRITE_SCALE;
            destRect.y = y * 64 * globals::SPRITE_SCALE;
            destRect.w = 64 * globals::SPRITE_SCALE;
            destRect.h = 64 * globals::SPRITE_SCALE;
            graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
        }
    }
 */

/* OLD LOAD FUNCTION
//TEMPORARY CODE TO LOAD THE BACKGROUND
this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage("res/backgrounds/bkBlue.png"));
this->_size = Vector2(1280, 960);
*/