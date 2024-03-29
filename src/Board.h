#pragma once

#include <cstdint>

#define BOARD_ROWS 5
#define BOARD_COLS 9
#define BOARD_SIZE (BOARD_ROWS * BOARD_COLS)

typedef uint8_t idx_t;
typedef uint8_t cell_t;

class Board
{
private:
    uint8_t* mCells;
    bool mUpdateUI;
public:
    Board() : Board(true) {};
    explicit Board(const bool& ui);
    Board(const Board& other);
    Board(Board&& other);
    ~Board();
    Board& operator=(const Board& other);
    Board& operator=(Board&& other);

    inline bool IsBlack(const idx_t& idx) const { return idx % 2 == 0; }
    inline int GetCell(const idx_t& idx) const
    {
        if (idx >= BOARD_SIZE) {
            return 0;
        }

        return mCells[idx];
    }
    void Clear(const idx_t& idx);
    void Move(const idx_t& from, const idx_t& to);
    void SetCell(const idx_t& idx, const cell_t& val);
    void SetUI(const bool& ui) { mUpdateUI = ui; };
};