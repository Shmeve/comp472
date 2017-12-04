#pragma once

#include "AIPlayer.h"

class OthelloPlayer : public AIPlayer
{
public:
    OthelloPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    int EvaluateHeuristic(const Board& board) override;
};