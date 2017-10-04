#pragma once

#include "Move.h"

class Player
{
protected:
    bool mIsPlayerOne;
public:
    Player() {};
    Player(bool playerOne) : mIsPlayerOne(playerOne) {};
    inline bool IsPlayerOne() { return mIsPlayerOne; }
    virtual Move GetMove() = 0;
};