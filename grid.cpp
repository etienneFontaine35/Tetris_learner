#include "grid.h"

//---------------------------------
//      class TETRIMINO
//---------------------------------

const std::vector<std::vector<int>> Tetrimino::TETRIMINO_TYPES ({{0, 0, -1, 0, 1, 0, 0, 1},
                                                                 {0, 0, 1, 0, 0, 1, 1, 1},
                                                                 {0, 0, 0, -1, 0, 1, 0, 2},
                                                                 {0, 0, 1, 0, -1, 1, 0, 1},
                                                                 {0, 0, -1, 0, 0, 1, 1, 1},
                                                                 {0, 0, 0, -2, 0, -1, 1, 0},
                                                                 {0, 0, 0, -2, 0, -1, -1, 0}});

Tetrimino::Tetrimino(int color, int orientation) : mColor(color), mOrientation(0)
{
    mComposition = TETRIMINO_TYPES[color];
    while (mOrientation != orientation)
    {
        clockwiseRotation();
    }    
    mX = GRID_WIDTH / 2;
    mY = -(1 + getBulk()[3]);
}

void Tetrimino::clockwiseRotation()
{
    int x_prev, y_prev;
    for (int i = 0; i < TETRI_BLOCKS; i++)
    {
        x_prev = mComposition[2*i+0];
        y_prev = mComposition[2*i+1];
        mComposition[2*i+0] = y_prev;
        mComposition[2*i+1] = -x_prev;
    }
    mOrientation = (mOrientation + 1) % 4;
}


void Tetrimino::goDown()
{
    mY++;
}

void Tetrimino::goUp()
{
    mY--;
}

void Tetrimino::goLeft()
{
    mX--;
}


void Tetrimino::goRight()
{
    mX++;
}


std::vector<int> Tetrimino::getBulk() const
{
    int x_min = 0, y_min = 0, x_max = 0, y_max = 0;
    int x, y;
    for (int i = 0; i < TETRI_BLOCKS; i++)
    {
        x = mComposition[2*i+0];
        y = mComposition[2*i+1];
        if (x < x_min)
        {
            x_min = x;
        }
 
        else if (x > x_max)
        {
            x_max = x;
        }

        if (y < y_min)
        {
            y_min = y;
        }

        else if (y > y_max)
        {
            y_max = y;
        }
    }
    return std::vector<int> {x_min, x_max, y_min, y_max};
}


//---------------------------------
//      class GRID
//---------------------------------

Grid::Grid() : mCurrTetrimino(rand() % Tetrimino::TETRIMINO_TYPES.size(), rand() % 4), mNextTetrimino(rand() % Tetrimino::TETRIMINO_TYPES.size(), rand() % 4), mGrid(GRID_HEIGHT*GRID_WIDTH, 0), mScore(0)
{

}

bool Grid::update()
{
    bool endgame(false);
    if (isGridBlocked())
    {
        endgame = fixCurrTetrimino();
    }
    else
    {
        mCurrTetrimino.goDown();
    }
    deleteCompletedLines();
    return endgame;
}

void Grid::receiveAction(int action)
{
    switch (action)
    {
        case 1 :
            if (mCurrTetrimino.getBulk()[0] + mCurrTetrimino.x() > 0)
            {
                mCurrTetrimino.goLeft();
            }
            break;

        case 2 :
            if (mCurrTetrimino.getBulk()[1] + mCurrTetrimino.x() < GRID_WIDTH - 1)
            {
                mCurrTetrimino.goRight();
            }
            break;
        
        case 3 :
            if (!isGridBlocked())
            {
                mCurrTetrimino.clockwiseRotation();
            }
            while (mCurrTetrimino.getBulk()[0] + mCurrTetrimino.x() < 0)
            {
                mCurrTetrimino.goRight();
            }
            while (mCurrTetrimino.getBulk()[1] + mCurrTetrimino.x() > GRID_WIDTH - 1)
            {
                mCurrTetrimino.goLeft();
            }
            while (isGridBlocked())
            {
                mCurrTetrimino.goUp();
            }
            mCurrTetrimino.goDown();
            break;
        
        case 4 :
            goFloor();
            break;
    }
}

bool Grid::isGridBlocked() const
{
    bool blocked = false;
    for (int i = 0; i < TETRI_BLOCKS; i++)
    {
        int x_currBlock = mCurrTetrimino.x() + mCurrTetrimino.composition()[2*i+0];
        int y_currBlock = mCurrTetrimino.y() + mCurrTetrimino.composition()[2*i+1];

        if (y_currBlock == GRID_HEIGHT - 1)
        {
            blocked = true;
        }
        else if (GRID_WIDTH*(y_currBlock+1)+x_currBlock > -1 && GRID_WIDTH*(y_currBlock+1)+x_currBlock < GRID_HEIGHT*GRID_WIDTH)
        {
            if (mGrid[GRID_WIDTH*(y_currBlock+1)+x_currBlock])
                blocked = true;
        }
    }
    return blocked;
}

void Grid::goFloor()
{
    while (!isGridBlocked())
    {
        mCurrTetrimino.goDown();
    }
}

bool Grid::fixCurrTetrimino()
{
    bool endgame = false;
    for (int i = 0; i < TETRI_BLOCKS; i++)
    {
        int x_currBlock = mCurrTetrimino.x() + mCurrTetrimino.composition()[2*i+0];
        int y_currBlock = mCurrTetrimino.y() + mCurrTetrimino.composition()[2*i+1];
        if (y_currBlock < 0)
            endgame = true;
        mGrid[GRID_WIDTH*y_currBlock+x_currBlock] = mCurrTetrimino.color() + 1;
    }
    mCurrTetrimino = mNextTetrimino;
    mNextTetrimino = Tetrimino(rand() % Tetrimino::TETRIMINO_TYPES.size(), rand() % 4);
    return endgame;
}

bool Grid::isLineCompleted(int y) const
{
    bool isCompletedLine = true;
    for (int x = 0; x < GRID_WIDTH; x++)
    {
        if (mGrid[y*GRID_WIDTH+x] == 0)
            isCompletedLine = false;
    }
    return isCompletedLine;
}

void Grid::deleteOneLine(int y)
{
    for (int yBis = y-1; yBis >= 0; yBis--)
    {
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            mGrid[(yBis+1)*GRID_WIDTH+x] = mGrid[(yBis)*GRID_WIDTH+x];
        }
    }
    mScore++;
}

void Grid::deleteCompletedLines()
{
    for (int i = 0; i < GRID_HEIGHT; i++)
    {
        if (isLineCompleted(i))
            deleteOneLine(i);
    }
}