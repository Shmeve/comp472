#include "Board.h"
#include "UI.h"

#include <cstdlib>
#include <cstring>

Board::Board()
{
    mCells = (uint8_t*) malloc((mSize >> 2) + 1);

    SetCell(mSize / 2, 0); // middle cell is empty
    for (int i = 0; i < mSize; ++i) {
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

Board::Board(const Board& other)
{
    mCells = (uint8_t*) malloc((mSize >> 2) + 1);
    memcpy(mCells, other.mCells, (mSize >> 2) + 1);
}

Board::~Board() noexcept
{
    free(mCells);
}

Board::Board(Board&& other) noexcept : mCells(other.mCells)
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
    free(mCells);
    mCells = other.mCells;
    other.mCells = nullptr;
    return *this;
}

int Board::GetPlayer(const int& idx)
{
    if (idx < 0 || idx > mSize)
        return 0;

    uint8_t pos = idx & 3; // index 0-3 within the byte
    uint8_t mask = 0b11000000 >> (pos << 1); // bitmask for the position (right-shift 2*pos)
    unsigned int offset = idx >> 2; // offset within the board array

    return (mCells[offset] & mask) >> (6 - (pos << 1));
}

void Board::Clear(const int& idx)
{
    SetCell(idx, 0);
}

void Board::Move(const int& from, const int& to)
{
    SetCell(to, GetPlayer(from));
    SetCell(from, 0);
}

void Board::SetCell(const int& idx, const int& val)
{
    uint8_t pos = idx & 3; // index 0-3 within the byte
    uint8_t mask = 0b11000000 >> (pos << 1); // bitmask for the position (right-shift 2*pos)
    unsigned int offset = idx >> 2; // offset within the board array

    mCells[offset] = (mCells[offset] & ~mask) | ((val << (6 - (pos << 1))) & mask);

    UI::getInstance()->setCell(idx / BOARD_COLS, idx % BOARD_COLS, val);
}
