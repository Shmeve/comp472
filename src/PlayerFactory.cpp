#include "PlayerFactory.h"

#include <string.h>
#include <stdexcept>

#include "Player/HumanPlayer.h"
#include "Player/NaivePlayer.h"
#include "Player/RemainingTilesPlayer.h"

const char* typeHumanPlayer = "Human";
const char* typeNaivePlayer = "Naive Heuristic (D2)";
const char* typeRemainingTilesPlayer = "Remaining Tiles Player";

const char** PlayerFactory::Options(/*out*/ unsigned int& len)
{
    static const char* opts[] = {typeHumanPlayer,
                                 typeNaivePlayer,
                                 typeRemainingTilesPlayer};

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
    }

    throw std::runtime_error("Invalid player type in PlayerFactory::Create");
}
