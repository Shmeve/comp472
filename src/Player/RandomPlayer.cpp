#include "RandomPlayer.h"
#include "Board.h"

#include <stdexcept>

int RandomPlayer::EvaluateHeuristic(const Board& board)
{
    int result = rand();
    return result;
}