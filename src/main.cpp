#include <iostream>

#include "HumanPlayer.h"
#include "GameManager.h"

int main(int argc, char** argv)
{
    //Game Setup
    Player** players = new Player*[2];

    //Create 2 human players
    players[0] = new HumanPlayer(true);
    players[1] = new HumanPlayer(false);

    GameManager::Outcome outcome = GameManager::Outcome::None;
    while (true)
    {
        Move p1Move = players[0]->GetMove();
        while (!GameManager::GetInstance()->IsValidMove(p1Move, true))
        {
            std::cout << "Invalid move!\n";
            p1Move = players[0]->GetMove();
        }

        outcome = GameManager::GetInstance()->PlayMove(p1Move, 2);

        if (outcome != GameManager::Outcome::None)
            break;

        // TODO: If AI makes mistake, LOSE
        Move p2Move = players[1]->GetMove();
        while (!GameManager::GetInstance()->IsValidMove(p2Move, false))
        {
            std::cout << "Invalid move!\n";
            p2Move = players[1]->GetMove();
        }

        outcome = GameManager::GetInstance()->PlayMove(p1Move, 1);

        if (outcome != GameManager::Outcome::None)
            break;
    }

    return 0;
}

