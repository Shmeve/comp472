#pragma once

#include "AIPlayer.h"

class CornerCellPlayer : public AIPlayer
{
public:
    CornerCellPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};