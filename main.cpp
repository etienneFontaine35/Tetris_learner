#include <cstdlib>
#include <iostream>
#include <string>

#include "game_manager.h"
#include "player.h"

int main()
{
    GameManager gameManager;
    Player player;

    gameManager.runPlayerGame(player);

    return 0;
}