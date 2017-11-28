#pragma once

#include "AIPlayer.h"

class DistanceTravelledPlayer : public AIPlayer
{
public:
    DistanceTravelledPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    int EvaluateHeuristic(const Board& board) override;
};