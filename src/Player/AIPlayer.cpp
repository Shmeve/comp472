#include "AIPlayer.h"
#include "Node.h"
#include "GameManager.h"

#include <limits.h>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <list>

Move AIPlayer::GetMove(Board board, /*out*/ int* value)
{
    board.SetUI(false);

    // Create tree
    Node* root = Node::CreateTree(board, mDepth, mIsPlayerOne);

    // Call MiniMax
    *value = MiniMax(root, mDepth, mIsPlayerOne);

    for (int i = 0; i < root->GetChildCount(); i++) {
        if (root->GetChild(i)->GetValue() == *value) {
            return root->GetChild(i)->GetMove();
        }
    }

    return Move(0, 0); //THIS IS BAD
}

int AIPlayer::MiniMax(Node* node, int depth, bool maxPlayer)
{
    if (depth == 1 || node->IsTerminal()) {
        node->SetValue(EvaluateHeuristic(node->GetBoard()));
        return node->GetValue();
    }

    if (maxPlayer) {
        int max = INT_MIN;
        for (int i = 0; i < node->GetChildCount(); i++) {
            max = std::max(max, MiniMax(node->GetChild(i), depth - 1, !maxPlayer));
        }
        node->SetValue(max);
        return max;
    } else {
        int min = INT_MAX;
        for (int i = 0; i < node->GetChildCount(); i++) {
            min = std::min(min, MiniMax(node->GetChild(i), depth - 1, !maxPlayer));
        }
        node->SetValue(min);
        return min;
    }
}