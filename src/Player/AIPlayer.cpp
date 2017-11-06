#include "AIPlayer.h"
#include "GameManager.h"

#include <limits>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <list>

const int8_t moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

Move AIPlayer::GetMove(Board board, /*out*/ int* value)
{
    board.SetUI(false);

    // perform minimax
    int boardValue = mIsPlayerOne ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move move = Minimax(board, boardValue, 1, DEPTH, mIsPlayerOne, mIsPlayerOne);

    // display e(n) if the move isn't a forfeit
    if (move != Move(0, 0)) {
        *value = boardValue;
    }

    return move;
}

Move AIPlayer::Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel)
{
    auto gameManager = GameManager::GetInstance();

    // initialize a best move, default = forfeit
    Move bestMove;

    // check if we're at a terminal board
    if (currentDepth == maxDepth) {
        // if yes, we evaluate its e(n) and bubble it up
        boardValue = EvaluateHeuristic(board);
        // don't care about retval
        return bestMove;
    }

    for (idx_t k = 0; k < BOARD_SIZE; ++k) {
        // for all current player's tokens...
        if (board.GetCell(k) == 2 - isPlayerOne) {
            // for every possible move...
            for (int8_t i : moves) {
                Move move = Move(k, k + i);

                // we'll check if this move is legit
                if (gameManager->IsValidMove(board, move, isPlayerOne)) {
                    // if it is, simulate it with a copy of the board
                    Board tmp = board;
                    gameManager->PlayMove(tmp, move, 1 + isPlayerOne, true);

                    // TODO: store outcome from PlayMove and don't recurse if not necessary

                    // perform minimax on this new result board
                    // we get the bubbled-up "best" value possible from this configuration
                    // and keep the move if's better for this level (depending on min/max)
                    int bv = !isMaxLevel ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
                    Minimax(tmp, bv, currentDepth + 1, maxDepth, !isPlayerOne, !isMaxLevel);

                    if ((isMaxLevel && bv > boardValue)
                        || (!isMaxLevel && bv < boardValue)) {
                        // this move is better than any we've seen so far from the lower levels, keep it
                        bestMove = move;
                        boardValue = bv;
                    }
                }
            }
        }
    }

    return bestMove;
}