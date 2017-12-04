#include <iostream>
#include <curses.h>
#include <stdexcept>
#include <string.h>
#include <limits>
#include <time.h>
#include <cxxopts/cxxopts.hpp>

#include "UI.h"
#include "GameManager.h"
#include "PlayerFactory.h"
#include "Player/HumanPlayer.h"

#define DEFAULT_DEPTH 6

int main(int argc, char** argv)
{
    cxxopts::Options options("Armadillo", "Team 11 - Bonzee");

    int greenPlayerType = -1;
    int redPlayerType = -1;
    int depth = DEFAULT_DEPTH;
    int greenDepth = 0;
    int redDepth = 0;

    options.add_options()
            ("h,help", "Help")
            ("w,wait", "Wait for debugger to attach")
            ("g,green", "Green player type", cxxopts::value(greenPlayerType))
            ("r,red", "Red player type", cxxopts::value(redPlayerType))
            ("d,depth", "Tree search depth for both players (shortcut)", cxxopts::value(depth))
            ("G,greendepth", "Tree search depth for Red player", cxxopts::value(greenDepth))
            ("R,reddepth", "Tree search depth for Green player", cxxopts::value(redDepth))
            ;

    options.parse(argc, argv);

    // wait to attach debugger
    if (options["wait"].as<bool>()) {
        getchar();
    }

    if (options["help"].as<bool>()) {
        std::cout << options.help();
        return 0;
    }

    srand((unsigned int)time(nullptr));

    UI* ui = UI::getInstance();
    ui->init();

    ui->mainMenu();

    unsigned int numTypes;
    auto player = PlayerFactory::PlayerTypes(numTypes);

    unsigned int numOpts;
    auto search = PlayerFactory::SearchTypes(numOpts);

    auto greenSearchMethod = std::numeric_limits<int>::max();
    auto redSearchMethod = std::numeric_limits<int>::max();

    if (greenPlayerType < 0) {
        greenPlayerType = ui->selectPlayer(player, numTypes, true);
        if (greenPlayerType != 0) { // AI
            greenSearchMethod = ui->selectSearchMethod(search, numOpts, true);
        }
    }

    if (redPlayerType < 0) {
        redPlayerType = ui->selectPlayer(player, numTypes, false);
        if (redPlayerType != 0) { // AI
            redSearchMethod = ui->selectSearchMethod(search, numOpts, false);
        }
    }

    ui->startGame();

    // Game Setup
    Player* players[2] = {PlayerFactory::Create(player[greenPlayerType], true, greenDepth ? greenDepth : depth, (greenSearchMethod == 0)),
                          PlayerFactory::Create(player[redPlayerType], false, redDepth ? redDepth : depth, (redSearchMethod == 0))};

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

    ui->outcome(outcome);

    return 0;
}

