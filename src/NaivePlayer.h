#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer() : AIPlayer() {};
    NaivePlayer(bool playerOne) : AIPlayer(playerOne) {};

    int EvaluateHeuristic(Board& board);
};