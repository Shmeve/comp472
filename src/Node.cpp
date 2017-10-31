#include "Node.h"
#include "GameManager.h"

#include <list>
#include <utility>
#include <vector>
#include <omp.h>

Node::Node(Node* parent, Board board, Move move, int depth)
        : mParent(parent), mBoard(std::move(board)), mMove(move), mDepth(depth)
{
}

Node::~Node()
{
    for (unsigned int i = 0; i < mChildCount; i++) {
        delete mChildren[i];
    }

    delete[] mChildren;
}

Node* Node::CreateTree(Board board, int depth, bool playerOne)
{
    Node* root = new Node(nullptr, std::move(board), {}, 0);
    std::list<int> pos = {-BOARD_COLS - 1, -BOARD_COLS, -BOARD_COLS + 1, -1, 1, BOARD_COLS - 1, BOARD_COLS, BOARD_COLS + 1};

    auto* nodesAtDepth = new std::vector<Node*>[depth + 1];
    nodesAtDepth[0].push_back(root);

    // Iterate through depth levels
    for (int i = 0; i <= depth; i++) {
        // Iterate through nodes in depth i
        std::vector<Node*>* tmpNodesAtDepth = new std::vector<Node*>[nodesAtDepth[i].size()];
        #pragma omp parallel for
        for (int j = 0; j < nodesAtDepth[i].size(); j++) {
            if (i == depth) {
                // If depth is lowest depth, NO CHILDREN
                nodesAtDepth[i][j]->mChildren = nullptr;
            } else {
                std::list<Move> moves;

                // Generate moves
                for (int k = 0; k < BOARD_ROWS * BOARD_COLS; k++) {
                    if (nodesAtDepth[i][j]->mBoard.GetCells()[k] == (i % 2 ? (playerOne ? 2 : 1) : (playerOne ? 1 : 2))) {
                        for (int n : pos) {
                            Move move = Move(k, k + n);
                            if (GameManager::GetInstance()->IsValidMove(nodesAtDepth[i][j]->mBoard, move, (i % 2) ? !playerOne : playerOne)) {
                                moves.push_back(move);
                            }
                        }
                    }
                }

                nodesAtDepth[i][j]->mChildCount = static_cast<unsigned int>(moves.size());

                int index = 0;
                nodesAtDepth[i][j]->mChildren = new Node*[nodesAtDepth[i][j]->mChildCount];

                // For each move, make children
                for (std::list<Move>::const_iterator it = moves.begin(); it != moves.end(); ++it) {
                    Board tmp = nodesAtDepth[i][j]->mBoard;
                    GameManager::GetInstance()->PlayMove(tmp, *it, (i % 2 ? (playerOne ? 1 : 2) : (playerOne ? 2 : 1)), true);
                    nodesAtDepth[i][j]->mChildren[index] = new Node(nodesAtDepth[i][j], tmp, *it, i + 1);
                    tmpNodesAtDepth[j].push_back(nodesAtDepth[i][j]->mChildren[index]);
                    index++;
                }
            }
        }
        for (int j = 0; j < nodesAtDepth[i].size(); j++) {
            if (!tmpNodesAtDepth[j].empty())
                nodesAtDepth[i + 1].insert(nodesAtDepth[i + 1].end(), tmpNodesAtDepth[j].begin(), tmpNodesAtDepth[j].end());
        }

    }

    return root;
}