#pragma once

#include "Player.h"
#include "Node.h"

class AIPlayer : public Player
{
public:
    AIPlayer() : Player() {};
    explicit AIPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board);
    int MiniMax(Node* node, int depth, bool max);
    virtual int EvaluateHeuristic(const Board& board) = 0;
};