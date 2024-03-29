#pragma once

#include "Player.h"

class HumanPlayer : public Player
{
public:
    explicit HumanPlayer(const bool& playerOne) : Player(playerOne) {};
    Move GetMove(Board board, /*out*/ int* value) override;
};