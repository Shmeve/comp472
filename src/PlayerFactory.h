#pragma once

#include "Player/Player.h"

class PlayerFactory
{
public:
    static const char** Options(/*out*/ unsigned int& len);
    static Player* Create(const char* type, const bool& playerOne, const int& depth);
};
