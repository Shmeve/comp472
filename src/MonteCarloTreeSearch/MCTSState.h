#pragma once

#include <Board.h>

#define MAX_CHILDREN 5

class MCTSState {
protected:
    int visits;
    int wins;
    int draws;
    int loses;
    int childrenCount;
    MCTSState* parent;
    Board board;
    MCTSState** children;
public:
    MCTSState();
    MCTSState(Board board);
    double_t UCB();
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
};
