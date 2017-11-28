#include "BetterCornerCellPlayer.h"
#include "Board.h"

#include <stdexcept>

int BetterCornerCellPlayer::EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth)
{
    int result = 0;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            switch (board.GetCell(r * BOARD_COLS + c)) {
            case 1:
                if (!(c & 0x07)) {
                    if (!(r & 0x03)) {
                        result += 1; // CORNER
                    }
                    else {
                        result += (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // FIRST OR LAST COLUMN
                    }
                }
                else {
                    if (!(r & 0x03)) {
                        result += (board.IsBlack(r * BOARD_COLS + c) ? 5 : 3); // TOP OR BOTTOM ROW
                    }
                    else {
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

    int green = 0, red = 0;
    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        switch (board.GetCell(i)) {
            case 1:
                green++;
                break;
            case 2:
                red++;
                break;
        }
    }

    if (count >= 10 || draw)
        result = std::numeric_limits<int>::min() + depth;

    if (abs(green-red) > 2) {
        if (red == 0) {
            result = std::numeric_limits<int>::max() - depth;
        } else if (green == 0) {
            result = std::numeric_limits<int>::min() + depth;
        } else if (green > red) {
            result += 100;
        } else {
            result -= 100;
        }
    }

    return result;
}