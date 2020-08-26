#ifndef GRID_H
#define GRID_H

#include <cstdlib>
#include <iostream>
#include <vector>

const int TETRI_BLOCKS(4);
const int GRID_HEIGHT(22);
const int GRID_WIDTH(10);

enum Colors {gray, violet, yellow, cyan, green, red, orange, blue, white};

class Tetrimino;
class Grid;


class Tetrimino
{
    public :
        static const std::vector<std::vector<int>> TETRIMINO_TYPES;                                
        
        Tetrimino(int color, int orientation);
        std::vector<int> getBulk() const;

        void clockwiseRotation();
        void goDown(); 
        void goUp();
        void goLeft(); 
        void goRight();

        const int& color() const {return mColor;}
        const int& x() const {return mX;}
        const int& y() const {return mY;}
        const std::vector<int>& composition() const {return mComposition;}

    private :
        int mColor;
        int mOrientation;
        int mX;
        int mY;
        std::vector<int> mComposition;

};


class Grid
{
    public :
        Grid();

        const std::vector<int>& grid() const {return mGrid;}
        const Tetrimino& currTetrimino() const {return mCurrTetrimino;}
        const Tetrimino& nextTetrimino() const {return mNextTetrimino;}
        const int& score() const {return mScore;}

        bool update();
        void receiveAction(int action);
        bool isGridBlocked() const;
        void goFloor();
        bool fixCurrTetrimino();
        bool isLineCompleted(int y) const;
        void deleteOneLine(int y);
        void deleteCompletedLines();

    private :
        Tetrimino mCurrTetrimino;
        Tetrimino mNextTetrimino;
        std::vector<int> mGrid;
        int mScore;
};

#endif