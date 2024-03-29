#pragma once

#include "AIPlayer.h"

class NeighborPlayer : public AIPlayer
{
public:
    NeighborPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};