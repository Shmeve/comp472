#include <cmath>
#include "MCTSState.h"

MCTSState::MCTSState() : board(board) {
    this->visits = 0;
    this->wins = 0;
    this->draws = 0;
    this->loses = 0;
    this->children = new MCTSState*[MAX_CHILDREN];
}

MCTSState::MCTSState(Board board) : board(board) {
    this->visits = 0;
    this->wins = 0;
    this->draws = 0;
    this->loses = 0;
    this->children = new MCTSState*[MAX_CHILDREN];
}

double_t MCTSState::UCB() {
    // TODO: evaluate board
    return sqrt((2*log(this->parent->visits))/this->visits);
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


