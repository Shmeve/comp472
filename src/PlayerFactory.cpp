#include "PlayerFactory.h"

#include <string.h>
#include <exception>

#include "HumanPlayer.h"
#include "NaivePlayer.h"
#include "RemainingTilesPlayer.h"

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

Player* PlayerFactory::Create(const char* type, const bool& playerOne)
{
    if (strcmp(type, typeHumanPlayer) == 0) {
        return new HumanPlayer(playerOne);
    } else if (strcmp(type, typeNaivePlayer) == 0) {
        return new NaivePlayer(playerOne);
    } else if (strcmp(type, typeRemainingTilesPlayer) == 0) {
        return new RemainingTilesPlayer(playerOne);
    }

    throw std::runtime_error("Invalid player type in PlayerFactory::Create");
}
