#include "NeighborPlayer.h"
#include "Board.h"

#include <stdexcept>

int NeighborPlayer::EvaluateHeuristic(const Board& board)
{
    int result = 0;

    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        switch (board.GetCell(i)) {
        case 1:
            if ((i % 9 != 0) && (i / 9 != 0)) {
                result -= (board.GetCell(i - BOARD_COLS - 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 8) && (i / 9 != 0)) {
                result -= (board.GetCell(i - BOARD_COLS + 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 0) && (i / 9 != 4)) {
                result -= (board.GetCell(i + BOARD_COLS - 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 8) && (i / 9 != 4)) {
                result -= (board.GetCell(i + BOARD_COLS + 1) == 1) ? -1 : 1;
            }
            else if (i % 9 != 0) {
                result += (board.GetCell(i - 1) == 1) ? -1 : 1;
            }
            else if (i % 9 != 8) {
                result -= (board.GetCell(i + 1) == 1) ? -1 : 1;
            }
            else if (i / 9 != 0) {
                result -= (board.GetCell(i - BOARD_COLS) == 1) ? -1 : 1;
            }
            else if (i / 9 != 4) {
                result -= (board.GetCell(i + BOARD_COLS) == 1) ? -1 : 1;
            }
            break;
        case 2:
            if ((i % 9 != 0) && (i / 9 != 0)) {
                result += (board.GetCell(i - BOARD_COLS - 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 8) && (i / 9 != 0)) {
                result += (board.GetCell(i - BOARD_COLS + 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 0) && (i / 9 != 4)) {
                result += (board.GetCell(i + BOARD_COLS - 1) == 1) ? -1 : 1;
            }
            else if ((i % 9 != 8) && (i / 9 != 4)) {
                result += (board.GetCell(i + BOARD_COLS + 1) == 1) ? -1 : 1;
            }
            else if (i % 9 != 0) {
                result += (board.GetCell(i - 1) == 1) ? -1 : 1;
            }
            else if (i % 9 != 8) {
                result += (board.GetCell(i + 1) == 1) ? -1 : 1;
            }
            else if (i / 9 != 0) {
                result += (board.GetCell(i - BOARD_COLS) == 1) ? -1 : 1;
            }
            else if (i / 9 != 4) {
                result += (board.GetCell(i + BOARD_COLS) == 1) ? -1 : 1;
            }
            break;
        }
    }

    return result;
}