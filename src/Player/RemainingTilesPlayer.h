#pragma once

#include "Player/AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    int EvaluateHeuristic(const Board& board) override;
};