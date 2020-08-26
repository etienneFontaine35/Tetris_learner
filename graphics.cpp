#include "graphics.h"

//---------------------------------
//      class DISPLAY
//---------------------------------

const std::vector<sf::Color> Display::COLORS({sf::Color(150,150,150), // Gray
                                              sf::Color(186,85,211),  // Purple
                                              sf::Color::Yellow,      // Yellow
                                              sf::Color::Cyan,        // Cyan
                                              sf::Color::Green,       // Green
                                              sf::Color::Red,         // Red
                                              sf::Color(255,165,0),   // Orange
                                              sf::Color::Blue,        // Blue
                                              sf::Color::White,
                                            });

Display::Display(Grid& playingGrid) : mWindow(sf::VideoMode(17 * TILE_SIZE, 22 * TILE_SIZE), "Tetris Learner", sf::Style::Titlebar | sf::Style::Close),
                                      mPlayingGrid(playingGrid),
                                      mTileSprite(sf::Vector2f(TILE_SIZE, TILE_SIZE))
{
    mWindow.setFramerateLimit(FRAMERATE);
    mTileSprite.setFillColor(COLORS[0]);
    mTileSprite.setOutlineThickness(-LINE_WIDTH);
    mTileSprite.setOutlineColor(COLORS[0]);
    if (!mFont.loadFromFile("Arial.ttf"))
    {
        std::cout << "error when loading Arial font file" << std::endl;
    }
    mText.setFont(mFont);
}


void Display::render()
{
    mWindow.clear(sf::Color::Black);
    displayCurrTetrimino();
    displayNextTetrimino();
    displayInterface();
    displayGrid();
    mWindow.display();
}

void Display::displayCurrTetrimino()
{
    const Tetrimino& currT(mPlayingGrid.currTetrimino());
    mTileSprite.setFillColor(COLORS[currT.color()+1]);
    for (int i = 0; i < TETRI_BLOCKS*2; i+=2)
    {
        int x = TILE_SIZE * (currT.x() + currT.composition()[i]);
        int y = TILE_SIZE * (currT.y() + currT.composition()[i+1]);
        mTileSprite.setPosition(x, y);
        mWindow.draw(mTileSprite);
    }
}

void Display::displayNextTetrimino()
{
    const Tetrimino& nextT(mPlayingGrid.nextTetrimino());
    mTileSprite.setFillColor(COLORS[nextT.color()+1]);
    for (int i = 0; i < TETRI_BLOCKS*2; i+=2)
    {
        int x = TILE_SIZE * (13 + nextT.composition()[i]);
        int y = TILE_SIZE * (5 + nextT.composition()[i+1]);
        mTileSprite.setPosition(x, y);
        mWindow.draw(mTileSprite);
    }
}

void Display::displayInterface()
{
    mText.setFillColor(COLORS[white]);
    mText.setString("Next Tetrimino");
    mText.setCharacterSize(0.7*TILE_SIZE);
    mText.setPosition(int((GRID_WIDTH+1.25) * TILE_SIZE), 2*TILE_SIZE);
    mWindow.draw(mText);

    mText.setString("Score : " + std::to_string(mPlayingGrid.score()));
    mText.setCharacterSize(TILE_SIZE);
    mText.setPosition(int((GRID_WIDTH+1.25) * TILE_SIZE), 10*TILE_SIZE);
    mWindow.draw(mText);

    // inside lines
    mGridLine.setSize(sf::Vector2f(TILE_SIZE*GRID_WIDTH, 2*LINE_WIDTH));
    mGridLine.setFillColor(COLORS[gray]);
    for (int i = 1; i < GRID_HEIGHT; i++)
    {
        mGridLine.setPosition(0, TILE_SIZE*i - LINE_WIDTH);
        mWindow.draw(mGridLine);
    }

    mGridLine.setSize(sf::Vector2f(2*LINE_WIDTH, TILE_SIZE*GRID_HEIGHT));
    for (int i = 1; i < GRID_WIDTH; i++)
    {
        mGridLine.setPosition(TILE_SIZE*i - LINE_WIDTH, 0);
        mWindow.draw(mGridLine);
    }

    // outside lines
    mGridLine.setFillColor(COLORS[white]);
    mGridLine.setPosition(-LINE_WIDTH, 0);
    mWindow.draw(mGridLine);
    mGridLine.setPosition( TILE_SIZE*GRID_WIDTH - LINE_WIDTH, 0);
    mWindow.draw(mGridLine);

    mGridLine.setSize(sf::Vector2f(TILE_SIZE*GRID_WIDTH, 2*LINE_WIDTH));
    mGridLine.setPosition(0, -LINE_WIDTH);
    mWindow.draw(mGridLine);
    mGridLine.setPosition(0, TILE_SIZE*GRID_HEIGHT - LINE_WIDTH);
    mWindow.draw(mGridLine);

    // next tetrimino frame
    mGridLine.setFillColor(COLORS[gray]);
    mGridLine.setSize(sf::Vector2f(TILE_SIZE*5, 2*LINE_WIDTH));
    mGridLine.setPosition((GRID_WIDTH+1) * TILE_SIZE, 3*TILE_SIZE-1);
    mWindow.draw(mGridLine);
    mGridLine.setPosition((GRID_WIDTH+1) * TILE_SIZE, 8*TILE_SIZE-1);
    mWindow.draw(mGridLine);
    mGridLine.setSize(sf::Vector2f(2*LINE_WIDTH, TILE_SIZE*5));
    mGridLine.setPosition((GRID_WIDTH+1) * TILE_SIZE, 3*TILE_SIZE-1);
    mWindow.draw(mGridLine);
    mGridLine.setPosition((GRID_WIDTH+6) * TILE_SIZE, 3*TILE_SIZE-1);
    mWindow.draw(mGridLine);
}

void Display::displayGrid()
{
    const std::vector<int>& grid(mPlayingGrid.grid());
    for (int j = 0; j < GRID_HEIGHT; j++)
    {
        for (int i = 0; i < GRID_WIDTH; i++)
        {
            int blockType = grid[GRID_WIDTH*j + i];
            if (blockType)
            {
                mTileSprite.setFillColor(COLORS[blockType]);
                mTileSprite.setPosition(i*TILE_SIZE, j*TILE_SIZE);
                mWindow.draw(mTileSprite);
            }
        }
    }
}