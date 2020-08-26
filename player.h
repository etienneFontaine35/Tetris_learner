#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <iostream>
#include <SFML/Window.hpp>

struct Key
{ 
	bool gauche, droite, haut, bas,  esc;
};

class Player
{
    public :
        Player();
        Key& getKeyPressed(sf::Event event);

    private :
		Key mKey;
};

#endif