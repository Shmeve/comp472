#pragma once

#include <Board.h>
#include <vector>
#include <Move.h>

#define MAX_CHILDREN 5

class MCTSState {
protected:
    bool playerOne;
    int visits;
    int wins;
    int draws;
    int loses;
    int childrenCount;
    MCTSState* parent;
    Move moveToCurrentState;
    Board board;
    MCTSState** children;
    std::vector<Move> availableMoves;
public:
    MCTSState();
    MCTSState(Board board, bool playerOne, Move move);
    double UCB();
    void visit();
    void win();
    void draw();
    void lose();
    int getVisits() const;
    int getWins() const;
    int getDraws() const;
    int getLoses() const;
    int getChildrenCount() const;
    MCTSState **getChildren() const;
    const std::vector<Move> &getAvailableMoves() const;
    Move getRandomMove();
    const Board &getBoard() const;
    bool isPlayerOne() const;
    void addChild(MCTSState* child);

    const Move &getMoveToCurrentState() const;

private:
    void generateMoves();
};
