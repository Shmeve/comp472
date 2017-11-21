#pragma once

#include "AIPlayer.h"

class RandomPlayer : public AIPlayer
{
public:
    RandomPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};