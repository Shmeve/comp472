#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};