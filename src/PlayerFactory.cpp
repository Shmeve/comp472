#include "PlayerFactory.h"

#include <string.h>
#include <stdexcept>

#include "HumanPlayer.h"
#include "NaivePlayer.h"
#include "RemainingTilesPlayer.h"

const char* typeHumanPlayer = "Human";
const char* typeNaivePlayer = "Naive Heuristic (D2)";
const char* typeRemainingTilesPlayer = "Remaining Tiles Player";

const char* alphaBeta = "With Alpha-Beta Pruning";
const char* noAlphaBeta = "Without Alpha-Beta Pruning";

const char** PlayerFactory::PlayerTypes(/*out*/ unsigned int& len)
{
    static const char* types[] = {typeHumanPlayer,
                                 typeNaivePlayer,
                                 typeRemainingTilesPlayer};

    len = sizeof(types) / sizeof(char*);

    return types;
}

const char** PlayerFactory::Options(/*out*/ unsigned int& len)
{
    static const char* opts[] = {alphaBeta,
                                 noAlphaBeta};

    len = sizeof(opts) / sizeof(char*);

    return opts;
}

Player* PlayerFactory::Create(const char* type, const bool& playerOne, const bool& alphaBeta)
{
    if (strcmp(type, typeHumanPlayer) == 0) {
        return new HumanPlayer(playerOne);
    } else if (strcmp(type, typeNaivePlayer) == 0) {
        return new NaivePlayer(playerOne, alphaBeta);
    } else if (strcmp(type, typeRemainingTilesPlayer) == 0) {
        return new RemainingTilesPlayer(playerOne, alphaBeta);
    }

    throw std::runtime_error("Invalid player type in PlayerFactory::Create");
}
