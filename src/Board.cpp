#include "Board.h"

Board::Board()
{
    mSize = 1;
    mCells = new int[1];
}

Board::Board(int size)
{
    mSize = size;
    mCells = new int[mSize];

    mCells[mSize / 2] = 0;
    for (int i = 0; i < mSize / 2; i++)
    {
        mCells[i] = 1;
        mCells[i + 1 + (mSize / 2)] = 2;
    }
}

Board::~Board()
{
    delete mCells;
}

int Board::GetPlayer(int idx)
{
    if (idx < 0 || idx > mSize)
        return 0;
    return mCells[idx];
}

void Board::Clear(int idx)
{
    mCells[idx] = 0;
}

void Board::MoveTo(int from, int to)
{
    mCells[to] = mCells[from];
    mCells[from] = 0;
}