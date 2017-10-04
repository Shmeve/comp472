#include <iostream>
#include <curses.h>
#include <string.h>

#include "UI.h"
#include "HumanPlayer.h"
#include "GameManager.h"

int main(int argc, char** argv)
{
    // wait to attach debugger
    if (argc > 1 && strncmp(argv[1], "--wait", 6) == 0) {
        getchar();
    }

    UI* ui = UI::getInstance();
    ui->init();

    //Game Setup
    Player** players = new Player*[2];

    //Create 2 human players
    players[0] = new HumanPlayer(true);
    players[1] = new HumanPlayer(false);

    GameManager* gameManager = GameManager::GetInstance();

    GameManager::Outcome outcome = GameManager::Outcome::None;
    while (true)
    {
        Move p1Move = players[0]->GetMove();
        while (!GameManager::GetInstance()->IsValidMove(p1Move, true))
        {
            ui->message("Invalid move!", true);
            p1Move = players[0]->GetMove();
        }

        outcome = GameManager::GetInstance()->PlayMove(p1Move, 2);
        ui->log(1, p1Move);

        if (outcome != GameManager::Outcome::None)
            break;

        // TODO: If AI makes mistake, LOSE
        Move p2Move = players[1]->GetMove();
        while (!GameManager::GetInstance()->IsValidMove(p2Move, false))
        {
            ui->message("Invalid move!", true);
            p2Move = players[1]->GetMove();
        }

        outcome = GameManager::GetInstance()->PlayMove(p2Move, 1);
        ui->log(2, p2Move);

        if (outcome != GameManager::Outcome::None)
            break;
    }

    return 0;
}

