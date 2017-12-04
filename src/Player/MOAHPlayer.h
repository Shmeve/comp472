#pragma once

#include "AIPlayer.h"

class MOAHPlayer : public AIPlayer
{
public:
    MOAHPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};