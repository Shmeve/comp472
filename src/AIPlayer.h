#pragma once

#include "Player.h"
#include "Node.h"

class AIPlayer : public Player
{
protected:
    int MiniMax(Node* node, int depth, bool max);
public:
    AIPlayer() : Player() {};
    explicit AIPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
};