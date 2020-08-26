#include "game_manager.h"
#include "player.h"

GameManager::GameManager() : mGraphicEngine(mTetrisGrid)
{
    mUpdateTimer.restart();
}

int GameManager::keyToAction(Key& keysPressed)
{
    int action = 0;
    if (keysPressed.gauche)
    {
        action = 1;
    }
    else if (keysPressed.droite)
    {
        action = 2;
    }
    else if (keysPressed.haut)
    {
        action = 3;
    }
    else if (keysPressed.bas)
    {
        action = 4;
    }
    return action;    
}

void GameManager::runPlayerGame(Player player)
{
    srand(time(NULL));
    mGameSpeed = GAME_SPEED_INITIAL;
    sf::Event event;
    bool isGameLost = false;

    while (mGraphicEngine.mWindow.isOpen() && !isGameLost)
    {
        while (mGraphicEngine.mWindow.pollEvent(event))
        {   
            Key& keysPressed = player.getKeyPressed(event);
            if (keysPressed.esc) mGraphicEngine.mWindow.close();
            mTetrisGrid.receiveAction(keyToAction(keysPressed));
        }

        mGameSpeed = GAME_SPEED_INITIAL * pow(GAME_SPEED_RATE, mTetrisGrid.score()/GAME_SPEED_UPDATE);
        if (mUpdateTimer.getElapsedTime().asSeconds() > mGameSpeed)
        {
            mUpdateTimer.restart();
            isGameLost = mTetrisGrid.update();
        }

        if (isGameLost) std::cout << "Enorme defaite, score : " << std::to_string(mTetrisGrid.score()) << std::endl;
        mGraphicEngine.render();
    }
}