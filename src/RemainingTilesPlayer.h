#pragma once

#include "AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer() : AIPlayer() {};
    RemainingTilesPlayer(bool playerOne) : AIPlayer(playerOne) {};

    int EvaluateHeuristic(Board& board);
};