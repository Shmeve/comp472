#pragma once

#include "AIPlayer.h"

class CornerCellPlayer : public AIPlayer
{
public:
    CornerCellPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};