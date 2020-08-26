#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "grid.h"

const int TILE_SIZE(40);
const int LINE_WIDTH(1);
const int FRAMERATE(60);


class Display
{
    public :
        static const std::vector<sf::Color> COLORS;
        Display(Grid& playingGrid);
        
        void render();
        void displayCurrTetrimino();
        void displayNextTetrimino();
        void displayInterface();
        void displayGrid();

        sf::RenderWindow mWindow;
        
    private :
        Grid& mPlayingGrid;
        sf::RectangleShape mTileSprite;
        sf::RectangleShape mGridLine;
        sf::Font mFont;
        sf::Text mText;
};

#endif