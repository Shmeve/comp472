#include "HumanPlayer.h"
#include "UI.h"
#include "Board.h"

#include <iostream>
#include <string>
#include <set>

Move HumanPlayer::GetMove()
{
    std::string moveStr = UI::getInstance()->getMove();

    return {BOARD_COLS * (toupper(moveStr[0]) - 'A') + (moveStr[1] - '0') - 1, BOARD_COLS * (toupper(moveStr[2]) - 'A') + (moveStr[3] - '0') - 1};
}