#include "RemainingTilesPlayer.h"

int RemainingTilesPlayer::EvaluateHeuristic(Board& board)
{
    int value = 0;
    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        if (board.GetCells()[i] == 2) {
            value++;
        }
    }

    return value;
}