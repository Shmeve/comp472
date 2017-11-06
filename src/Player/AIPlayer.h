#pragma once

#include "Player.h"
#include "Node.h"

class AIPlayer : public Player
{
protected:
    int mDepth;
    int MiniMax(Node* node, int depth, bool max);
public:
    AIPlayer(const bool& playerOne, const int& depth) : Player(playerOne), mDepth(depth) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
};