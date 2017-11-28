#include "RemainingTilesPlayer.h"
#include "Board.h"

int RemainingTilesPlayer::EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth)
{
    int value = 0;
    for (idx_t i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        if (board.GetCell(i) == 2) {
            value++;
        }
    }

    return value;
}