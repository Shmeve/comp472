#include "MOAHPlayer.h"
#include "Board.h"
#include "GameManager.h"

#include <cmath>

const int moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

int MOAHPlayer::EvaluateHeuristic(const Board& board)
{
    auto gameManager = GameManager::GetInstance();

    int result = 0;

    // corner heuristic
    //int greenCornerScore = 0;
    //int redCornerScore = 0;

    // moves heuristic
    int greenAttackMoves = 0;
    //int greenAttackPiecesEliminated = 0;
    //int greenAttackMaxPiecesEliminated = 0;
    //int greenNoopMoves = 0;
    //int redAttackMoves = 0;
    //int redAttackPiecesEliminated = 0;
    //int redAttackMaxPiecesEliminated = 0;
    int redNoopMoves = 0;
    //int greenPossibleMoves = 0;
    //int redPossibleMoves = 0;

    // remaining tiles heuristic
    int greenPiecesLeft = 0;
    int redPiecesLeft = 0;
    //int greenPiecesOnBlack = 0;
    //int redPiecesOnBlack = 0;

    // clustering heuristic
    //int greenMaxCol = 0;
    //int greenMaxRow = 0;
    //int greenMinCol = BOARD_COLS - 1;
    //int greenMinRow = BOARD_ROWS - 1;
    //int redMaxCol = 0;
    //int redMaxRow = 0;
    //int redMinCol = BOARD_COLS - 1;
    //int redMinRow = BOARD_ROWS - 1;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            auto k = r * BOARD_COLS + c;
            auto cell = board.GetCell(k);
            //auto isBlack = board.IsBlack(k);
            auto isPlayerOne = cell == 1;

            if (cell != 0) {

                switch (cell) {
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
                }

                /*
                * Corner cell
                */

                /*
                if (isPlayerOne) {
                    if (!(c & 0x07)) {
                        if (!(r & 0x03)) {
                            greenCornerScore += 1; // CORNER
                        } else {
                            greenCornerScore += (isBlack ? 5 : 3); // FIRST OR LAST COLUMN
                        }
                    } else {
                        if (!(r & 0x03)) {
                            greenCornerScore += (isBlack ? 5 : 3); // TOP OR BOTTOM ROW
                        } else {
                            greenCornerScore += (isBlack ? 8 : 4); // CENTER AREA
                        }
                    }
                    ++greenPiecesLeft;
                    if (isBlack) {
                        ++greenPiecesOnBlack;
                    }

                    // clustering
                    if (r > greenMaxRow) {
                        greenMaxRow = r;
                    }

                    if (r < greenMinRow) {
                        greenMinRow = r;
                    }

                    if (c > greenMaxCol) {
                        greenMaxCol = c;
                    }

                    if (c < greenMinCol) {
                        greenMinCol = c;
                    }
                } else {
                    if (!(c & 0x07)) {
                        if (!(r & 0x03)) {
                            redCornerScore -= 1; // CORNER
                        } else {
                            redCornerScore -= (isBlack ? 5 : 3); // FIRST OR LAST COLUMN
                        }
                    } else {
                        if (!(r & 0x03)) {
                            redCornerScore -= (isBlack ? 5 : 3); // TOP OR BOTTOM ROW
                        } else {
                            redCornerScore -= (isBlack ? 8 : 4); // CENTER AREA
                        }
                    }
                    ++redPiecesLeft;
                    if (isBlack) {
                        ++redPiecesOnBlack;
                    }

                    // clustering
                    if (r > redMaxRow) {
                        redMaxRow = r;
                    }

                    if (r < redMinRow) {
                        redMinRow = r;
                    }

                    if (c > redMaxCol) {
                        redMaxCol = c;
                    }

                    if (c < redMinCol) {
                        redMinCol = c;
                    }
                }
                 */

                /*
                * Attack/defense
                */

                for (const auto& i : moves) {
                    Move move = Move(k, k + i);

                    if (!gameManager->IsValidMove(board, move, isPlayerOne)) {
                        continue;
                    }

                    Board tmp = board;
                    int attack = gameManager->Attack(tmp, Move(k, k + i), isPlayerOne + 1, true);

                    if (isPlayerOne) {
                        ++greenAttackMoves;
                    } else if (attack == 0) {
                        ++redNoopMoves;
                    }

                    /*
                    if (isPlayerOne) {
                        //greenAttackPiecesEliminated += attack;

                        //if (attack == 0) {
                        //    ++greenNoopMoves;
                        //} else {
                        //    if (attack > greenAttackMaxPiecesEliminated) {
                        //        greenAttackMaxPiecesEliminated = attack;
                        //    }
                            ++greenAttackMoves;
                        //}
                    } else {
                        //redAttackPiecesEliminated += attack;
                        //
                        if (attack == 0) {
                            ++redNoopMoves;
                        } else {
                            //if (attack > redAttackMaxPiecesEliminated) {
                            //    redAttackMaxPiecesEliminated = attack;
                            //}
                            //++redAttackMoves;
                        }
                    }
                     */
                }
            }
        }
    }

    return (
            200 * greenPiecesLeft +
            //0 * greenPiecesOnBlack +
            //0 * greenPossibleMoves +
            10 * greenAttackMoves +
            //0 * greenAttackMaxPiecesEliminated +
            //0 * greenNoopMoves +
            //0 * greenCornerScore +
            //0 * greenDeltaRow +
            //0 * greenDeltaCol +

            //0 * redDeltaCol +
            //0 * redDeltaRow +
            //0 * redCornerScore +
            5 * redNoopMoves +
            //0 * redAttackMaxPiecesEliminated +
            //0 * redAttackMoves +
            //0 * redPossibleMoves +
            //0 * redPiecesOnBlack +
            -100 * redPiecesLeft +

            result
    );

    // win against naive
    //return (
    //        100 * (greenPiecesLeft - redPiecesLeft) +
    //        50 * (greenPiecesOnBlack - redPiecesOnBlack) +
    //        30 * (greenAttackMoves) +
    //        -20 * (redAttackMoves) +
    //        //-15 * (greenNoopMoves) +
    //        0
    //);

    // win against corner
    //return (
    //        100 * (greenPiecesLeft - redPiecesLeft) +
    //        50 * (greenPiecesOnBlack - redPiecesOnBlack) +
    //        30 * (greenAttackMoves) +
    //        -20 * (redAttackMoves) +
    //        -10 * (greenNoopMoves + redNoopMoves) +
    //        0
    //);
}