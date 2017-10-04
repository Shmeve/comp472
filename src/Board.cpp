#include "Board.h"
#include "UI.h"

Board::Board() : mSize(BOARD_ROWS * BOARD_COLS)
{
    mCells = new int[mSize];

    SetCell(mSize / 2, 0); // middle cell is empty
    for (int i = 0; i < mSize; ++i)
    {
        int row = i / BOARD_COLS, col = i % BOARD_COLS;

        if (row < BOARD_ROWS / 2) {
            // player 1 rows
            SetCell(i, 1);
        } else if (row == BOARD_ROWS / 2 && col != BOARD_COLS / 2) {
            // middle row -- first half is player 2, 2nd half is player 1
            SetCell(i, 1 + (col < BOARD_COLS / 2));
        } else if (row > BOARD_ROWS / 2) {
            // player 2 rows
            SetCell(i, 2);
        }
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
    SetCell(to, mCells[from]);
    SetCell(from, 0);
}

void Board::SetCell(const int& idx, const int& val)
{
	mCells[idx] = val;
	UI::getInstance()->setCell(idx / BOARD_COLS, idx % BOARD_COLS, val);
}
