#pragma once

#include "AIPlayer.h"

class MOAHPlayer : public AIPlayer
{
public:
    MOAHPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};