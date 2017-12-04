#pragma once

#include "AIPlayer.h"

class DistancePlayer : public AIPlayer
{
public:
    DistancePlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};