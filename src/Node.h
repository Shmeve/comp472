#pragma once

#include "Board.h"
#include "Move.h"

class Node
{
private:
    Node** mChildren;
    Board mBoard;
    Move mMove;
    int mChildCount;
    int mValue;
public:
    Node();
    ~Node();

    static Node* CreateTree(Board board, int depth, bool playerOne);
    inline Board GetBoard() { return mBoard; }
    inline int GetChildCount() { return mChildCount; }
    inline Node* GetChild(int index) { return mChildren[index]; }
    inline Move GetMove() { return mMove; }
    inline int GetValue() { return mValue; }
    inline bool IsTerminal() { return mChildren == nullptr; }
    inline void SetValue(int value) { mValue = value; }
};