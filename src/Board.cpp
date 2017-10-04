#include "Board.h"
#include "UI.h"

Board::Board() : mSize(BOARD_ROWS * BOARD_COLS)
{
    mCells = new int[mSize];

    SetCell(mSize / 2, 0);
    for (int i = 0; i < mSize / 2; i++)
    {
        SetCell(i, 1);
        SetCell(i + 1 + (mSize / 2), 2);
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
    SetCell(idx, 0);
}

void Board::Move(int from, int to)
{
    mCells[to] = mCells[from];
    mCells[from] = 0;
}

void Board::SetCell(const int& idx, const int& val)
{
	mCells[idx] = val;
	UI::getInstance()->setCell(idx / BOARD_COLS, idx % BOARD_COLS, val);
}
