#include "Node.h"
#include "GameManager.h"

#include <list>

Node::Node()
{
    mBoard = Board(false);
}

Node::~Node()
{
    for (int i = 0; i < mChildCount; i++) {
        delete mChildren[i];
    }

    delete[] mChildren;
}

Node* Node::CreateTree(Board board, int depth, bool playerOne)
{
    Node* node = new Node();
    node->mBoard = board;

    std::list<int> pos = { -BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1 };
    std::list<Move> moves;

    for (int i = 0; i < BOARD_ROWS * BOARD_COLS; i++) {
        if (node->mBoard.GetCells()[i] == (playerOne ? 1 : 2))
        {
            for (int n : pos) {
                Move move = Move(i, i + n);
                if (GameManager::GetInstance()->IsValidMove(node->mBoard, move, playerOne))
                    moves.push_back(move);
            }
        }
    }
    node->mChildCount = moves.size();

    if (depth > 0 && node->mChildCount > 0)
    {
        node->mChildren = new Node*[node->mChildCount];
        int index = 0;
        for (std::list<Move>::const_iterator it = moves.begin(); it != moves.end(); ++it) {
            Board tmp = node->mBoard;
            GameManager::GetInstance()->PlayMove(tmp, *it, 1, true);
            node->mChildren[index] = CreateTree(tmp, depth - 1, !playerOne);
            node->mChildren[index]->mMove = *it;
            index++;
        }
    }
    else
    {
        node->mChildren = nullptr;
    }

    return node;
}