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

const char* typeHumanPlayer = "Human";
const char* typeNaivePlayer = "Naive Heuristic (D2)";
const char* typeRemainingTilesPlayer = "Remaining Tiles Player";
const char* typeCellMovesPlayer = "Cell Moves Player";
const char* typeCornerCellPlayer = "Corner Cell Player";
const char* typeRandomPlayer = "Random Player";
const char* typeBestPathPlayer = "Best Path Player";

const char* minimax = "MiniMax with Alpha-Beta Pruning";
const char* montecarlo = "Monte Carlo";

const char** PlayerFactory::PlayerTypes(/*out*/ unsigned int& len)
{
    static const char* types[] = {typeHumanPlayer,
                                 typeNaivePlayer,
                                 typeRemainingTilesPlayer,
                                 typeCellMovesPlayer,
                                 typeCornerCellPlayer,
                                 typeRandomPlayer,
                                 typeBestPathPlayer};

    len = sizeof(types) / sizeof(char*);

    return types;
}

const char** PlayerFactory::SearchTypes(/*out*/ unsigned int& len)
{
    static const char* opts[] = { minimax, montecarlo };

    len = sizeof(opts) / sizeof(char*);

    return opts;
}

Player* PlayerFactory::Create(const char* type, const bool& playerOne, const int& depth, bool minimax)
{
    if (strcmp(type, typeHumanPlayer) == 0) {
        return new HumanPlayer(playerOne);
    } else if (strcmp(type, typeNaivePlayer) == 0) {
        return new NaivePlayer(playerOne, depth, minimax);
    } else if (strcmp(type, typeRemainingTilesPlayer) == 0) {
        return new RemainingTilesPlayer(playerOne, depth, minimax);
    } else if (strcmp(type, typeCellMovesPlayer) == 0) {
        return new CellMovesPlayer(playerOne, depth, minimax);
    } else if (strcmp(type, typeCornerCellPlayer) == 0) {
        return new CornerCellPlayer(playerOne, depth, minimax);
    } else if (strcmp(type, typeRandomPlayer) == 0) {
        return new RandomPlayer(playerOne, depth, minimax);
    } else if (strcmp(type, typeBestPathPlayer) == 0) {
        return new BestPathPlayer(playerOne, depth, minimax);
    }

    throw std::runtime_error("Invalid player type in PlayerFactory::Create");
}
