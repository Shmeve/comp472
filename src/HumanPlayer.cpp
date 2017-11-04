#include "HumanPlayer.h"
#include "UI.h"
#include "Board.h"

#include <iostream>
#include <string>
#include <set>

Move HumanPlayer::GetMove(Board board)
{
    std::string moveStr = UI::getInstance()->getMove(mIsPlayerOne);

    return {static_cast<idx_t>(BOARD_COLS * (toupper(moveStr[0]) - 'A') + (moveStr[1] - '0') - 1),
            static_cast<idx_t>(BOARD_COLS * (toupper(moveStr[2]) - 'A') + (moveStr[3] - '0') - 1)};
}