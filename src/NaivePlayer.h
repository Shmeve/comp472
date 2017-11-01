#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer() : AIPlayer() {};
    NaivePlayer(bool playerOne, bool alphaBeta) : AIPlayer(playerOne, alphaBeta) {};

    int EvaluateHeuristic(Board& board);
};