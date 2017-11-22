#pragma once

#include "AIPlayer.h"

class NaivePlayer : public AIPlayer
{
public:
    NaivePlayer() : AIPlayer() {};
    explicit NaivePlayer(const bool& playerOne) : AIPlayer(playerOne) {};

    int EvaluateHeuristic(const Board& board) override;
};