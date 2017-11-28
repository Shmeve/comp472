#pragma once

#include "AIPlayer.h"

class BestPathPlayer : public AIPlayer
{
public:
    BestPathPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth);
};