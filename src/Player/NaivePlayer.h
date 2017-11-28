#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    int EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth) override;
};