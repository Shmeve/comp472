#pragma once

#include "Board.h"
#include "Move.h"

class GameManager
{
private:
    static GameManager* mInstance;
    int mCol;
    int mRow;
    int mBoardSize;
    int mTokens[2];
    int mConsecutiveNoAttack;

    GameManager();

public:
    enum Outcome
    {
        None,
        Player1Win,
        Player2Win,
        Draw
    };

    ~GameManager();
    static GameManager* GetInstance();

    Outcome EvaluateWinningCondition();
    bool IsValidMove(Board& board, const Move& move, bool playerOne);
    Outcome PlayMove(Board& board, const Move& move, int opponent, bool ai);
    void Attack(Board& board, const Move& move, int opponent, bool ai);
    int Eliminate(Board& board, int currentPos, int direction, int opponent, bool ai);
};