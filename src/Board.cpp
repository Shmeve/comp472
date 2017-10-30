#include "Board.h"
#include "UI.h"

#include <cstdlib>
#include <cstring>

Board::Board(bool ui)
{
    mCells = new int[mSize];
    mUpdateUI = ui;

    SetCell(mSize / 2, 0); // middle cell is empty
    for (unsigned int i = 0; i < mSize; ++i)
    {
        int row = i / BOARD_COLS, col = i % BOARD_COLS;

        if (row < BOARD_ROWS / 2) {
            // player 2 rows
            SetCell(i, 2);
        } else if (row == BOARD_ROWS / 2 && col != BOARD_COLS / 2) {
            // middle row -- first half is player 1, 2nd half is player 2
            SetCell(i, 1 + (col > BOARD_COLS / 2));
        } else if (row > BOARD_ROWS / 2) {
            // player 1 rows
            SetCell(i, 1);
        }
    }
}

Board::Board(const Board& other)
{
    mCells = new int[mSize];
    memcpy(mCells, other.mCells, mSize*sizeof(int));
    mUpdateUI = other.mUpdateUI;
}

Board::~Board()
{
    delete mCells;
}

Board::Board(Board&& other) noexcept : mCells(other.mCells), mUpdateUI(other.mUpdateUI)
{
    other.mCells = nullptr;
}

Board& Board::operator=(const Board& other)
{
    Board tmp(other);
    *this = std::move(tmp);
    return *this;
}

Board& Board::operator=(Board&& other) noexcept
{
    mCells = other.mCells;
    other.mCells = nullptr;
    mUpdateUI = other.mUpdateUI;
    return *this;
}

int Board::GetPlayer(unsigned int idx)
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
    if (mUpdateUI)
        UI::getInstance()->setCell(idx / BOARD_COLS, idx % BOARD_COLS, val);
}
