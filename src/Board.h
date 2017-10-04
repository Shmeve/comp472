#pragma once

#define BOARD_ROWS 5
#define BOARD_COLS 9

class Board
{
private:
    int* mCells;
    const int mSize;
public:
    Board();
    ~Board();
    inline int* GetCells() { return mCells; }
    inline bool IsBlack(int idx) { return idx % 2 == 0; }
    int GetPlayer(int idx);
    void Clear(int idx);
    void Move(int from, int to);
};