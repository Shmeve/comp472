#include "IDontKnowWhatImDoingPlayer.h"
#include "Board.h"
#include "GameManager.h"

#include <cmath>

const int moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

int IDontKnowWhatImDoingPlayer::EvaluateHeuristic(const Board& board)
{
    auto gameManager = GameManager::GetInstance();

    // corner heuristic
    int greenCornerScore = 0;
    int redCornerScore = 0;

    // moves heuristic
    int greenAttackMoves = 0;
    int greenAttackPiecesEliminated = 0;
    int greenAttackMaxPiecesEliminated = 0;
    int greenNoopMoves = 0;
    int redAttackMoves = 0;
    int redAttackPiecesEliminated = 0;
    int redAttackMaxPiecesEliminated = 0;
    int redNoopMoves = 0;
    int greenPossibleMoves = 0;
    int redPossibleMoves = 0;

    // remaining tiles heuristic
    int greenPiecesLeft = 0;
    int redPiecesLeft = 0;
    int greenPiecesOnBlack = 0;
    int redPiecesOnBlack = 0;

    for (idx_t r = 0; r < BOARD_ROWS; ++r) {
        for (idx_t c = 0; c < BOARD_COLS; ++c) {
            auto k = r * BOARD_COLS + c;
            auto cell = board.GetCell(k);
            auto isBlack = board.IsBlack(k);
            auto isPlayerOne = cell == 1;

            if (cell != 0) {

                /*
                * Corner cell
                */

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
                }

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
                        greenAttackPiecesEliminated += attack;

                        if (attack == 0) {
                            ++greenNoopMoves;
                        } else {
                            if (attack > greenAttackMaxPiecesEliminated) {
                                greenAttackMaxPiecesEliminated = attack;
                            }
                            ++greenAttackMoves;
                        }
                    } else {
                        redAttackPiecesEliminated += attack;

                        if (attack == 0) {
                            ++redNoopMoves;
                        } else {
                            if (attack > redAttackMaxPiecesEliminated) {
                                redAttackMaxPiecesEliminated = attack;
                            }
                            ++redAttackMoves;
                        }
                    }
                }
            }
        }
    }

    return (
            100 * greenPiecesLeft +
            10 * greenPiecesOnBlack +
            0 * greenPossibleMoves +
            0 * greenAttackMoves +
            25 * greenAttackMaxPiecesEliminated +
            0 * greenNoopMoves +
            100 * greenCornerScore +

            -10 * redCornerScore +
            0 * redNoopMoves +
            -25 * redAttackMaxPiecesEliminated +
            -10 * redAttackMoves +
            0 * redPossibleMoves +
            -10 * redPiecesOnBlack +
            -200 * redPiecesLeft +

            0
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