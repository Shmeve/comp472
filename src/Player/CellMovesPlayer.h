#pragma once

#include "AIPlayer.h"

class CellMovesPlayer : public AIPlayer
{
public:
    CellMovesPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth);
};