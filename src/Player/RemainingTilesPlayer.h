#pragma once

#include "Player/AIPlayer.h"

class RemainingTilesPlayer : public AIPlayer
{
public:
    RemainingTilesPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    int EvaluateHeuristic(const Board& board) override;
};