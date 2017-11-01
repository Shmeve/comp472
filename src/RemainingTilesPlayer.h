#pragma once

#include "AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer() : AIPlayer() {};
    RemainingTilesPlayer(bool playerOne, bool alphaBeta) : AIPlayer(playerOne, alphaBeta) {};

    int EvaluateHeuristic(Board& board);
};