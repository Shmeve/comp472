#pragma once

#include "Player.h"

class PlayerFactory
{
public:
    static const char** PlayerTypes(/*out*/ unsigned int& len);
    static const char** Options(/*out*/ unsigned int& len);
    static Player* Create(const char* type, const bool& playerOne, const bool& alphaBeta);
};
