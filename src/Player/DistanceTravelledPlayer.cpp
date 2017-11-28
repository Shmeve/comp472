#include "DistanceTravelledPlayer.h"
#include "Board.h"

int8_t score[2][5] = { {50, 40, 30, 20, 10}, {10, 20, 30, 40, 50} };

int DistanceTravelledPlayer::EvaluateHeuristic(const Board& board)
{
    int result = 0;
    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        switch (board.GetCell(i)) {
        case 1:
            result += score[0][i % 8];
            break;
        case 2:
            result -= score[1][i % 8];
            break;
        }
    }

    return result;
}