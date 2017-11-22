#pragma once

#include "Player/AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer() : AIPlayer() {};
    explicit RemainingTilesPlayer(const bool& playerOne) : AIPlayer(playerOne) {};

    int EvaluateHeuristic(const Board& board) override;
};