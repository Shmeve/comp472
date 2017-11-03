#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer() : Player() {};
    HumanPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board);
};