#include <cmath>
#include <GameManager.h>
#include <cstdlib>
#include <random>
#include "MCTSState.h"

const int8_t moves[] = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

MCTSState::MCTSState(Board board, bool playerOne, Move move) : board(board), children(), availableMoves() {
    this->playerOne = playerOne;
    this->visits = 0;
    this->wins = 0;
    this->draws = 0;
    this->loses = 0;
    this->moveToCurrentState = move;
    this->parent = nullptr;
    this->evaluation = 0;

    generateMoves();
}

MCTSState::~MCTSState()
{
    int size = this->children.size();
    for (idx_t i = 0; i < size; ++i) {
        free(this->children[i]);
    }
}

double MCTSState::UCB(const int& heuristicValue) {
    // TODO: evaluate board -> should probably consider wins/losses and can integrate some of our heuristics
        // Heuristic + UCB equation.
    this->evaluation = ((double)(((this->playerOne) ? wins - loses : loses - wins) + draws) / (double)(wins + loses + draws)) + heuristicValue + TUNE * sqrt((abs(log(this->parent->visits))) / (double)(this->visits));
    return evaluation;
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

const std::vector<MCTSState *> &MCTSState::getChildren() const {
    return children;
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
    if (!availableMoves.empty())
        return availableMoves.at(rand() % availableMoves.size());
    else
        return Move();
}

const Board &MCTSState::getBoard() const {
    return board;
}

void MCTSState::update(int result) {
    switch (result) {
        case GameManager::Outcome::Player1Win:
            win();
            break;
        case GameManager::Outcome::Player2Win:
            lose();
            break;
        case GameManager::Outcome::Draw:
            draw();
            break;
        default:
            break;
    }
}

bool MCTSState::isPlayerOne() const {
    return playerOne;
}

void MCTSState::addChild(MCTSState *child) {
    child->setParent(this);
    children.push_back(child);
}

bool MCTSState::childrenIsFull() {
    return children.size() < MAX_CHILDREN;
}

const Move &MCTSState::getMoveToCurrentState() const {
    return moveToCurrentState;
}

MCTSState *MCTSState::getParent() const {
    return parent;
}

void MCTSState::setParent(MCTSState *parent) {
    this->parent = parent;
}

double MCTSState::getEvaluation() {
    return this->evaluation;
}