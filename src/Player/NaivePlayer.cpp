#include "NaivePlayer.h"
#include "Board.h"

int NaivePlayer::EvaluateHeuristic(const Board& board)
{
    int result = 0;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            switch (board.GetCell(r * BOARD_COLS + c)) {
                case 1:
                    result += 100 * (r + 1);
                    result += 50 * (c + 1);
                    break;
                case 2:
                    result -= 100 * (r + 1);
                    result -= 50 * (c + 1);
                    break;
                default:
                    break;
            };
        }
    }

    return result;
}