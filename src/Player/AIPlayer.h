#pragma once

#include "Player.h"

#define DEPTH 3

class AIPlayer : public Player
{
public:
    AIPlayer() : Player() {};
    explicit AIPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
    Move Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel);
};