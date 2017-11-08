#include "CornerCellPlayer.h"
#include "Board.h"

#include <stdexcept>

int CornerCellPlayer::EvaluateHeuristic(const Board& board)
{
    int result = 0;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            switch (board.GetCell(r * BOARD_COLS + c)) {
            case 1:
                if (!(c & 0x07)) {
                    if (!(r & 0x03)) {
                        result += 1; // CORNER
                    } else {
                        result += (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // FIRST OR LAST COLUMN
                    }
                } else {
                    if (!(r & 0x03)) {
                        result += (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // TOP OR BOTTOM ROW
                    } else {
                        result += (board.IsBlack(r * BOARD_COLS + c) ? 8 : 4); // CENTER AREA
                    }
                }
                break;
            case 2:
                if (!(c & 0x07)) {
                    if (!(r & 0x03)) {
                        result -= 1; // CORNER
                    }
                    else {
                        result -= (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // FIRST OR LAST COLUMN
                    }
                }
                else {
                    if (!(r & 0x03)) {
                        result -= (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // TOP OR BOTTOM ROW
                    }
                    else {
                        result -= (board.IsBlack(r * BOARD_COLS + c) ? 8 : 4); // CENTER AREA
                    }
                }
                break;
            default:
                break;
            };
        }
    }

    return result;
}