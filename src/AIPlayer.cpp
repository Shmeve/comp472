#include "AIPlayer.h"
#include "Node.h"
#include "GameManager.h"

#include <limits.h>
#include <algorithm>

#include <iostream>
#include <fstream>
#include <list>
#include <time.h>

Move AIPlayer::GetMove(Board board)
{
    board.SetUI(false);

    // Create tree
    std::ofstream file;
    file.open("C:/Users/thoma/Desktop/runtime.txt", std::ios::app);

    clock_t t = clock();
    Node* root = Node::CreateTree(board, 4, false);
    t = clock() - t;

    file << ((float)t / CLOCKS_PER_SEC) << '\n';
    file.close();

    // Call MiniMax
    int value = MiniMax(root, 4, mIsPlayerOne);

    // TODO: draw root
    /*std::ofstream file;
    file.open("tree.txt");

    std::list<Node*> tree;
    tree.push_back(root);

    int depth = 0;
    Node* prevParent = nullptr;
    while (!tree.empty()) {
        Node* node = tree.front();

        if (depth != node->GetDepth()) {
            depth = node->GetDepth();
            prevParent = node->GetParent();
            file << "/n";
        }

        if (prevParent == node->GetParent()) {
            file << " ";
        } else {
            file << ",";
        }

        file << node->GetValue();

        for (int i = 0; i < node->GetChildCount(); i++)
            tree.push_back(node->GetChild(i));

        prevParent = node->GetParent();
        tree.pop_front();
    }

    file << "/n/n";
    file.close();
    */

    for (int i = 0; i < root->GetChildCount(); i++) {
        if (root->GetChild(i)->GetValue() == value) {
            return root->GetChild(i)->GetMove();
        }
    }

    return Move(0, 0); //THIS IS BAD
}

int AIPlayer::MiniMax(Node* node, int depth, bool maxPlayer)
{
    if (depth == 0 || node->IsTerminal()) {
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