#include "BestPathPlayer.h"
#include "Board.h"

#include <stdexcept>

int BestPathPlayer::EvaluateHeuristic(const Board& board)
{
    int lateralGreen = 0;
    int lateralRed = 0;
    int diagonalGreen = 0;
    int diagonalRed = 0;

    for (idx_t i = 0; i < BOARD_SIZE; ++i) {
        int row = (i / BOARD_COLS) + 1;
        int col = (i % BOARD_COLS) + 1;
        int tmp = 0;
        switch (board.GetCell(i)) {
            case 0:
                break;
            case 1: // GREEN
                for (int j = 0; j < BOARD_ROWS; ++j) { // UP AND DOWN
                    if (j != row) {
                        switch (board.GetCell(j*BOARD_COLS + col)) {
                            case 0:
                            case 1:
                                break;
                            case 2:
                                ++lateralRed;
                                break;
                        }
                    }
                }
                for (int j = 0; j < BOARD_COLS; ++j) { // LEFT AND RIGHT
                    if (j != col) {
                        switch (board.GetCell(row*BOARD_COLS + j)) {
                            case 0:
                            case 1:
                                break;
                            case 2:
                                ++lateralRed;
                                break;
                        }
                    }
                }

                if (board.IsBlack(row*BOARD_COLS + col)) { // DIAGONAL
                    for (idx_t j = 0; j < 4; ++j) {
                        int tmpRow = row;
                        int tmpCol = col;

                        int rowThreshold = (j < 2) ? 0 : BOARD_ROWS;
                        int colThreshold = (j % 3 == 0) ? 0 : BOARD_COLS;
                        while (tmpRow != rowThreshold && tmpCol != colThreshold) {
                            (j < 2) ? --tmpRow : ++tmpRow;
                            (j % 3 == 0) ? --tmpCol : ++tmpCol;
                            switch (board.GetCell(tmpRow*BOARD_COLS + tmpCol)) {
                                case 0:
                                case 1:
                                    break;
                                case 2:
                                    ++diagonalRed;
                                    break;
                            }
                        }
                    }
                }

                break;
            case 2: // RED
                for (int j = 0; j < BOARD_ROWS; ++j) { // UP AND DOWN
                    if (j != row) {
                        switch (board.GetCell(j*BOARD_COLS + col)) {
                            case 0:
                            case 2:
                                break;
                            case 1:
                                ++lateralGreen;
                                break;
                        }
                    }
                }
                for (int j = 0; j < BOARD_COLS; ++j) { // LEFT AND RIGHT
                    if (j != col) {
                        switch (board.GetCell(row*BOARD_COLS + j)) {
                            case 0:
                            case 2:
                                break;
                            case 1:
                                ++lateralGreen;
                                break;
                        }
                    }
                }

                if (board.IsBlack(row*BOARD_COLS + col)) { // DIAGONAL
                    for (idx_t j = 0; j < 4; ++j) {
                        int tmpRow = row;
                        int tmpCol = col;

                        int rowThreshold = (j < 2) ? 0 : BOARD_ROWS;
                        int colThreshold = (j % 3 == 0) ? 0 : BOARD_COLS;
                        while (tmpRow != rowThreshold && tmpCol != colThreshold) {
                            (j < 2) ? --tmpRow : ++tmpRow;
                            (j % 3 == 0) ? --tmpCol : ++tmpCol;
                            switch (board.GetCell(tmpRow*BOARD_COLS + tmpCol)) {
                                case 0:
                                case 2:
                                    break;
                                case 1:
                                    ++diagonalGreen;
                                    break;
                            }
                        }
                    }
                }

                break;
        }
    }

    return 10 * lateralGreen - 10 * lateralRed + 15 * diagonalGreen - 15 * diagonalRed;
}