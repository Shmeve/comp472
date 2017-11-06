#include "RemainingTilesPlayer.h"
#include "Board.h"

int RemainingTilesPlayer::EvaluateHeuristic(const Board& board)
{
    int value = 0;
    for (idx_t i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        if (board.GetCell(i) == 2) {
            value++;
        }
    }

    return value;
}