#include "GameManager.h"

#include <set>

using namespace std;

GameManager* GameManager::mInstance(nullptr);

GameManager::GameManager() : mConsecutiveNoAttack(0), mRow(BOARD_ROWS), mCol(BOARD_COLS)
{
    mBoardSize = mRow * mCol;
    mBoard = new Board();
    mTokens[0] = 22;
    mTokens[1] = 22;
}

GameManager::~GameManager()
{
    delete mBoard;
    delete mInstance;
}

GameManager* GameManager::GetInstance()
{
    if (mInstance == nullptr)
        mInstance = new GameManager();

    return mInstance;
}

GameManager::Outcome GameManager::EvaluateWinningCondition()
{
    Outcome outcome = None;

    //No more black tokens
    if (mTokens[0] == 0)
        outcome = Player2Win;
    //No more white tokens
    else if (mTokens[1] == 0)
        outcome = Player1Win;

    return outcome;
}

bool GameManager::IsValidMove(const Move& move, bool playerOne)
{
    int currPos = move.mStartPos;

    //Check if start and end are on board
    if (move.mStartPos < 0 || move.mEndPos > mBoardSize - 1
        || move.mEndPos < 0 || move.mEndPos > mBoardSize - 1)
        return false;

    //Check that the start cell has the player's token and the end cell is empty
    //Assuming: 0 -> empty, 1 -> playerOne, 2-> playerTwo
    int startPlayer = mBoard->GetPlayer(move.mStartPos);
    int endPlayer = mBoard->GetPlayer(move.mEndPos);

    if (endPlayer != 0)
        return false;
    if (playerOne && startPlayer != 1)
        return false;
    if (!playerOne && startPlayer != 2)
        return false;

    //Check if start -> end is valid given the colour

    //Black and White:
    //Up: -9, Down: +9, Left: -1, Right +1
    //Black only (corners):
    //TR: -8, TL: -10, BR: +10, BL: +8

    int absDirection = abs(move.mEndPos - move.mStartPos);

    set<int> blackMoves = { 1, mCol - 1, mCol, mCol + 1 };
    set<int> whiteMoves = { 1, mCol };

    auto blackSearch = blackMoves.find(absDirection);
    auto whiteSearch = whiteMoves.find(absDirection);

    bool isBlack = mBoard->IsBlack(move.mStartPos);

    if (isBlack && blackSearch == blackMoves.end())
        return false;
    if (!isBlack && whiteSearch == whiteMoves.end())
        return false;

    //TODO: Not sure if set is slower
    //if (mBoard.IsBlack(move.mStartPos))
    //{
    //    if (absDirection != mCol && absDirection != 1 && absDirection != mCol - 1 && absDirection != mCol + 1)
    //        return false;
    //}

    return true;
}

GameManager::Outcome GameManager::PlayMove(const Move& move, int opponent)
{
    Outcome outcome = None;

    Attack(move, opponent);

    mBoard->Move(move.mStartPos, move.mEndPos);

    outcome = EvaluateWinningCondition();

    if (outcome == None && mConsecutiveNoAttack >= 10)
        outcome = Draw;

    return outcome;
}

void GameManager::Attack(const Move& move, int opponent)
{
    int direction = move.mEndPos - move.mStartPos;

    //Forward attack
    if (mBoard->GetPlayer(move.mStartPos + 2 * direction) == opponent)
        Eliminate(move.mEndPos, direction, opponent);
    //Backward attack
    else if (mBoard->GetPlayer(move.mStartPos - 2 * direction) == opponent)
        Eliminate(move.mEndPos, -direction, opponent);
    //Defensive move
    else
        mConsecutiveNoAttack++;
}

int GameManager::Eliminate(int currentPos, int direction, int opponent)
{
    int desiredEnd = currentPos + direction;

    //Check if desired attack position is on the board
    if (desiredEnd < 0 || desiredEnd > mBoardSize - 1)
        return 0;

    //Check to see if desired attack pos is in same line as original
    //This is only a problem if we are moving left or right
    if (direction == -1 && currentPos % mCol == 0)
        return 0;
    if (direction == 1 && currentPos % mCol == mCol - 1)
        return 0;

    //If desired attack position has an opponent, attack and keep going
    if (mBoard->GetPlayer(desiredEnd) == opponent)
    {
        mBoard->Clear(desiredEnd);
        mTokens[opponent - 1]--;
        currentPos += direction;
        return Eliminate(currentPos, direction, opponent) + 1;
    }

    //If attacked cell does not hold an opponent, we are done
    return 0;
}
