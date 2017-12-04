#pragma once

#include <MonteCarloTreeSearch/MCTSState.h>
#include "Player.h"
#include "GameManager.h"

#define DEPTH 4
#define TIME_LIMIT 2.5
#define MCTS_SIMULATIONS 3

class AIPlayer : public Player
{
protected:
    int mDepth;
    bool mMiniMax;
public:
    AIPlayer(const bool& playerOne, const int& depth, bool minimax) : Player(playerOne), mDepth(depth), mMiniMax(minimax) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
    Move Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel, int alpha, int beta);
    Move MonteCarlo(const Board& board, /*out*/ int& boardValue, const bool& isPlayerOne);
    GameManager::Outcome simulate(MCTSState* node);
};