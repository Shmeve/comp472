#pragma once

#include "AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer() : AIPlayer() {};
    RemainingTilesPlayer(const bool& playerOne) : AIPlayer(playerOne) {};

    int EvaluateHeuristic(Board& board);
};