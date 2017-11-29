#pragma once

#include "AIPlayer.h"

class CellMovesPlayer : public AIPlayer
{
public:
    CellMovesPlayer(const bool& playerOne, const int& depth, bool minimax) : AIPlayer(playerOne, depth, minimax) {};

    virtual int EvaluateHeuristic(const Board& board);
};