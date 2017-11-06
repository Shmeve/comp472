#pragma once

#include "Player.h"

#include <omp.h>

#define DEPTH 3

class AIPlayer : public Player
{
private:
    omp_lock_t lock;
public:
    AIPlayer() : Player() {
        omp_init_lock(&lock);
    };
    virtual ~AIPlayer();
    explicit AIPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board, /*out*/ int* value) override;
    virtual int EvaluateHeuristic(const Board& board) = 0;
    Move Minimax(const Board& board, /*out*/ int& boardValue, const int& currentDepth, const int& maxDepth, const bool& isPlayerOne, const bool& isMaxLevel, int alpha, int beta);
};