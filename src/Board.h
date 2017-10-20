#pragma once

#include <cstdint>

#define BOARD_ROWS 5
#define BOARD_COLS 9

class Board
{
private:
    uint8_t* mCells;
    const unsigned int mSize = BOARD_ROWS * BOARD_COLS;
public:
    Board();
    Board(const Board& other);
    Board(Board&& other) noexcept;
    ~Board() noexcept;
    Board& operator=(const Board& other);
    Board& operator=(Board&& other) noexcept;

    inline bool IsBlack(const int& idx) { return idx % 2 == 0; }
    int GetPlayer(const int& idx);
    void Clear(const int& idx);
    void Move(const int& from, const int& to);
    void SetCell(const int& idx, const int& val);
};