#include "Board.h"
#include "UI.h"

#include <cstdlib>
#include <cstring>

Board::Board(const bool& ui)
        : mUpdateUI(ui)
{
    mCells = new cell_t[BOARD_SIZE];

    SetCell(BOARD_SIZE / 2, 0); // middle cell is empty
    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
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
    mCells = new cell_t[BOARD_SIZE];
    memcpy(mCells, other.mCells, BOARD_SIZE * sizeof(cell_t));
    mUpdateUI = other.mUpdateUI;
}

Board::Board(Board&& other)
        : mCells(other.mCells), mUpdateUI(other.mUpdateUI)
{
    other.mCells = nullptr;
}

Board::~Board()
{
    delete mCells;
}

Board& Board::operator=(const Board& other)
{
    Board tmp(other);
    *this = std::move(tmp);
    return *this;
}

Board& Board::operator=(Board&& other)
{
    mCells = other.mCells;
    other.mCells = nullptr;
    mUpdateUI = other.mUpdateUI;
    return *this;
}

void Board::Clear(const idx_t& idx)
{
    SetCell(idx, 0);
}

void Board::Move(const idx_t& from, const idx_t& to)
{
    SetCell(to, mCells[from]);
    SetCell(from, 0);
}

void Board::SetCell(const idx_t& idx, const cell_t& val)
{
    mCells[idx] = val;

    if (mUpdateUI) {
        UI::getInstance()->setCell(idx / BOARD_COLS, idx % BOARD_COLS, val);
    }
}
