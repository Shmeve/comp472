#include <iostream>
#include <curses.h>
#include <string.h>

#include "UI.h"
#include "HumanPlayer.h"
#include "RemainingTilesPlayer.h"
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
    players[1] = new RemainingTilesPlayer(false);

    GameManager* gameManager = GameManager::GetInstance();
    Board gameBoard = Board(true);

    GameManager::Outcome outcome = GameManager::Outcome::None;
    while (true)
    {
        Move p1Move = players[0]->GetMove(gameBoard);
        while (!GameManager::GetInstance()->IsValidMove(gameBoard, p1Move, players[0]->IsPlayerOne()))
        {
            ui->message("Invalid move!", true);
            p1Move = players[0]->GetMove(gameBoard);
        }

        outcome = GameManager::GetInstance()->PlayMove(gameBoard, p1Move, 2, false);
        ui->log(1, p1Move);

        if (outcome != GameManager::Outcome::None)
            break;

        Move p2Move = players[1]->GetMove(gameBoard);
        while (!GameManager::GetInstance()->IsValidMove(gameBoard, p2Move, players[1]->IsPlayerOne()))
        {
            outcome = GameManager::Outcome::Player1Win;
            break;

            //TODO: Allow for Human Player2
            //ui->message("Invalid move!", true);
            //p2Move = players[1]->GetMove();
        }

        if (outcome != GameManager::Outcome::None)
            break;

        outcome = GameManager::GetInstance()->PlayMove(gameBoard, p2Move, 1, false);
        ui->log(2, p2Move);

        if (outcome != GameManager::Outcome::None)
            break;
    }

    std::string message;

    switch (outcome) {
        case GameManager::Outcome::Player1Win:
            message = "Player 1 wins!";
            break;
        case GameManager::Outcome::Player2Win:
            message = "Player 2 wins!";
            break;
        case GameManager::Outcome::Draw:
            message = "It's a draw!";
            break;
        default:
            message = "This isn't good.";
            break;
    }

    ui->message(message, true);

    return 0;
}

