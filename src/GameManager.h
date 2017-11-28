#pragma once

#include "Board.h"
#include "Move.h"

class GameManager
{
private:
    static GameManager* mInstance;
    int mTokens[2];
    int mConsecutiveNoAttack;

    // FOR AI ONLY
    int mAIConsecutiveNoAttack;
    bool mDrawOccurred;

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
    Outcome EvaluateAIWinningCondition(const Board& board);
    bool IsValidMove(const Board& board, const Move& move, const bool& playerOne) const;
    Outcome PlayMove(Board& board, const Move& move, int opponent, bool ai);
    void Attack(Board& board, const Move& move, int opponent, bool ai);
    int Eliminate(Board& board, int currentPos, int direction, int opponent, bool ai);

    inline void SetAICount(int count) { mAIConsecutiveNoAttack = count; if (count >= 10) mDrawOccurred = true; else mDrawOccurred = false; }
    inline int GetAICount() { return mAIConsecutiveNoAttack; }
    inline bool GetDrawOccurred() { return mDrawOccurred; }
};