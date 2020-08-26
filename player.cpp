#include "player.h"

Player::Player()
{
    mKey.gauche = false;
    mKey.droite = false;
    mKey.haut = false;
    mKey.bas = false;
    mKey.esc = false;
}

Key& Player::getKeyPressed(sf::Event event)
{
    switch (event.type)
    {
        case sf::Event::KeyPressed :
        
            if (event.key.code == sf::Keyboard::Up)
                mKey.haut = true;
            
            else if (event.key.code == sf::Keyboard::Down)
                mKey.bas = true;
        
            else if (event.key.code == sf::Keyboard::Left)
                mKey.gauche = true;

            else if (event.key.code == sf::Keyboard::Right)
                mKey.droite = true;
            
            else if (event.key.code == sf::Keyboard::Escape)
                mKey.esc = true;
            break;
    
        case sf::Event::KeyReleased :
            if (event.key.code == sf::Keyboard::Up)
                mKey.haut = false;

            else if (event.key.code == sf::Keyboard::Down)
                mKey.bas = false;

            else if (event.key.code == sf::Keyboard::Left)
                mKey.gauche = false;

            else if (event.key.code == sf::Keyboard::Right)
                mKey.droite = false;

            else if (event.key.code == sf::Keyboard::Escape)
                mKey.esc = false;
            break;
        
        default :
            break;
    }
    return mKey;
}