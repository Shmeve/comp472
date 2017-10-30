#include "NaivePlayer.h"

int NaivePlayer::EvaluateHeuristic(Board& board)
{
    int horizontalGreen = 0;
    int verticalGreen = 0;
    int horizontalRed = 0;
    int verticalRed = 0;

    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        int row = (i / 9) + 1;
        int col = (i % 9) + 1;
        switch (board.GetCells()[i]) {
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