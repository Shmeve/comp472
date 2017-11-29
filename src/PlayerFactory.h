#pragma once

#include "Player/Player.h"

class PlayerFactory
{
public:
    static const char** PlayerTypes(/*out*/ unsigned int& len);
    static const char** SearchTypes(/*out*/ unsigned int& len);
    static Player* Create(const char* type, const bool& playerOne, const int& depth, bool minimax);
};
