#pragma once

#include "AIPlayer.h"

class OthelloPlayer : public AIPlayer
{
public:
    OthelloPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    int EvaluateHeuristic(const Board& board) override;
};