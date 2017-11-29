#include "AIPlayer.h"
#include "GameManager.h"

#include <limits>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <list>

const int moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

Move AIPlayer::GetMove(Board board, /*out*/ int* value)
{
    board.SetUI(false);

    // perform minimax
    int boardValue = mIsPlayerOne ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    Move move = Minimax(board, boardValue, 1, mDepth, mIsPlayerOne, mIsPlayerOne, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

    // display e(n) if the move isn't a forfeit
    if (move != Move(0, 0)) {
        *value = boardValue;
    }

    return move;
}

Move AIPlayer::Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel, int alpha, int beta)
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

    // we use this bool to force a move to be returned instead of forfeiting if all
    // possible moves lead to death
    bool first = true;

    for (idx_t k = 0; k < BOARD_SIZE; ++k) {
        // for all current player's tokens...
        if (board.GetCell(k) == 2 - isPlayerOne) {
            // for every possible move...
            for (const auto& i : moves) {
                Move move = Move(k, k + i);

                // we'll check if this move is legit
                if (gameManager->IsValidMove(board, move, isPlayerOne)) {
                    // if it is, simulate it with a copy of the board
                    Board tmp = board;
                    auto outcome = gameManager->PlayMove(tmp, move, 1 + isPlayerOne, true);

                    // perform minimax on this new result board
                    // we get the bubbled-up "best" value possible from this configuration
                    // and keep the move if's better for this level (depending on min/max)
                    int bv;
                    switch (outcome) {
                        case GameManager::Outcome::Player1Win:
                            bv = std::numeric_limits<int>::max() - currentDepth;
                            break;
                        case GameManager::Outcome::Player2Win:
                            bv = std::numeric_limits<int>::min() + currentDepth;
                            break;
                        case GameManager::Outcome::Draw:
                            bv = 0;
                            break;
                        default:
                            bv = !isMaxLevel ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
                            Minimax(tmp, bv, currentDepth + 1, maxDepth, !isPlayerOne, !isMaxLevel, alpha, beta);
                            break;
                    }

                    if ((isMaxLevel && bv > boardValue)
                        || (!isMaxLevel && bv < boardValue)
                        || first) {
                        // this move is better than any we've seen so far from the lower levels, keep it
                        bestMove = move;
                        boardValue = bv;
                        first = false;

                        // update alpha and beta values depending on which level we are (min/max)
                        if (isMaxLevel && boardValue > alpha) {
                            alpha = boardValue;
                        } else if (!isMaxLevel && boardValue < beta) {
                            beta = boardValue;
                        }

                        // prune the rest of this subtree if alpha and beta conflict
                        if (beta <= alpha) {
                            return bestMove;
                        }
                    }
                }
            }
        }
    }

    return bestMove;
}