#pragma once

#include "Board.h"
#include "Move.h"

class Node
{
private:
    Node* mParent = nullptr;
    Node** mChildren = nullptr;
    Board mBoard;
    Move mMove;
    unsigned int mChildCount = 0;
    int mValue;
    int mDepth;
public:
    Node(Node* parent, Board board, Move move, int depth);
    ~Node();

    static Node* CreateTree(Board board, int depth, bool playerOne);
    inline Board& GetBoard() { return mBoard; }
    inline int GetChildCount() { return mChildCount; }
    inline Node* GetChild(int index) { return mChildren[index]; }
    inline Node* GetParent() { return mParent; }
    inline Move GetMove() { return mMove; }
    inline int GetValue() { return mValue; }
    inline int GetDepth() { return mDepth; }
    inline bool IsTerminal() { return mChildCount == 0; }
    inline void SetValue(int value) { mValue = value; }
};