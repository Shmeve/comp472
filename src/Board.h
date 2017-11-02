#pragma once

#include <cstdint>

#define BOARD_ROWS 5
#define BOARD_COLS 9

typedef unsigned int idx_t;
typedef uint8_t cell_t;

class Board
{
private:
    uint8_t* mCells;
    const idx_t mSize = BOARD_ROWS * BOARD_COLS;
    bool mUpdateUI;
public:
    Board() : Board(true) {};
    explicit Board(const bool& ui);
    Board(const Board& other);
    Board(Board&& other) noexcept;
    ~Board() noexcept;
    Board& operator=(const Board& other);
    Board& operator=(Board&& other) noexcept;

    bool IsBlack(const idx_t& idx) { return idx % 2 == 0; }
    int GetCell(const idx_t& idx);
    void Clear(const idx_t& idx);
    void Move(const idx_t& from, const idx_t& to);
    void SetCell(const idx_t& idx, const uint8_t& val);
    void SetUI(const bool& ui) { mUpdateUI = ui; };
};