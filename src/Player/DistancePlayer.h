#pragma once

#include "AIPlayer.h"

class DistancePlayer : public AIPlayer
{
public:
    DistancePlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};