#pragma once

#include "Player.h"
#include "Node.h"

class AIPlayer : public Player
{
private:
    bool mAlphaBeta;
public:
    AIPlayer() : Player() {};
    AIPlayer(bool playerOne, bool alphaBeta) : mAlphaBeta(alphaBeta), Player(playerOne) {};
    Move GetMove(Board board);
    int MiniMax(Node* node, int depth, bool maxPlayer);
    int AlphaBeta(Node* node, int depth, int alpha, int beta, bool maxPlayer);
    virtual int EvaluateHeuristic(Board& board) = 0;
};