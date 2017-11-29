#include "PlayerFactory.h"

#include <string.h>
#include <stdexcept>

#include "Player/HumanPlayer.h"
#include "Player/NaivePlayer.h"
#include "Player/RemainingTilesPlayer.h"
#include "Player/CellMovesPlayer.h"
#include "Player/CornerCellPlayer.h"
#include "Player/RandomPlayer.h"
#include "Player/BestPathPlayer.h"
#include "Player/IDontKnowWhatImDoingPlayer.h"

const char* typeHumanPlayer = "Human";
const char* typeNaivePlayer = "Naive Heuristic (D2)";
const char* typeRemainingTilesPlayer = "Remaining Tiles Player";
const char* typeCellMovesPlayer = "Cell Moves Player";
const char* typeCornerCellPlayer = "Corner Cell Player";
const char* typeRandomPlayer = "Random Player";
const char* typeBestPathPlayer = "Best Path Player";
const char* typeIDontKnowWhatImDoingPlayer = "wat";

const char** PlayerFactory::Options(/*out*/ unsigned int& len)
{
    static const char* opts[] = {
            /* 0 */ typeHumanPlayer,
            /* 1 */ typeNaivePlayer,
            /* 2 */ typeRemainingTilesPlayer,
            /* 3 */ typeCellMovesPlayer,
            /* 4 */ typeCornerCellPlayer,
            /* 5 */ typeRandomPlayer,
            /* 6 */ typeBestPathPlayer,
            /* 7 */ typeIDontKnowWhatImDoingPlayer
    };

    len = sizeof(opts) / sizeof(char*);

    return opts;
}

Player* PlayerFactory::Create(const char* type, const bool& playerOne, const int& depth)
{
    if (strcmp(type, typeHumanPlayer) == 0) {
        return new HumanPlayer(playerOne);
    } else if (strcmp(type, typeNaivePlayer) == 0) {
        return new NaivePlayer(playerOne, depth);
    } else if (strcmp(type, typeRemainingTilesPlayer) == 0) {
        return new RemainingTilesPlayer(playerOne, depth);
    } else if (strcmp(type, typeCellMovesPlayer) == 0) {
        return new CellMovesPlayer(playerOne, depth);
    } else if (strcmp(type, typeCornerCellPlayer) == 0) {
        return new CornerCellPlayer(playerOne, depth);
    } else if (strcmp(type, typeRandomPlayer) == 0) {
        return new RandomPlayer(playerOne, depth);
    } else if (strcmp(type, typeBestPathPlayer) == 0) {
        return new BestPathPlayer(playerOne, depth);
    } else if (strcmp(type, typeIDontKnowWhatImDoingPlayer) == 0) {
        return new IDontKnowWhatImDoingPlayer(playerOne, depth);
    }

    throw std::runtime_error("Invalid player type in PlayerFactory::Create");
}
