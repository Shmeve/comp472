#pragma once

#define BOARD_ROWS 5
#define BOARD_COLS 9

class Board
{
private:
    int* mCells;
    const unsigned int mSize = BOARD_ROWS * BOARD_COLS;

    bool mUpdateUI;
public:
    Board() {};
    Board(bool ui);
    Board(const Board& other);
    Board(Board&& other) noexcept;
    ~Board() noexcept;
    Board& operator=(const Board& other);
    Board& operator=(Board&& other) noexcept;

    inline int* GetCells() { return mCells; }
    inline bool IsBlack(int idx) { return idx % 2 == 0; }
    int GetPlayer(int idx);
    void Clear(int idx);
    void Move(int from, int to);
    void SetCell(const int& idx, const int& val);
    inline void SetUI(bool ui) { mUpdateUI = ui; };
};