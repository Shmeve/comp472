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
    MCTSState* parent;
    std::vector<MCTSState*> children; /*TODO: rework children*/
    Board board;
    Move moveToCurrentState;
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
    const std::vector<MCTSState *> &getChildren() const;
    const std::vector<Move> &getAvailableMoves() const;
    Move getRandomMove();
    void update(int result);
    const Board &getBoard() const;
    bool isPlayerOne() const;
    void addChild(MCTSState* child);
    bool childrenIsFull();
    const Move &getMoveToCurrentState() const;
    MCTSState *getParent() const;
    void setParent(MCTSState *parent);
private:
    void generateMoves();
};
