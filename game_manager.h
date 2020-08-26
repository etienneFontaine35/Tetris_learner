#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>
#include <SFML/System.hpp>
#include "grid.h"
#include "graphics.h"
#include "player.h"
#include "tetris_ai.h"

#define GAME_SPEED_INITIAL 2.0
#define GAME_SPEED_RATE 0.75
#define GAME_SPEED_UPDATE 3

class GameManager
{
    public :
        GameManager();
        int keyToAction(Key& keysPressed);
        void runPlayerGame(Player player);

    private :
        sf::Clock mUpdateTimer;
        Grid mTetrisGrid;
        Display mGraphicEngine;
        double mGameSpeed;
};

#endif