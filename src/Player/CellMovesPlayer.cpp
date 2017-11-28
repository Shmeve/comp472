#include "CellMovesPlayer.h"
#include "Board.h"

#include <stdexcept>

int CellMovesPlayer::EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth)
{
    int result = 0;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            switch (board.GetCell(r * BOARD_COLS + c)) {
            case 1:
                result += (board.IsBlack(r * BOARD_COLS + c) ? 6 : 4);
                break;
            case 2:
                result -= (board.IsBlack(r * BOARD_COLS + c) ? 6 : 4);
                break;
            default:
                break;
            };
        }
    }

    return result;
}