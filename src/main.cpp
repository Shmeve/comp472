#include <iostream>
#include <curses.h>

#include "UI.h"
#include "GameManager.h"
#include "PlayerFactory.h"
#include "HumanPlayer.h"

int main(int argc, char** argv)
{
    // wait to attach debugger
    if (argc > 1 && strncmp(argv[1], "--wait", 6) == 0) {
        getchar();
    }

    UI* ui = UI::getInstance();
    ui->init();

    ui->mainMenu();

    unsigned int numOpts;
    auto opts = PlayerFactory::Options(numOpts);

    auto greenPlayerType = ui->selectPlayer(opts, numOpts, true);
    auto redPlayerType = ui->selectPlayer(opts, numOpts, false);

    ui->startGame();

    //Game Setup
    Player* players[2] = {PlayerFactory::Create(opts[greenPlayerType], true),
                          PlayerFactory::Create(opts[redPlayerType], false)};

    GameManager* gameManager = GameManager::GetInstance();
    Board gameBoard = Board(true); // TODO: refactor this ui=true parameter
    GameManager::Outcome outcome = GameManager::Outcome::None;

    while (true) {
        Move p1Move = players[0]->GetMove(gameBoard);
        bool validMove = GameManager::GetInstance()->IsValidMove(gameBoard, p1Move, players[0]->IsPlayerOne());
        //If player is human, allow for error
        if (dynamic_cast<HumanPlayer*>(players[0])) {
            while (!validMove) {
                ui->message("Invalid move!", true);
                p1Move = players[0]->GetMove(gameBoard);
                validMove = GameManager::GetInstance()->IsValidMove(gameBoard, p1Move, players[0]->IsPlayerOne());
            }
        } else //If player is AI, error is failure
        {
            if (!validMove) {
                outcome = GameManager::Outcome::Player2Win;
                break;
            }
        }

        outcome = GameManager::GetInstance()->PlayMove(gameBoard, p1Move, 2, false);
        ui->log(1, p1Move);

        if (outcome != GameManager::Outcome::None) {
            break;
        }

        Move p2Move = players[1]->GetMove(gameBoard);
        validMove = GameManager::GetInstance()->IsValidMove(gameBoard, p2Move, players[1]->IsPlayerOne());
        //If player is human, allow for error
        if (dynamic_cast<HumanPlayer*>(players[1])) {
            while (!validMove) {
                ui->message("Invalid move!", true);
                p2Move = players[1]->GetMove(gameBoard);
                validMove = GameManager::GetInstance()->IsValidMove(gameBoard, p2Move, players[1]->IsPlayerOne());
            }
        } else //If player is AI, error is failure
        {
            if (!validMove) {
                outcome = GameManager::Outcome::Player1Win;
                break;
            }
        }

        if (outcome != GameManager::Outcome::None) {
            break;
        }

        outcome = GameManager::GetInstance()->PlayMove(gameBoard, p2Move, 1, false);
        ui->log(2, p2Move);

        if (outcome != GameManager::Outcome::None) {
            break;
        }
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

