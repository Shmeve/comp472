#include "HumanPlayer.h"

#include <iostream>
#include <string>
#include <set>

Move HumanPlayer::GetMove()
{
    std::set<char> rows = { 'A', 'B', 'C', 'D', 'E' };

    std::string startString;
    std::string endString;

    auto rowSearch = rows.begin();
    do {
        std::cout << (mIsPlayerOne ? "Player 1: " : "Player 2: ");
        std::cout << "Enter the start cell: \n";
        std::cin >> startString;

        rowSearch = rows.find(toupper(startString[0]));
    } while (startString.length() != 2 || rowSearch == rows.end() || startString[1] - '0' > 9 || startString[1] - '0' < 1);

    do {
        std::cout << (mIsPlayerOne ? "Player 1: " : "Player 2: ");
        std::cout << "Enter the end cell: \n";
        std::cin >> endString;

        rowSearch = rows.find(toupper(endString[0]));
    } while (endString.length() != 2 || rowSearch == rows.end() || endString[1] - '0' > 9 || endString[1] - '0' < 1);

    return Move(9 * (toupper(startString[0]) - 'A') + (startString[1] - '0') - 1, 9 * (toupper(endString[0]) - 'A') + (endString[1] - '0') - 1);
}