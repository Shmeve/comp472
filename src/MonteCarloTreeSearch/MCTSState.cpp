#include <cmath>
#include <GameManager.h>
#include <cstdlib>
#include "MCTSState.h"

const int8_t moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

MCTSState::MCTSState() : board(board) {
    this->visits = 0;
    this->wins = 0;
    this->draws = 0;
    this->loses = 0;
    this->children = new MCTSState*[MAX_CHILDREN];
    generateMoves();
}

MCTSState::MCTSState(Board board, bool playerOne, Move move) : board(board) {
    this->playerOne = playerOne;
    this->visits = 0;
    this->wins = 0;
    this->draws = 0;
    this->loses = 0;
    this->moveToCurrentState = move;
    this->children = new MCTSState*[MAX_CHILDREN];

    generateMoves();
}

double MCTSState::UCB() {
    // TODO: evaluate board
    return sqrt((2*abs(log(this->parent->visits)))/this->visits);
}

void MCTSState::visit() {
    visits++;
}

void MCTSState::win() {
    wins++;
}

void MCTSState::draw() {
    draws++;
}

void MCTSState::lose() {
    loses++;
}

int MCTSState::getVisits() const {
    return visits;
}

int MCTSState::getWins() const {
    return wins;
}

int MCTSState::getDraws() const {
    return draws;
}

int MCTSState::getLoses() const {
    return loses;
}

MCTSState **MCTSState::getChildren() const {
    return children;
}

int MCTSState::getChildrenCount() const {
    return childrenCount;
}

void MCTSState::generateMoves() {
    auto gameManager = GameManager::GetInstance();

    for (idx_t k = 0; k < BOARD_SIZE; ++k) {
        // for all current player's tokens...
        if (board.GetCell(k) == 2 - playerOne) {
            // for every possible move...
            for (int8_t i : moves) {
                Move move = Move(k, k + i);

                if (gameManager->IsValidMove(board, move, playerOne)) {
                    availableMoves.push_back(move);
                }
            }
        }
    }
}

const std::vector<Move> &MCTSState::getAvailableMoves() const {
    return availableMoves;
}

Move MCTSState::getRandomMove() {
    int index = rand() % availableMoves.size();
    return availableMoves.at(index);
}

const Board &MCTSState::getBoard() const {
    return board;
}

bool MCTSState::isPlayerOne() const {
    return playerOne;
}

void MCTSState::addChild(MCTSState *child) {
    children[childrenCount] = child;
    childrenCount++;
}

const Move &MCTSState::getMoveToCurrentState() const {
    return moveToCurrentState;
}


