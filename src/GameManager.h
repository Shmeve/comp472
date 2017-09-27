#include "Board.h"
#include "Move.h"

class GameManager
{
private:
    static GameManager* mInstance;
    int mCol;
    int mRow;
    int mBoardSize;
    Board mBoard;
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
    GameManager* GetInstance();

    Outcome EvaluateWinningCondition();
    bool IsValidMove(const Move& move, bool playerOne);
    Outcome PlayMove(const Move& move, int opponent);
    void Attack(const Move& move, int opponent);
    int Eliminate(int currentPos, int direction, int opponent);
    void GetBoard(int* board);
};