#include "GameManager.h"
#include <cmath>

#include <set>

using namespace std;

GameManager* GameManager::mInstance(nullptr);

GameManager::GameManager() : mConsecutiveNoAttack(0), mRow(BOARD_ROWS), mCol(BOARD_COLS)
{
    mBoardSize = mRow * mCol;
    mTokens[0] = 22;
    mTokens[1] = 22;
}

GameManager::~GameManager()
{
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

bool GameManager::IsValidMove(Board& board, const Move& move, bool playerOne)
{
    int currPos = move.mStartPos;

    //Check if start and end are on board
    if (move.mStartPos < 0 || move.mEndPos > mBoardSize - 1
        || move.mEndPos < 0 || move.mEndPos > mBoardSize - 1)
        return false;

    //Check that the start cell has the player's token and the end cell is empty
    //Assuming: 0 -> empty, 1 -> playerOne, 2-> playerTwo
    int startPlayer = board.GetPlayer(move.mStartPos);
    int endPlayer = board.GetPlayer(move.mEndPos);

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

    set<int> blackMoves = { 1, mCol - 1, mCol, mCol + 1 };  /*1, 8, 9, 10*/
    set<int> whiteMoves = { 1, mCol };                      /*1, 9*/

    auto blackSearch = blackMoves.find(absDirection);
    auto whiteSearch = whiteMoves.find(absDirection);

    bool isBlack = board.IsBlack(move.mStartPos);

    if (isBlack && blackSearch == blackMoves.end())
        return false;
    if (!isBlack && whiteSearch == whiteMoves.end())
        return false;

    // On left/right moves check that start and end position is on the same row
    if (absDirection == 1 && move.mEndPos/mCol != move.mStartPos/mCol)
        return false;
    // On any diagonal movement check if change in rows is not 1
    if (absDirection != 1 && absDirection != 9 && abs(move.mEndPos/mCol - move.mStartPos/mCol) != 1)
        return false;

    //TODO: Not sure if set is slower
    //if (mBoard.IsBlack(move.mStartPos))
    //{
    //    if (absDirection != mCol && absDirection != 1 && absDirection != mCol - 1 && absDirection != mCol + 1)
    //        return false;
    //}

    return true;
}

GameManager::Outcome GameManager::PlayMove(Board& board, const Move& move, int opponent, bool ai)
{
    Outcome outcome = None;

    Attack(board, move, opponent, ai);

    board.Move(move.mStartPos, move.mEndPos);

    outcome = EvaluateWinningCondition();

    if (outcome == None && mConsecutiveNoAttack >= 10)
        outcome = Draw;

    return outcome;
}

void GameManager::Attack(Board& board, const Move& move, int opponent, bool ai)
{
    int direction = move.mEndPos - move.mStartPos;
    int eliminated = 0;

    // Forward attack check
    if (board.GetPlayer(move.mStartPos + 2 * direction) == opponent) {
        eliminated = Eliminate(board, move.mEndPos, direction, opponent, ai);
        mConsecutiveNoAttack = 0;
    }

    // Backward attack check and no forward attack
    if (board.GetPlayer(move.mStartPos - direction) == opponent && eliminated == 0) {
        Eliminate(board, move.mStartPos, -direction, opponent, ai);
        mConsecutiveNoAttack = 0;
    }

    // Defensive move
    if (eliminated == 0)
        mConsecutiveNoAttack++;
}

int GameManager::Eliminate(Board& board, int currentPos, int direction, int opponent, bool ai)
{
    int desiredEnd = currentPos + direction;
    int absDirection = abs(direction);

    //Check if desired attack position is on the board
    if (desiredEnd < 0 || desiredEnd > mBoardSize - 1)
        return 0;

    //Check to see if desired attack pos is in same line as original
    //This is only a problem if we are moving left or right
    if (direction == -1 && currentPos % mCol == 0)
        return 0;
    if (direction == 1 && currentPos % mCol == mCol - 1)
        return 0;

    // Check to see diagonal attacks only cross 1 column
    if (absDirection != 1 && absDirection !=9 && abs((desiredEnd % mCol) - (currentPos % mCol)) != 1)
        return 0;

    //If desired attack position has an opponent, attack and keep going
    if (board.GetPlayer(desiredEnd) == opponent)
    {
        board.Clear(desiredEnd);
        if (!ai)
            mTokens[opponent - 1]--;
        currentPos += direction;
        return Eliminate(board, currentPos, direction, opponent, ai) + 1;
    }

    //If attacked cell does not hold an opponent, we are done
    return 0;
}
