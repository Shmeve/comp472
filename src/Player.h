#pragma once

#include "Move.h"
#include "Board.h"

class Player
{
protected:
    bool mIsPlayerOne;
public:
    Player() {};
    Player(const bool& playerOne) : mIsPlayerOne(playerOne) {};
    inline bool IsPlayerOne() { return mIsPlayerOne; }
    virtual Move GetMove(Board board) = 0;
};