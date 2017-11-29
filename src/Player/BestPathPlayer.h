#pragma once

#include "AIPlayer.h"

class BestPathPlayer : public AIPlayer
{
public:
    BestPathPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};