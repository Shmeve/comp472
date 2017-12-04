#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    int EvaluateHeuristic(const Board& board) override;
};