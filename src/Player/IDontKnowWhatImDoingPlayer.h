#pragma once

#include "AIPlayer.h"

class IDontKnowWhatImDoingPlayer : public AIPlayer
{
public:
    IDontKnowWhatImDoingPlayer(const bool& playerOne, const int& depth) : AIPlayer(playerOne, depth) {};

    virtual int EvaluateHeuristic(const Board& board);
};