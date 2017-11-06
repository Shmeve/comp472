#include "NaivePlayer.h"
#include "Board.h"

int NaivePlayer::EvaluateHeuristic(const Board& board)
{
    int horizontalGreen = 0;
    int verticalGreen = 0;
    int horizontalRed = 0;
    int verticalRed = 0;

    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        int row = (i / BOARD_COLS) + 1;
        int col = (i % BOARD_COLS) + 1;
        switch (board.GetCell(i)) {
            case 0:
                break;
            case 1:
                horizontalGreen += row;
                verticalGreen += col;
                break;
            case 2:
                horizontalRed += row;
                verticalRed += col;
                break;
            default:
                // BAD
                return -1;
        };
    }

    return 100 * horizontalGreen + 50 * verticalGreen - 100 * horizontalRed - 50 * verticalRed;
}