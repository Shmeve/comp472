#include "OthelloPlayer.h"
#include "Board.h"

int8_t weight[45] = { +4, -3, +2, +2, +2, +2, +2, -3, +4,
                      -3, -4, -1,  0, -1,  0, -1, -4, -3,
                      +2, -1,  0, +1,  0, +1,  0, -1, +2,
                      -3, -4, -1,  0, -1,  0, -1, -4, -3,
                      +4, -3, +2, +2, +2, +2, +2, -3, +4 };

int OthelloPlayer::EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth)
{
    int result = 0;
    int factor = 0;
    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        switch (board.GetCell(i)) {
            case 0:
                factor = 0;
                break;
            case 1:
                factor = 1;
                break;
            case 2:
                factor = -1;
                break;
        }
        result += factor * weight[i];
    }

    return result;
}