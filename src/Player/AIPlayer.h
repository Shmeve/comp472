#pragma once

#include "Player.h"

#define DEPTH 4
#define TIME_LIMIT 3

class AIPlayer : public Player
{
protected:
    int mDepth;
public:
    AIPlayer(const bool& playerOne, const int& depth) : Player(playerOne), mDepth(depth) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
    Move Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel, int alpha, int beta);
    Move RandomMove(const Board& board, const bool& isPlayerOne);
    Move MonteCarlo(const Board& board, const bool& isPlayerOne);
    void MCTSUpperConfidenceBound();
};