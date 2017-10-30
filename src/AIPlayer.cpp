#include "AIPlayer.h"
#include "Node.h"
#include "GameManager.h"

#include <limits.h>
#include <algorithm>

Move AIPlayer::GetMove(Board board)
{
    board.SetUI(false);

    // Create tree
    Node* root = Node::CreateTree(board, 3, false);

    // Call MiniMax
    // TODO: if RED -> MIN, GREEN -> MAX
    // FOR NAIVE HEURISTIC
    // HARD-CODE FALSE FOR RED
    int max = MiniMax(root, 3, false);

    for (int i = 0; i < root->GetChildCount(); i++) {
        if (root->GetChild(i)->GetValue() == max)
            return root->GetChild(i)->GetMove();
    }

    return Move(0, 0); //THIS IS BAD
}

int AIPlayer::MiniMax(Node* node, int depth, bool maxPlayer)
{
    if (depth = 0 || node->IsTerminal())
        return EvaluateHeuristic(node->GetBoard());

    if (maxPlayer)
    {
        int max = INT_MIN;
        for (int i = 0; i < node->GetChildCount(); i++) {
            max = std::max(max, MiniMax(node->GetChild(i), depth - 1, !maxPlayer));
        }
        node->SetValue(max);
        return max;
    }
    else
    {
        int min = INT_MAX;
        for (int i = 0; i < node->GetChildCount(); i++) {
            min = std::min(min, MiniMax(node->GetChild(i), depth - 1, !maxPlayer));
        }
        node->SetValue(min);
        return min;
    }
}