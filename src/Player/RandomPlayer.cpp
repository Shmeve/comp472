#include "RandomPlayer.h"
#include "Board.h"

#include <stdexcept>

int RandomPlayer::EvaluateHeuristic(const Board& board, const int& count, const bool& draw, const int& depth)
{
    int result = rand();
    return result;
}