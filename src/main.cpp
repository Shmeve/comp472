#include <iostream>
#include <curses.h>
#include <stdexcept>
#include <string.h>
#include <limits>

#include "UI.h"
#include "GameManager.h"
#include "PlayerFactory.h"
#include "Player/HumanPlayer.h"

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

    // Game Setup
    Player* players[2] = {PlayerFactory::Create(opts[greenPlayerType], true),
                          PlayerFactory::Create(opts[redPlayerType], false)};

    GameManager* gameManager = GameManager::GetInstance();
    Board gameBoard = Board(true); // TODO: refactor this ui=true parameter
    GameManager::Outcome outcome = GameManager::Outcome::None;
    unsigned int currentPlayer = 0; // green goes first

    while (outcome == GameManager::Outcome::None) {
        Player* player = players[currentPlayer];
        bool isPlayerOne = player->IsPlayerOne();
        Move move;
        int value = std::numeric_limits<int>::min();
        bool validMove;

        do {
            move = player->GetMove(gameBoard, &value);
            validMove = gameManager->IsValidMove(gameBoard, move, isPlayerOne);

            if (!validMove) {
                if (move == Move(0, 0)) {
                    // Move A1 A1 (0, 0) signals forfeit
                    outcome = isPlayerOne ? GameManager::Outcome::Player2Win
                                          : GameManager::Outcome::Player1Win;
                } else if (dynamic_cast<HumanPlayer*>(player)) {
                    // If player is human, allow for input error
                    ui->message("Invalid move!", true);
                } else {
                    // If player is AI, error is exception
                    throw std::runtime_error("AI returned incorrect move");
                }
            }
        } while (!validMove && outcome == GameManager::Outcome::None);

        // bail out early if we have an outcome
        if (outcome != GameManager::Outcome::None) {
            break;
        }

        outcome = gameManager->PlayMove(gameBoard, move, 1 + isPlayerOne, false);
        ui->log(isPlayerOne, move, value);

        // flip current player
        currentPlayer = 1 - currentPlayer;
    }

    std::string message;

    switch (outcome) {
        case GameManager::Outcome::Player1Win:
            message = "Green wins!";
            break;
        case GameManager::Outcome::Player2Win:
            message = "Red wins!";
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

