#pragma once

#include "AIPlayer.h"

class RandomPlayer : public AIPlayer
{
public:
    RandomPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};