#include "HumanPlayer.h"

#include <iostream>

Move HumanPlayer::GetMove()
{
    char* startString = nullptr;
    char* endString = nullptr;
    std::cout << "Enter the start cell: \n";
    std::cin >> startString;
    std::cout << "\nEnter the end cell: \n";
    std::cin >> endString;

    //TODO: Validate this is proper move

    //TODO: Format into move
    return Move(0, 0);
}