#pragma once

#include "Player.h"
#include "Node.h"

class AIPlayer : public Player
{
public:
    AIPlayer() : Player() {};
    AIPlayer(bool playerOne) : Player(playerOne) {};
    Move GetMove(Board board);
    int MiniMax(Node* node, int depth, bool max);
    virtual int EvaluateHeuristic(Board& board) = 0;
};