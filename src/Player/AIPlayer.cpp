#include "AIPlayer.h"
#include "GameManager.h"

#include <limits>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <list>
#include <MonteCarloTreeSearch/MCTSState.h>

const int8_t moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

Move AIPlayer::GetMove(Board board, /*out*/ int* value)
{
    board.SetUI(false);

    // perform minimax
    int boardValue = mIsPlayerOne ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    //Move move = Minimax(board, boardValue, 1, mDepth, mIsPlayerOne, mIsPlayerOne, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    Move move = MonteCarlo(board, mIsPlayerOne);

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
                    Minimax(tmp, bv, currentDepth + 1, maxDepth, !isPlayerOne, !isMaxLevel, alpha, beta);

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

Move AIPlayer::RandomMove(const Board &board, const bool& isPlayerOne)
{
}

Move AIPlayer::MonteCarlo(const Board &board, const bool& isPlayerOne)
{
    auto gameManager = GameManager::GetInstance();
    bool terminate = false;

    // initialize a best move, default = forfeit
    Move bestMove;

    // Start Timer
    time_t start = clock();

    // Root State
    MCTSState root = MCTSState(board);


    while (((clock()-start)/CLOCKS_PER_SEC < TIME_LIMIT) && !terminate) {
        // Selection
        MCTSState selection = root;

        while (selection.getChildren()[0] != nullptr) {
            MCTSState** children = selection.getChildren();
            double_t bestChildValue = 0;
            int bestChildIndex = -1;

            // Select best child node
            for (int i = 0; i < selection.getChildrenCount(); i++) {
                double_t evaluation = children[i]->UCB();

                if (evaluation > bestChildValue) {
                    bestChildValue = evaluation;
                    bestChildIndex = i;
                }
            }

            // Evaluate best child
            if (bestChildIndex == -1) {
                int choice = rand() % MAX_CHILDREN;

                selection = *selection.getChildren()[choice];
            }
            else {
                selection = *selection.getChildren()[bestChildIndex];
            }
        }

        // Expansion

        // Simulation

        // Backpropagation
    }

    return bestMove;
}

